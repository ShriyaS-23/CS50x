#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

int count_letters(string t);
int count_words(string t);
int count_sentences(string t);

int main(void)
{
    string text = get_string("Text :\n");
    int l = count_letters(text);
    int w = count_words(text);
    int s = count_sentences(text);
    
    float L = (float)l / (float)w * 100;
    
    float S = (float)s / (float)w * 100;
    
    int read = round (0.0588 * L - 0.296 * S - 15.8);
    
    if (read < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (read > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", read);
    }
    
}

int count_letters(string t)
{
    int n = 0;
    for(int i = 0, x = strlen(t); i <= x; i++)
    {
        if ((t[i] >= 'a' && t[i] <= 'z') || (t[i] >= 'A' && t[i] <= 'Z'))
        {
            n++;
        }
    }
    return n;
}

int count_words(string t)
{
    int n = 0;
    for(int i = 0, x = strlen(t); i <= x; i++)
    {
        if (t[i] == ' ')
        {
            n++;
        }
    }
    return n+1;
}

int count_sentences(string t)
{
    int n = 0;
    for (int i = 0, x = strlen(t); i <= x; i++)
    {
        if (t[i] == '.' || t[i] == '!' || t[i] == '?')
        {
            n++;
        }
    }
    return n;
}