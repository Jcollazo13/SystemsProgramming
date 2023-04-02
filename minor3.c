// Jonathan Collazo || CSCE 3600 || EUID: 11535014 
// Minor Assignment 3 Basic Shell Program
// Basic Shell Program that takes in user input and executes commands

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Command delcarations
int shell_cd(char **args);
int shell_help(char **args);
int shell_exit(char **args);

int main()
{
    shell_loop(); // Command loop
    return 0; 
}

// Basic loop for shell structure 
void shell_loop()
{
    char *line; // User input
    char **args; // Arguments
    int status; // Status of command

    // Loop until user enters "quit" command
    do{
        printf("minor 3 > "); // Prompt for user input 
        line = shell_read_line(); // Read user input
        args = shell_split_line(line); // Split user input into arguments for execution 
        status = shell_execute(args); // Execute command

        // Free memory allocated from other functions
        free(line);
        free(args);
    }
    while(status); 
}

char *shell_read_line()
{
  char *line = NULL;
  ssize_t buffersize = 0; // have getline allocate a buffer for us

  if (getline(&line, &buffersize, stdin) == -1){
    if (feof(stdin)) {
      exit(EXIT_SUCCESS);  // EOF found 
    } else  {
      perror("readline");
      exit(EXIT_FAILURE); // NO EOF found
    }
  }

  return line;
}

char **shell_split_line(char *line)
{
  int buffersize = SHELL_TOK_BUFSIZE, position = 0;
  char **tokens = malloc(buffersize * sizeof(char*));
  char *token;

  if (!tokens) 
  {
    fprintf(stderr, "shell: allocation error");
    exit(EXIT_FAILURE);
}

token = strtok(line, SHELL_TOK_DELIM);
while(token != NULL)
{
    tokens[position] = token;
    position++;

    if (position >= buffersize) 
    {
      buffersize += SHELL_TOK_BUFSIZE;
      tokens = realloc(tokens, buffersize * sizeof(char*));
      if (!tokens) 
      {
        fprintf(stderr, "shell: allocation error");
        exit(EXIT_FAILURE);
      }
    }

    token = strtok(NULL, SHELL_TOK_DELIM);
  }

  tokens[position] = NULL;
  return tokens; // used as arguments for execvp
}

int shell_launch()
{
    pid_t pid, wpid;
    int status;

    pid = fork(); // Fork child process
    if(pid == 0) // Child process
    {
        if(execvp(args[0], args) == -1) // Execute command
        {
            perror("shell"); // Error message
        }
        exit(EXIT_FAILURE);
    }
    else if(pid < 0) // Error forking
    {
        perror("shell");
    }
    else // Parent process
    {
        do
        {
            wpid = waitpid(pid, &status, WUNTRACED); // Wait for child process to finish
        }
        while(!WIFEXITED(status) && !WIFSIGNALED(status)); // Check if child process exited normally or was terminated by a signal
    }

    return 1;
}

// List of built in commands & list of their functions 
char *builtin_str[] = {
    "cd",
    "help",
    "exit"
};


int (*builtin_func[]) (char **) = {
    &shell_cd,
    &shell_help,
    &shell_exit
};

// gets the number of built in commands 
int shell_num_builtins()
{
  return sizeof(builtin_str) / sizeof(char *); 
}

// Builtin command implementations

int shell_cd(char **args)
{
    if(args[1] == NULL) // Check if argument is valid
    {
        fprintf(stderr, "shell: expected argument to \"cd\"\n");
    }
    else
    {
        if(chdir(args[1]) != 0) // Change directory
        {
            perror("shell"); // Error message
        }
    }
    return 1;
}

int shell_help(char **args)
{
    printf("Jonathan Collazo's Shell\n");
    printf("Type program names and arguments, and hit enter.\n");
    printf("The following are built in:\n");

    // pring built in commands 
    for(int i = 0; i < shell_num_builtins(); i++)
    {
        printf(" %s\n", builtin_str[i]);
    }

    return 1; 
}

int shell_exit(char **args)
{
    return 0; // Exit shell
}

int shell_execute(char **args)
{
    if(args[0] == NULL) // Check if command was entered
    {
        printf("No command entered\n"); 
        return 1;
    }

    for(int i = 0; i < shell_num_builtins(); i++) // Check if command is built in
    {
        if(strcmp(args[0], builtin_str[i]) == 0)
        {
            return (*builtin_str[i])(args);
        }
    }

    return shell_launch(args); // Launch command
}