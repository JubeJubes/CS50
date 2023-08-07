#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>


bool isNum (string word) {
    for (int i=0, n = strlen(word);i<n;i++) {
        if (!isdigit(word[i])) {
            return false;
        }
    }
    return true;
}

int main(int argc, string argv[])
{
    if (argc != 2 || !isNum(argv[1])) {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    int key = atoi (argv[1]);
    string plaintext = get_string("plaintext:  ");
    char ciphertext[(int)strlen(plaintext)+1];
    ciphertext[(int)strlen(plaintext)] = '\0';

    for (int i=0, n=strlen(plaintext); i<n; i++) {

        if ( (plaintext[i] >96) && (plaintext[i] <123)) {
            ciphertext[i] = ((int)plaintext[i] + key - 97)%26 +97;
        }
        else if ((plaintext[i] >64) && (plaintext[i] <91)) {
            ciphertext[i] = ((int)plaintext[i] + key - 65)%26 +65;
        }
        else {
           ciphertext[i] = plaintext[i];
        }
    }

    printf("ciphertext: %s\n",ciphertext);
    return 0;
}