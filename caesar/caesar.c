#include<stdio.h>
#include<cs50.h>
#include<ctype.h>
#include <stdlib.h>
#include<string.h>

int main(int argc , string argv[])
{

    if (argc == 2)
    {
        int i = 0 ;
        int n = strlen(argv[1]);

        for(i = 0; i < n; i++)
        {
            if(!isdigit(argv[1][i]))
            {
                printf("Usage: ./caesar key\n");
                exit(1);

            }
        }

        int x = atoi(argv[1]) ;

        string text = get_string("plaintext: ");
        printf("ciphertext: ");

        for(i = 0; i < strlen(text); i++)
        {

            if(islower(text[i]))
            {
                printf("%c", (((text[i] - 'a') + x) % 26) + 'a');
            }
            else if(isupper(text[i]))
            {
                printf("%c", (((text[i] - 'A') + x) % 26) + 'A');
            }
            else
            {
                printf("%c", text[i]);
            }

            }
        }
        else
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
        printf("\n");

    }
