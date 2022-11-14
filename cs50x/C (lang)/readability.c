#include <cs50.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    // Asks the user to input text and returns it to str variable
    string str = get_string("Text: ");

    // Variables for counts
    int letters = count_letters(str);
    int words = count_words(str);
    int sentences = count_sentences(str);

    // Calculates average letters/sentences per 100 words
    double L = letters / (words / 100.0);
    double S = sentences / (words / 100.0);

    // Calculates Coleman-Liau index and rounds it to int
    int index = round((0.0588 * L) - (0.296 * S) - 15.8);

    // If index less than 16 and more than 1 prints index
    if (index < 16 && index > 1)
    {
        printf("Grade %d\n", index);
    }

    // If index less than 1 prints "Before Grade 1"
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }

    // If index more than 16 prints "Grade 16+"
    else
    {
        printf("Grade 16+\n");
    }
    return 0;
}

// Counts letters in given string
int count_letters(string text)
{
    int count = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (tolower(text[i]) >= 'a' && tolower(text[i]) <= 'z')
        {
            count++;
        }
    }
    return count;
}

// Counts words in given string
int count_words(string text)
{
    int count = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == ' ' && text[i + 1] != ' ')
        {
            count++;
        }
    }
    return count + 1;
}

// Counts sentences in given string
int count_sentences(string text)
{
    int count = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            count++;
        }
    }
    return count;
}
