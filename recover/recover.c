#include <stdio.h>
#include <stdlib.h>
#include<stdint.h>

typedef uint8_t BYTE;
int main(int argc, char *argv[])
{
    if(argc != 2){
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }
    BYTE buffer[512];
    FILE *point = NULL;
    int counter = 0;
    char *flnm = NULL;
    FILE *f = fopen(argv[1], "r");
    while(fread(buffer, sizeof(uint8_t), 512, f) == 512){
        if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0){
            if(point == NULL){
                fclose(point);
            }
            sprintf(flnm, "%03i.jpg", counter);
            FILE *img = fopen(flnm , "w");
            counter ++;
        }
        if(point != NULL){
            fwrite(buffer, sizeof(buffer), 1, point);
        }
    }

    if(point == NULL){
        fclose(point);
    }
    return 0;
}