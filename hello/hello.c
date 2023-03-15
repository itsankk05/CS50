#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string name = get_string("What's Your Name: ");
    printf("hello, %s\n", name);
}