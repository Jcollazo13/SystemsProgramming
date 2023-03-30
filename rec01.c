// Jonathan Collazo || EUID: 11535014 || CSCE 3600 Systems Programming

// Program reads in ASCII char from user & prints decimal, hexadecimal, & binary values for char 

#include <stdio.h>


char getUserInput()
{
    unsigned char target;
    printf("Enter a printable ASCII character: "); 
    scanf("%c", &target);
    printf("%c", target);
    return target;

}


void printBase10(char target)
{
    printf("\nBase 10: %d", target);

}

void printHex(char target)
{
    printf("\nHexadecimal: %x", target);
}

void printBinary(char target)
{
    int temp; 
    printf("\nBinary: ");
    for(int i = 7; i >= 0; i--)
    {
       temp = target >> i; 
       if(temp & 1 == 1)
       {
        printf("1");
       }
       else 
       {
        printf("0");
       }
    }
    printf("\n");

}

int main()
{
    unsigned char userValue = getUserInput();
    printBase10(userValue);
    printHex(userValue);
    printBinary(userValue);
    return 0;
    
}