#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");
    string result;

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    if (score1 > score2){
        result = "Player 1 wins!";
    }
    else if (score1 < score2) {
        result = "Player 2 wins!";
    }
    else {
        result = "Tie!";
    }

    printf("%s\n",result);
}

int compute_score(string word)
{
    int value =0;

    for (int i=0, n= strlen(word); i<n; i++) {
        if (isupper(word[i])||islower(word[i])) {
            value += POINTS[toupper(word[i])-65];
        }
    }
    return value;
}
