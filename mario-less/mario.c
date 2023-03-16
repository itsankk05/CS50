
#include<stdio.h>
#include<cs50.h>

int main(void)
{
    int i , j , height;
     while (true) {
                height = get_int("Height: ");

                if (height <= 8 && height > 0) {
                break;
                  }
                 }

    for(i=1; i < height+1; i++) {


        for(j=i; j<height; j++) {

        printf(" ");


        }
        for(j=0 ; j<i; j++) {

             printf("#");

         }
         printf("\n");

    }


}


