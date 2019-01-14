// Declares a dictionary's functionality

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

// Maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

int dict_word_cnt;
// Prototypes
bool check(const char *word);
bool load(const char *dictionary);
unsigned int size(void);
bool unload(void);

//trie is defined with _trie *path of length 27, 26 for english alphabets a to z and one more for character '(apostrophe)
typedef struct _trie
{
    bool is_word;
    struct _trie *path[27];
} trie;

trie head;
void populate_null_paths(trie *trie_in);
void free_trie_node(trie *trie_in);

#endif // DICTIONARY_H