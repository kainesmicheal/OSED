#include<stdio.h>
int main(){
 
    char input[100];
    char password[10] = "hello";
 
    printf ("\nEnter your password: ");
    scanf("%100s", &input);
    printf("\n Your string is :");
    printf(input);
    if (strcmp(password,input,5) == 0){
        printf("\nYour password is correct\n");
    }
    else
        {
        printf("\n Password doesn't match\n");
    }
}
