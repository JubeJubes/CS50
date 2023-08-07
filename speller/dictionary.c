// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 100;

// Hash table
node *table[N] ={NULL};

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    node *temp_ptr;
    temp_ptr = table[hash(word)];
    while (temp_ptr != NULL) {
        if (strcasecmp(temp_ptr->word, word) == 0) {
            return true;
        }
        temp_ptr = temp_ptr->next;
    }
    return false;
}

//Hashes word to a number
unsigned int hash(const char *word)
{
    //TODO: Improve this hash function
    unsigned int h_return;
    if (isalpha(word[1])) {
        return (toupper(word[0]) + toupper(word[1]) - 129);
    }
    return toupper (word[0]) - 'A';
}

// unsigned int hash(const char *word)
// {
//     //TODO: Improve this hash function
//     unsigned int h_return;
//     unsigned char_count=0, char_out=0;
//     for (int i=0, len =strlen(word); (i<2 || i <len); i++) {
//         char_count += word[i];
//     }

//     return char_count % 100;
// }

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *dic_file = fopen(dictionary, "r");
    if (dic_file == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        return 1;
    }

    int index = 0;
    unsigned int hash_return;
    char c;
    char *word_temp = malloc (46*sizeof(char));
    node *temp_ptr, *last_ptr;
    while (fread(&c, sizeof(char), 1, dic_file))
    {
        if (isalpha(c) || (c == '\'' && index > 0)){
            word_temp[index] = c;
            index++;

            if (index > LENGTH)
            {
                // Consume remainder of alphabetical string
                while (fread(&c, sizeof(char), 1, dic_file) && isalpha(c));

                // Prepare for new word
                index = 0;
            }
        }
        else if (index>0 ) {
            word_temp[index] = '\0';
            temp_ptr = malloc(sizeof(node));
            strcpy(temp_ptr->word,word_temp);
            hash_return = hash(word_temp);
            temp_ptr->next = table[hash_return];
            table[hash_return] = temp_ptr;

////////////////////////////////////////////////////////////
/*
            if (table[hash(word_temp)]==NULL) {
                table[hash(word_temp)] = temp_ptr;
            }
            else{
                last_ptr = table[hash(word_temp)];
                while (last_ptr->next != NULL) {
                    last_ptr=last_ptr->next;
                }
                last_ptr->next = temp_ptr;
            }
*/
/////////////////////////////////////////////////////////////////
            index=0;
        }
    }
    free(word_temp);
        // Close text
    fclose(dic_file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    unsigned count=0;
    node *t_ptr;

    for (int i=0; i<N;i++) {
        t_ptr = table[i];
        while (t_ptr!=NULL){
            t_ptr = t_ptr->next;
            count++;
        }
    }
    return count;
}

//unload recursive helper
void freeup(node *p){
    if (p==NULL) return;
    freeup(p->next);
    free(p);
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO

    for (int i=0; i<N;i++) {
        freeup(table[i]);
    }

    return true;

}

