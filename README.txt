My implementation of the wordfreak game revolves around the functions readline, splitline, and
ultimately processfile which incorporates the other two functions.  The readline function reads
a single char from a word one by one and evaluates the char based on what it is.  If the char is
an uppercase letter, then it is turned into lowercase.  If the char is not a letter (a number for example)
then a space is used to replace it. If the char is '\n', it stops processing.  The splitline function
is used to split a given line into words based on a new line or space delimiter.  The processfile
then calls these two functions to properly evaluate each line input.  The hashing part of my 
implementation takes place in my hw3.c file and is called int hash(char letter) and it essentially
takes in a char and converts it to a number used for the hashtable.  The BST part of my implementation
occurs in the bst.c file and it contains the basic functions associated with bsts such as creating
a node, inserting, and removing.  Within this file are also functions used to find things like the
max length of a word within the tree which is then used for output formatting.  And finally, once 
my program is done running, all memory is freed with my freeHashTabMemory function which frees all
data in the hashtable and frees all nodes in the tree as well.



VIDEO LINK: https://youtu.be/eo3fQif4-E0