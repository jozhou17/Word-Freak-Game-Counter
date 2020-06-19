#include "bst.h"

/*
 goal: Get the word with max count;
 param WORD_NODE *root: pointer to root of bst
 */
int getMaxWordCount(WORD_NODE *root)
{
    static int maxWordCount = 0;

    if (root != NULL)
    {
        if (root->count > maxWordCount)
        {
            maxWordCount = root->count;
        }

        getMaxWordCount(root->left);

        getMaxWordCount(root->right);
    }

    return maxWordCount;
}

/* goal: get the length of the max number  for formating
    param WORD_NODE *hashTable[]: pointer to an hashtable of WORD_NODES to be traversed through to get maxWordCount
*/
int getFormatNumberSize(WORD_NODE *hashTable[])
{
    int maxNumberCnt = 0;
    char cnt[10];
    for (int i = 0; i < INDEX_SIZE; ++i)
    {
        maxNumberCnt = getMaxWordCount(hashTable[i]);
    }

    // Convert the max word count into a "String" 123 become "123". It means the number has a size of 3 for formating
    sprintf(cnt, "%i", maxNumberCnt);

    // reurn the size of the number.
    return strlen(cnt);
}
/*
 goal: get the max word length for formating in the out file
 param WORD_NODE *root: pointer to root of bst
*/
int getMaxWordLength(WORD_NODE *root)
{
    static int maxWordLen = 0;

    if (root != NULL)
    {
        if (strlen(root->key) > maxWordLen)
        {
            maxWordLen = strlen(root->key);
        }

        getMaxWordLength(root->left);

        getMaxWordLength(root->right);
    }

    return maxWordLen;
}
/*
 goal: Search the whole hashtable for the max word size, each slot in the hashtable holds bst
 param: WORD_NODE *hashTable: pointer to hashtable of WORD_NODES to be traversed through to get maxWordLength
 */
int getFormatWordSize(WORD_NODE *hashTable[])
{
    int maxWordLen = 0;
    for (int i = 0; i < INDEX_SIZE; ++i)
    {
        maxWordLen = getMaxWordLength(hashTable[i]);
    }

    return maxWordLen;
}
/*
goal: creates a WORD_NODE node
param char word[]: array containing words
*/
WORD_NODE *createNode(char word[])
{
    WORD_NODE *ptr;
    ptr = malloc(sizeof(WORD_NODE));
    ptr->count = ((word != NULL) ? 1 : 0); // initalize the count to 1 for each word
    strcpy(ptr->key, word);
    ptr->left = NULL;
    ptr->right = NULL;

    return ptr;
}
/*
goal: insert node into bst
param WORD_NODE *root: root of bst
param char word[]: array containing words
*/
WORD_NODE *insert(WORD_NODE *root, char word[])
{
    if (root == NULL)
    {
        return createNode(word);
    }
    else if (strcmp(root->key, word) < 0)
    {
        root->right = insert(root->right, word);
    }
    else if (strcmp(root->key, word) > 0)
    {
        root->left = insert(root->left, word);
    }
    else
    {
        root->count = root->count + 1; // if the word is already exist in the BST then increase the count by 1
    }

    return root;
}
/*
goal: frees pointers from entire tree
param WORD_NODE *root: root of bst
*/
void removeTree(WORD_NODE *root)
{
    if (root != NULL)
    {
        removeTree(root->left);
        removeTree(root->right);
        free(root); // Recursively remove the leaf first.
    }
}
/*
goal: Free the memory for the hashtable, each hash index hold a BST.
param WORD_NODE *hashtable: pointer to hashtable
*/
void freeHashTabMemory(WORD_NODE *hashTable[])
{
    printf("\nFree memory for the HashTable : \n");
    for (int i = 0; i < INDEX_SIZE; ++i)
    {
        if (hashTable[i] != NULL)
        {
            printf("Free memory for BST : %c \n", hashTable[i]->key[0]);
            removeTree(hashTable[i]);
        }
    }
}
/*
 goal: Write to the file in order
 param WORD_NODE *root: root of bst
 param int fd: file descriptor when file opened
 */
void inOrder(WORD_NODE *root, int fd, int wordSize, int numberSize)
{
    char word[100];
    if (root != NULL)
    {
        inOrder(root->left, fd, wordSize, numberSize);

        printf("%-*s : %*i\n", wordSize, root->key, numberSize, root->count);

        //means left justify, * is the size
        sprintf(word, "%-*s : %*i\n", wordSize, root->key, numberSize, root->count);
        // write to file
        write(fd, word, strlen(word));
        inOrder(root->right, fd, wordSize, numberSize);
    }
}
