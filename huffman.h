#ifndef _HUFFMAN_H
#define _HUFFMAN_H
#include <stdio.h>
typedef struct node{
   char *string;
   int frequency;
   struct node* left;
   struct node*right;
   struct node *next;
} SingleNode;
//static SingleNode * heapRoot =NULL;

SingleNode*getHeapRoot(SingleNode **node);
void initialNode (char * token);
void readFile(char *argument);
void insertNode(char *input, int);
void frequencyShorter();
int isALeaf(SingleNode *root);
void codeBook(SingleNode * root, char*array, int top,int file);
void searchInBook(char*book, char *stringTosearch,int top,char*fileToCompress);
void printArray(char *array, int number,int file);
int maxHeightOfTree(SingleNode*root);
void initialNode (char *token);
void frequencyShorter();
char isDelimter (char character);
char * correspondingDelimiter (char chacter);
char isEscape (char *stringToCheck);
void compressor(char*fileToCompress, char*book);
void decompressor(char* fileToDecompress, char* codeBook);
void printList();
SingleNode* minHeapBuilder();


#endif
