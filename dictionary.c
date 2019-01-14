
// Implements a dictionary's functionality
#include <stdio.h>
#include <stdbool.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"
#include <stdlib.h>


// This function checks if a word exists in dictionary it returns true if word is in dictionary else false
bool check(const char *word)
{
    //make cursor first point to head
    trie *cursor = &head;
    char char_to_test;
    int len = strlen(word);
    //each character of input word is iterated until the end of file 
    for (int char_pos = 0, path_no = 0; char_pos <= len; char_pos++)
    {
        char_to_test = word[char_pos];

        //If we have completed reading a word
        if (char_to_test == '\0' )
        {
            //return the boolean value of cursor->is_word
            //the value of is_word flag at that trie position is returned. If it is a word already entered in dictionary it returns true else false.
            return cursor->is_word;
        }

        if (char_to_test == '\'')
        {
            // for apostrophe put in last position, after 26 alphabets
            path_no = 26;
        }

        else
        {
            if(isupper(char_to_test))
            {
                path_no = tolower(char_to_test) - 'a';
            }

            else
            {
                //subtract 'a' (offset), to get the alphabet position (as 'a'=0, 'b'=1 ..., to fit with our logic in trie path)
                path_no = char_to_test - 'a';
            }
        }

        if(cursor->path[path_no] == NULL)
        {
            return false;
        }
        //trie path is travesed
        cursor = cursor->path[path_no];
    }
    return false;
}


// Loads dictionary into memory by reading input file, returning true if successful else false
bool load(const char *dictionary)
{
    bool loaded = false;
    populate_null_paths(&head);

    FILE *inptr = fopen(dictionary, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "could not open %s.\n", dictionary);
        return loaded;
    }

    dict_word_cnt = 0;
    int index = 0;
    //make cursor first point to head
    trie *cursor = &head;

    //each character is iterated until the end of file,
    for(int c = fgetc(inptr), pos = 0; c != EOF; c = fgetc(inptr))
    {
        // -the character is tested against alphabet or apostrophe(not the first letter of word), if true, the character is appended to word and index count is incremented.
        if (isalpha(c) || (c == '\'' && index > 0))
        {
            index++;
            // Ignore alphabetical strings too long to be words
            // If the index count of a word is greater than max-length(defined maximum length of a word), then the rest of the characters of the word is consumed and index is set to zero and continued to next iteration
            if (index > LENGTH)
            {
                // Consume remainder of alphabetical string
                while ((c = fgetc(inptr)) != EOF && isalpha(c));

                // Prepare for new word
                index = 0;
                continue;
            }
             
            if (c == '\'')
            {
                // for apostrophe put in last position, after 26 alphabets
                pos = 26;
            }
            else
            {
                //subtract 'a' (offset), to get the alphabet position (as 'a'=0, 'b'=1 ..., to fit with our logic in trie path)
                pos = c - 'a';
            }

            //since it is inside a function this is executed during runtime if this function is called, we need to allocate memory dynamically using malloc
            //if the path is not formed
            if (cursor->path[pos] == NULL) 
            {
                trie *new_cursor = malloc(sizeof(trie));
                populate_null_paths(new_cursor);

                //make cursor's that path point to new_cursor's pointer location
                cursor->path[pos] = new_cursor;

                //now make cursor point to new cursor;
                cursor = new_cursor;
            }
            //if the path is already formed, make cursor point to that path
            else
            {
                cursor = cursor->path[pos];
            }
        }
        // Ignore words with numbers (like MS Word can)
        // the character is tested against, numerical value. If it matches then the word is consumed until it finds numeric characters and index is set to zero and continued to next iteration
        else if (isdigit(c))
        {
            // Consume remainder of alphanumeric string
            while ((c = fgetc(inptr)) != EOF && isalnum(c));

            // Prepare for new word by setting index count to zero
            index = 0;
        }
        //we have completed reading a word
        // if all above test doesn't apply and index is greater than zero then it must be an end of a word, then index is set to zero and words count is incremented and is_word flag is set to true at that trie position.
        else if(index > 0 ) 
        {
            cursor->is_word = true;
            //redirect the cursor position to head to get ready for next word
            cursor = &head;
            dict_word_cnt++;
            index = 0;
            continue;
        }
    }

    fclose(inptr);

    loaded = true;
    return loaded;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return dict_word_cnt;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    //head is in heap so do free(head.path[i]) DOT
    for (int i = 0; i < 27; i++)
    {
        if (head.path[i] != NULL)
        {
            //send to recursive free_trie_node function
            free_trie_node(head.path[i]);
        }
        else
        {
            free(head.path[i]);
        }
    }
    return true;
}

//this is freeing of malloc'ed memory(in stack) so do free(cursor ->ppath[i]), USE  ->
void free_trie_node(trie *trie_in)
{
    trie *cursor = trie_in;
    for (int i = 0; i < 27; i++)
    {
        if (cursor ->path[i] == NULL)
        {
            free(cursor ->path[i]);
        }
        else
        {
            //recursive call
            free_trie_node(cursor ->path[i]);
        }
    }

    free(trie_in);
}

void populate_null_paths(trie *trie_in)
{
    for(int i = 0; i < 27; i++)
    {
        trie_in->is_word = false;
        trie_in->path[i] = NULL;
    }
}