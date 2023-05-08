/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
C#, VB, Perl, Swift, Prolog, Javascript, Pascal, HTML, CSS, JS
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

void performArithmetic(float x, float y)
{
    char sub_choice;
    
    printf("Which operations to perfrom? Choose one:\n");
    
    printf("1. Addition \n2. Subtraction \n3. Multiplication\n4. Divison\n");
    printf("Your choice:");
    scanf("%c", &sub_choice);
    printf("\n");
    
    if(sub_choice == '1')
    printf("%f + %f = %f\n", x, y, x+y);
    else if(sub_choice == '2')
    printf("%f + %f = %f\n", x, y, x-y);
    else if(sub_choice == '3')
    printf("%f + %f = %f\n", x, y, x*y);
    else if(sub_choice == '4')
    printf("%f + %f = %f\n", x, y, x/y);
    else
    printf("Invaild choice.\n");
    
}

bool isPrime (int num)
{
    if(num == 1)
        return 0;
    else if(num == 2)
        return 1;
    else 
    {
        for(int i=3; i<=num/2; i++)
            if (num%1 == 0)
                return 0;
        return 1;
    }
}

int oddOrEven (int num)
{
    if (num%2 == 0)
        return 1;
    else
        return 0;
}

int factorial (int num)
{
    int fact = 1;
    for(int i = 1; i<=num; i++)
        fact = fact*i;
    return fact;
}

int main(void)
{
    char name[20];
    char choice;
    float operand1, operand2;
    int num;
    
    printf("What is your name? ");
    scanf("%s", name);
    printf("Hello %s\n\n", name);
    
    while(1)
    {
        printf("Please enter your choice (1 to 5) from below;\n");
        
        printf("1. Arithmetic Operations\n2. Prime Detection\n3. Odd or even detection\n4. Factorial\n5. exit\n");
        printf("Your choice:");
        scanf(" %c", &choice);
        printf("\n");
        
        if(choice == '1')
        {
            printf("Enter operand 1:");
            scanf("%f", &operand1);
            printf("Enter operand 2:");
            scanf("%f", &operand2);
            
            performArithmetic(operand1, operand2);
        }
        
        else if(choice == '2')
        {
            printf("Enter Number:");
            scanf("%d", &num);
            
            if(isPrime(num))
                printf("%d is a prime number\n", num);
            else
                printf("%d is not a prime number\n", num);
        }
        
        else if (choice == '3')
        {
            printf("Enter number:");
            scanf("%d", &num);
            if(oddOrEven(num) == 1)
                printf("%d is even\n", num);
            else
                printf("%d is odd\n", num);
                
        }
        else if (choice == '4')
        {
        printf("Emter number:");
        scanf("%d", &num);
        
        printf("Factorial of %d is %d\n", num, factorial(num));
        }
        
        else if (choice == '5')
        {
            printf("Thank you for using this simple calculator.\n");
            break;
        }
        else
            printf("Thank you for using this simple calculator.\n");
    }
    
    return 0;

}
