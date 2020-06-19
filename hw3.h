#include "bst.h"

int hash(char letter);
bool readLine(char *source, int line_Length, int fd);
void splitline(char *source, char delimiter[], WORD_NODE *hashTable[]);
void processFile(char *source, int fd, WORD_NODE *hashTable[]);
void readArgvFiles(char *argv[], char *buffer, WORD_NODE *hashTable[]);
void writeOutPutToFile(WORD_NODE *hashTable[], int writeFD);
