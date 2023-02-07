// Jonathan Collazo || EUID: 11535014 || CSCE 3600 Systems Programming

#include <stdio.h>
#include <stdlib.h>


int* int_ptr;
void swap(int* int_ptr);
void getInput();

int main ()
{
getInput();
swap(int_ptr);

return 0; 

}

// Swaps the value of two integers stored in an int array, using bitwise XOR function
void swap(int* int_ptr)
{
    int_ptr[0] = int_ptr[0] ^ int_ptr[2];
    int_ptr[2] = int_ptr[0] ^ int_ptr[2];
    int_ptr[0] = int_ptr[0] ^ int_ptr[2];

    printf("New Values: %d, ", int_ptr[0]);
    printf("%d \n", int_ptr[2]);

}

// Collects initial integer values from user
void getInput()
{
    int_ptr = (int*) malloc(4); // initializes int array to hold 2 integers

   if(int_ptr == NULL)
   {
    printf("Memory allocation failed.\n");
    exit(1);
   }

   else 
   {
    printf("Enter the first integer: ");
    scanf("%d",&int_ptr[0]);

    printf("Enter the second integer: ");
    scanf("%d",&int_ptr[2]);
   }

   printf("Original Values: %d,",int_ptr[0]);
   printf("%d\n",int_ptr[2]);
}