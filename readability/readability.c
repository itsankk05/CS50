#include<stdio.h>
#include<ctype.h>
#include<cs50.h>
#include<string.h>
#include<math.h>

int count_words(string text);
int count_sentences(string text);
int count_letters(string text);

int main(void)
{

    string text = get_string("Text:") ;

    float words = count_words(text);
    float sentences = count_sentences(text);
    float letters = count_letters(text);

    float L = letters / words * 100 ;
    float S = sentences / words * 100;
    float index = (0.0588 * L) - (0.296 * S) - 15.8;
    int answer = round(index);

    if (answer > 16)
    {
        printf("Grade 16+\n");
    }
    else if (answer < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", answer);
    }


}

int count_words(string text)
{
    int word = 0 ;
    for(int i = 0; i <= strlen(text) ; i++)
    {
        if (text[i] == ' ')
        {
            word++;
        }
    }

    return word + 1;
}

int count_sentences(string text)
{
    int sentence = 0 ;
    for(int i = 0; i <= strlen(text); i++)
    {
        if(text[i] == '?' || text[i] == '!' || text[i] == '.')
        {
            sentence ++;
        }
    }
    return sentence ;
}

int count_letters(string text)
{
    int letter = 0;
    for(int i = 0; i <=strlen(text); i++)
    {
        if(isalpha(text[i]))
        {
            letter++;
        }
    }
    return letter;
}