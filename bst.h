#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdbool.h>

#define INDEX_SIZE 26

typedef struct word_node
{
    char key[30];
    int count;
    struct word_node *left;
    struct word_node *right;
} WORD_NODE;


WORD_NODE *insert(WORD_NODE *root, char word[]);
void inOrder(WORD_NODE *root, int fd, int wordSize, int numberSize);
int getMaxWordLength(WORD_NODE *root);
int getMaxNumberLength(WORD_NODE *root);
int getMaxWordCount(WORD_NODE *root);
void removeTree(WORD_NODE *root);
void freeHashTabMemory(WORD_NODE *hashTable[]);
int getFormatWordSize(WORD_NODE *hashTable[]);
int getFormatNumberSize(WORD_NODE *hashTable[]);
