#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


int count_letters (string text) {
    int count=0;
    for (int i=0; i< strlen(text);i++) {
        if (isupper(text[i])||islower(text[i])) {
            count++;
        }
    }
    return count;
}

int count_words (string text) {
    int words=1;
    for (int i=0, n = strlen(text);i<n;i++) {
        if (text[i]== ' ') {
            words++;
        }
    }
    return words;
}

int count_sentences (string text) {
    int sentences =0;
    for (int i=0, n = strlen(text);i<n;i++) {
        if ((text[i]== '!') || (text[i]== '?') || (text[i]== '.')) {
            sentences++;
        }
    }
    return sentences;
}

void coleman ( int Letters, int Words, int Sentences) {

    float cole =  5.88 * (float) Letters/Words - 29.6 * (float) Sentences/Words - 15.8;
    // printf ("%i\n",Letters);
    // printf ("%i\n",Words);
    // printf ("%i\n",Sentences);

    if (cole < 1) {
        printf("%s\n","Before Grade 1");
    }
    else if (cole > 16) {
        printf("%s\n","Grade 16+");
    }
    else {
        printf("Grade %i\n",(int)round(cole));
    }

}

int main(void)
{
    string text1 = get_string("Text: ");

    int letters = count_letters(text1);
    int words = count_words(text1);
    int sentences = count_sentences(text1);

    coleman (letters,words,sentences);
}