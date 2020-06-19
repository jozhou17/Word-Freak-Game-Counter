// cat pipe.txt | .\hw3 t1.txt t2.txt t3.txt  // linus
// more pipe.txt | hw3 t1.txt t2.txt t3.txt  // on pc
// .\hw3 t1.txt t2.txt t3.txt
//  
// in linus  hit control d to stop the stand input and indicate a end of line
//  in window hit  contol z

#include "hw3.h"

const char OUTFILE[] = "output.txt";
const int SIZE = 1024;
const char SPACE = ' ';
const char EMV_STR[] = "WORD_FREAK"; // environment variable stores the file name

/*
goal: writes to outputfile inOrder by obtaining word and number size of each word from hashtable
param WORD_NODE *hashtable[]: pointer to hashtable
param int writeFD: file descriptor for write
*/
void writeOutPutToFile(WORD_NODE *hashTable[], int writeFD)
{
	int wordSize = getFormatWordSize(hashTable);

	int numberSize = getFormatNumberSize(hashTable);

	for (int i = 0; i < INDEX_SIZE; ++i)
	{
		// Write the words in the BST for the same hash index in order
		inOrder(hashTable[i], writeFD, wordSize, numberSize);
	}

	if (close(writeFD) < 0)
	{
		perror("Write file close error");
		printf("\n Write file close error\n");
	}
}
/*
goal: Open all files from the main argv and process it.
param char *argv[]: arguement input
param char *buffer:
*/
void readArgvFiles(char *argv[], char *buffer, WORD_NODE *hashTable[])
{
	int readFD = -1;

	//File 1  go to argv[1], file 2 go to argv[2]
	for (int i = 1; argv[i]; ++i)
	{
		printf("\n File name : %s \n", argv[i]);

		readFD = open(argv[i], O_RDONLY);

		if (readFD == -1)
		{
			perror("open file from argument error ");
		}

		processFile(buffer, readFD, hashTable);

		if (close(readFD) < 0)
		{
			perror("Open file close error");
			printf("\n Opn file close error\n");
		}
	} // end for loop
}
/*
goal: read file and split words based on space or new line
param char *source: pointer to char to be adjusted
param int fd: file descriptor
param WORD_NODE *hashTable[]: pointer to hashtable that stores each word
*/
void processFile(char *source, int fd, WORD_NODE *hashTable[])
{
	// read the file line by line
	while (readLine(source, SIZE, fd))
	{
		
		// split each line into words which delimited by SPACE or new line
		splitline(source, " \n", hashTable);
	}
}
/*
goal:
param char *source: pointer to char to be evaluated/adjusted
param char delimiter[]: array containing delimiters used to divide up letters
param WORD_NODE *hashTable[]: hashtable used to store words
*/
void splitline(char *source, char delimiter[], WORD_NODE *hashTable[])
{
	char *str = strtok(source, delimiter);

	while (str != NULL)
	{
		printf(" #: %s \n", str);

		// get the hash slot by applying the hash function to the word (based on the first char in the word)
		int hashSlot = hash(str[0]);

		// Store the word into the BST which is stored in the slot of a hashtable
		hashTable[hashSlot] = insert(hashTable[hashSlot], str);
		
		str = strtok(NULL, delimiter);
	}
}
/*
goal: read one character until end of file. If char read is not a letter, replace with space.
Also changes all letters to lowercase
param char *source: pointer to char to be adjusted 
param int line_Length: number of lines to be read
param int fd: file descriptor
*/
bool readLine(char *source, int line_Length, int fd)
{
	int ch;
	char one_char;
	char *destination = source;

	for (int i = 0; i < line_Length - 1; ++i)
	{
		if ((ch = read(fd, &one_char, 1)) == EOF || ch < 1)
		{
			break;
		}

		// if not alpha and not new line then replace it with space
		if (!isalpha(one_char) && (one_char != '\n'))
		{
			*destination++ = SPACE;
		}
		else
		{ // change to lower case
			*destination++ = tolower(one_char);
		}

		// if \n break out of the loop and stop processing
		if (one_char == '\n')
		{
			break;
		}
	}

	// Append '\0' to the end of the line. It is need for all C string library functions
	*destination = '\0';

	// if destination pointeer has not been moved at all , means empty string
	if (destination == source)
	{
		return false;
	}
	return true;
}

/*
goal: hashing function for letters
param char letter: letter to be turned into a number
*/
int hash(char letter)
{
	// letter a = 0, b =1, c = 2
	return (int)letter - 'a';
}

int main(int argc, char *argv[])
{
	int readFD = -1;
	int readEnv = -1;
	int writeFD = -1;
	char *str;
	
	// *Initalized the local variable
	WORD_NODE *hashTable[INDEX_SIZE] = { NULL, NULL, NULL, NULL, NULL,
	                                     NULL, NULL, NULL, NULL, NULL,
										 NULL, NULL, NULL, NULL, NULL,
										 NULL, NULL, NULL, NULL, NULL,
										 NULL, NULL, NULL, NULL, NULL,
										 NULL
	                                   };

	//char buffer[SIZE];
	char *buffer = (char *)calloc(SIZE, sizeof(char));

	// get file name from environment variable.
	char *envStr = getenv(EMV_STR);

	printf("# ENV variable : %s", envStr);

	if (envStr != NULL)
	{
		readEnv = open(envStr, O_RDONLY);
		if (readEnv == -1)
		{
			perror("open ENV name based file error ");
			return 1;
		}
		processFile(buffer, readEnv, hashTable);

		if (close(readEnv) < 0)
		{
			perror("Open environment name related file close error");
			printf("\n Open environment name related file close error\n");
		}
	}

	readArgvFiles(argv, buffer, hashTable);

	// process file from standard input which is  FD 0
	processFile(buffer, STDIN_FILENO, hashTable);

	//--------------------Open file for write---------------------------------------
	writeFD = open(OUTFILE, O_RDWR | O_CREAT | O_TRUNC | O_APPEND, 0644);

	writeOutPutToFile(hashTable, writeFD);

	freeHashTabMemory(hashTable);

	free(buffer);

	return 0;
}