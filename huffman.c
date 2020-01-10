#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "huffman.h"
SingleNode * head = NULL;
SingleNode * cursor = NULL;
SingleNode * heapRoot =NULL;

void readFile(char *argument){//this function taken in a file and read it character by until it finds a special character, make it a token and insert it in a linked list.
    char currentToken[1][30];
    char *delimiterToken[10];
    int top=0;
    int index =0;
    int j =0;
    int file = open(argument,O_RDONLY);
    
    if (file ==-1){//check to see if file exist
      printf("Error, unable to open file\n");
      return;
    }
    
    char currentCharacter;
    int status =0;
    char f='y';
    
    do {
      status = read(file, &currentCharacter, 1);
      if (status <=0 && f == 'y'){
        printf("Error No tokens to read\n");
        return;
      }
      if (status>0){// check to see if the file sitll have content to read
      f = 'n';
      if (currentCharacter == ' '){ // if it comes accross space store the token and pass it into a linkked list, treats the space as a token as a value of $%1 and pass it into a linked list. The same procedure goes with the other else ifs but just with different special character with their corresponding strings.
          if (top !=0){
              currentToken[index][top] = '\0';
              insertNode(currentToken[index],top);
              index = 0;
              top =0;
           }
          delimiterToken[j]= "$%1";
          insertNode(delimiterToken[j],3);
          j = 0;
      }      
      else if (currentCharacter =='\t'){
          if (top !=0){
              currentToken[index][top] = '\0';
              insertNode(currentToken[index],top);
              index = 0;
              top =0;
           }
          delimiterToken[j]= "$%2";
          insertNode(delimiterToken[j],3);
          j = 0;
      }
      else if (currentCharacter == '\b'){
          if (top !=0){
              currentToken[index][top] = '\0';
              insertNode(currentToken[index],top);
              index = 0;
              top =0;
           }
          delimiterToken[j]= "$%3";
          insertNode(delimiterToken[j],3);
          j = 0;
      }
      else if (currentCharacter == '\''){
         if (top !=0){
              currentToken[index][top] = '\0';
              insertNode(currentToken[index],top);
              index = 0;
              top =0;
           }
          delimiterToken[j]= "$%4";
          insertNode(delimiterToken[j],3);
          j = 0;
      
      }
      else if (currentCharacter == '\"'){
         if (top !=0){
              currentToken[index][top] = '\0';
              insertNode(currentToken[index],top);
              index = 0;
              top =0;
           }
          delimiterToken[j]= "$%5";
          insertNode(delimiterToken[j],3);
          j = 0; 
      
      }
      else if (currentCharacter == '\?'){
          if (top !=0){
              currentToken[index][top] = '\0';
              insertNode(currentToken[index],top);
              index = 0;
              top =0;
           }
          delimiterToken[j]= "$%6";
          insertNode(delimiterToken[j],3);
          j = 0;
      
      }
      else if (currentCharacter == '\\'){
          if (top !=0){
              currentToken[index][top] = '\0';
              insertNode(currentToken[index],top);
              index = 0;
              top =0;
           }
          delimiterToken[index]= "$%7";
          insertNode(delimiterToken[j],3);
          j = 0;
      
      }
      else if (currentCharacter == '\a'){
         if (top !=0){
              currentToken[index][top] = '\0';
              insertNode(currentToken[index],top);
              index = 0;
              top =0;
           }
          delimiterToken[j]= "$%8";
          insertNode(delimiterToken[j],3); 
          j = 0;
      
      }
      else if (currentCharacter == '\f'){
              if (top !=0){
              currentToken[index][top] = '\0';
              insertNode(currentToken[index],top);
              index = 0;
              top =0;
           }
          delimiterToken[index]= "$%9";
          insertNode(delimiterToken[index],3);
          j = 0;
      }
      else if (currentCharacter == '\n'){
          if (top !=0){
              currentToken[index][top] = '\0';
              insertNode(currentToken[index],top);
              index = 0;
              top =0;
           }
          delimiterToken[j]= "$%0";
          insertNode(delimiterToken[j],3);
          j = 0;
      
      }
      else if (currentCharacter == '\r'){
         if (top !=0){
              currentToken[index][top] = '\0';
              insertNode(currentToken[index],top);
              index = 0;
              top =0;
           }
          delimiterToken[j]= "$1%";
          insertNode(delimiterToken[j],3);
          j = 0;
      }
      else if (currentCharacter == '\v'){ 
          if (top !=0){
              currentToken[index][top] = '\0';
	      insertNode(currentToken[index],top);
              index = 0;
              top =0;
           }
          delimiterToken[index]= "1$%";
          insertNode(delimiterToken[j],3);
          j = 0;
      }
       else {// if it is just a regular character put it in the current token.
         currentToken[index][top] = currentCharacter;
         top ++;
      }
     }
    }while(status >0);
  close(file);
}

void initialNode (char *token){// this function initializes the head of the linked list.
   head = (SingleNode*)malloc (sizeof(SingleNode));
   head ->string = token;
   head->frequency =1;
   head -> left =NULL;
   head ->right = NULL;
   head ->next = NULL;
   cursor = head;
}
void insertNode(char *input, int top){// this fuction taken in the tokens got from the readFile and store them in a linked list
     int i =0;
     int numChar = top+1; 
     char*temp = (char*)malloc(sizeof(char)*numChar);
     
     if(temp == NULL){// check to see if malloc did not return NULL
         printf("sorry malloc return Null\n");
         return;
     }
     for(i=0; i< numChar; i++)// this resize the token that we just received
       temp[i]= input [i];
     
     if (head == NULL){// check to see if the linked list has been initialized.
       initialNode(temp);
       return;
     }
     
     SingleNode* newNode = (SingleNode*) malloc (sizeof(SingleNode));
     
     if(newNode == NULL){
         printf("sorry malloc return Null\n");
         return;
     }
     newNode->string =temp;//initialize new Node
     newNode ->frequency =1;
     newNode->next = NULL;
 
     SingleNode *currentNode = head;
     while (currentNode-> next != NULL){ //loop until the end of the tokens
       if (strcmp(currentNode->string, newNode->string)==0){// if a given token already exist in the linked list just increment the frequency and break the loop
           currentNode->frequency = currentNode->frequency + 1;
           break;
       }
       currentNode = currentNode->next;
     }
     if (currentNode-> next == NULL){// check to see if the loop reached the end
       if(strcmp(currentNode->string, newNode->string)==0)// check to see if 
          currentNode->frequency = currentNode->frequency + 1;
       else{
          currentNode->next = newNode;
          }
          
     }

}

void frequencyShorter(){// the function shorts the linked list that holds the tokens in an ascending order based on their the frequency of the tokens.
  if (head == NULL || head->next ==NULL)
     return;
  SingleNode*current;
  SingleNode*nextNode;
  for (current = head; current->next !=NULL; current =current->next){
     for (nextNode = current->next; nextNode !=NULL; nextNode = nextNode->next){
        if (current->frequency > nextNode->frequency){//if the frequency of the current node is greater than the frequency of the next node swap the data that is in the the two nodes using a temporary node.
           
           SingleNode * temporaryNode= (SingleNode*)malloc (sizeof(SingleNode));
           temporaryNode->string = current->string;
           temporaryNode->frequency = current->frequency;
           temporaryNode->left = current->left;
           temporaryNode->right = current->right;
           
            current->string =nextNode ->string;
            current->frequency =nextNode->frequency;
            current->left =nextNode->left;
            current->right = nextNode->right;
            
            nextNode ->string= temporaryNode->string;
            nextNode ->frequency = temporaryNode->frequency ;
            nextNode ->left = temporaryNode->left ;
            nextNode->right = temporaryNode->right ;

        }
     }
   }
}
char isDelimter (char character){// this function check to see if it is a character that marks the end of a token by checking to see if it is one of the special characters
   if (character== ' ' ||character =='\n' ||character =='\t' || character== '\b' ||character =='\"' ||character =='\'' || character== '\?' ||character =='\\' ||character =='\f' || character =='\r' ||character =='\v' || character== '\a')
      return 'y';
   else  return 'n';
}
char * correspondingDelimiter (char chacter){//this function receives a character then check to see if it is a special character. if that is the case, it returns the corresponding special character
 
   if (' '==0)
      return "$%1";
   else if ('\t'==0)
      return "$%2";
   else if ('\b'==0)
      return "$%3";
   else if ('\''==0)
      return "$%4";
   else if ('\"'==0)
      return "$%5";
   else if ('\?'==0)
      return "$%6";
   else if ('\\'==0)
      return "$%7";
   else if ('\a'==0)
      return "$%8";
   else if ('\f'==0)
      return "$%9";
   else if ('\n'==0)
      return "$%0";
   else if ('\r'==0)
       return "$1%";
   return "1$%";

}

void searchInBook(char*book, char *stringTosearch,int top,char*fileToCompress){
  //this function takes in a token and goes to the codebook to look for its bit string if it finds it uses it corresponding bit string to compress it.
  
   int lengthOfFileName = strlen(fileToCompress)+5;
   char *fileName = (char*) malloc (sizeof(char)*lengthOfFileName);
   strcpy(fileName,fileToCompress);//copies file name in a variables
   strcat(fileName, ".hcz");// concatinate the file name with .hcz to form the name of the compressed file.
   int file= open(fileName,O_CREAT|O_APPEND|O_RDWR,00644);//opens a new file to be able to write the compressed data in it.
   int i =0;
   
   int numChar = top+1; 
   char*actualString = (char*)malloc(sizeof(char)*numChar);
   if (actualString == NULL){
      printf("sorry malloc return NULL\n");
      return;
   }
   for(i=0; i< numChar; i++)
   actualString[i]= stringTosearch[i];//copies the data in the string that we want to search into a new variable to resize it.
   int fbook = open(book, O_RDONLY);
   if (fbook ==-1){//check to see if file exist
      printf("Error, unable to open file\n");	
      return;
    }
    int status =0;
    char currentCharacter;
    char stringToken [1][30];
    int row =0;
    int col=0;
    
    do {
        char hasWritten = 'n';//tells if we has already find the token in the codebook and compressed
        int index=0;
        status = read(fbook, &currentCharacter,1);
        if (status>0){
            while (currentCharacter !='\t'){//stores the string data into 2D array until it comes accross a the tab that seperates the tokens and their corresponding bit strings.
                stringToken[row][col]=currentCharacter;
                col=col+1;
                status = read(fbook, &currentCharacter,1);
            }
            
        stringToken[row][col]='\0';// put a null terminator at the end of the current token
        status = read(fbook, &currentCharacter,1);
        col =col+1;
           
        char*temp = (char*)malloc(sizeof(char)*col);
         temp[index] = stringToken[row][index];// resizes the token we just read to avoid overflow.
         index = index+1;
         while (index <col){
            temp[index] = stringToken[row][index];
            index++;
         }
          row =0;
          col =0;
         if (strcmp(actualString,temp)==0){// compare the string we are trying to compress with the token we just read from the code book.  if they are the same it will write its corresponding bit string into the compressed file
             while(currentCharacter !='\n'){
                 write(file,&currentCharacter,1);
                 status = read(fbook, &currentCharacter,1);
             }
             hasWritten ='y';
         }
         else{ // they are not the same, it will just read without writing into the compressed file until the end of codebook line.
             while(currentCharacter !='\n'){
                 status = read(fbook, &currentCharacter,1);
             }
         }
      }
      if (hasWritten == 'y')// if we found the token and compressed it, break out of the loop
         break;
    }while(status>0);
  close(fbook);
  close(file);
}
void compressor(char*fileToCompress, char*book){
     int fcompress = open(fileToCompress,O_RDONLY);// open the file we want to compress
     int fbook = open(book, O_RDONLY); // open our codeBook
     if (fcompress == -1||fbook ==-1){// if either of them is not a file print error message and return.
        printf("Error, Unable to open file either wrong codeBook or wrong file to compress\n");
        return;
     }
    char currentToken[1][30];
    char *delimiterToken[10];
     int top =0;
     char charFCompress;
     int statusCompress =0;
     char typeOfChar;
     int j=0; 
     int index=0;
     do{
        statusCompress = read(fcompress, &charFCompress,1);
        if (statusCompress>0){//check to see if it is a special character that marks the end of a token       
            typeOfChar = isDelimter(charFCompress);
             if (typeOfChar == 'y'){
             //if it is a special character, add the null terminator to the current token and pass it to search function to look for its corresponding bit string. it the replace the special character with the string that was assigned to it and pass it into the search function to look for its corresponding bit string
                 if (charFCompress == ' '){
                    if (top !=0){
                        currentToken[index][top] = '\0';
                         searchInBook(book,currentToken[index],top,fileToCompress);
                         index = 0;
                         top =0;
                     }
                   delimiterToken[j]= "$%1";
                   searchInBook(book,delimiterToken[j],3,fileToCompress);
	  	   j = 0;
                } 
                     
                else if (charFCompress =='\t'){
         	     if (top !=0){
              		currentToken[index][top] = '\0';
              		searchInBook(book,currentToken[index],top,fileToCompress);
	                index = 0;
                        top =0;
                      }
                    delimiterToken[j]= "$%2";
                    searchInBook(book,delimiterToken[j],3,fileToCompress);
                    j = 0;
              }
              else if (charFCompress == '\b'){
          	     if (top !=0){
              		currentToken[index][top] = '\0';
              		searchInBook(book,currentToken[index],3,fileToCompress);
              		index = 0;
              		top =0;
          	     }
          	    delimiterToken[j]= "$%3";
          	    searchInBook(book,delimiterToken[j],3,fileToCompress);
          	    j = 0;
      	    }
      	    else if (charFCompress == '\''){
         	 if (top !=0){
              	      currentToken[index][top] = '\0';
                      searchInBook(book,currentToken[index],3,fileToCompress);
              	      index = 0;
              	      top =0;
           	}
          	delimiterToken[j]= "$%4";
          	searchInBook(book,delimiterToken[j],3,fileToCompress);
          	j = 0;      
      	  }
      	  else if (charFCompress == '\"'){
         	if (top !=0){
              	     currentToken[index][top] = '\0';
                     searchInBook(book,currentToken[index],top,fileToCompress);
                     index = 0;
                    top =0;
           	}
          	delimiterToken[j]= "$%5";
          	searchInBook(book,delimiterToken[j],3,fileToCompress);
          	j = 0; 
      
      	  }
      	  else if (charFCompress == '\?'){
          	if (top !=0){
              	    currentToken[index][top] = '\0';
                    searchInBook(book,currentToken[index],3,fileToCompress);
                    index = 0;
             	    top =0;
           	}
          	delimiterToken[j]= "$%6";
          	searchInBook(book,delimiterToken[j],3,fileToCompress);
          	j = 0;
      
      	}
        else if (charFCompress == '\\'){
              if (top !=0){
              	   currentToken[index][top] = '\0';
                   searchInBook(book,currentToken[index],3,fileToCompress);
                   index = 0;
                   top =0;
              }
              delimiterToken[index]= "$%7";
              searchInBook(book,delimiterToken[index],3,fileToCompress);
              index = 0;
      
      }
      else if (charFCompress == '\a'){
             if (top !=0){
              	 currentToken[index][top] = '\0';
                 searchInBook(book,currentToken[index],3,fileToCompress);
                 index = 0;
                 top =0;
              }
              delimiterToken[j]= "$%8";
              searchInBook(book,delimiterToken[j],3,fileToCompress); 
              j = 0;
      
      }
      else if (charFCompress == '\f'){
              if (top !=0){
                 currentToken[index][top] = '\0';
                 searchInBook(book,currentToken[index],3,fileToCompress);
                 index = 0;
                 top =0;
              }
              delimiterToken[index]= "$%9";
              searchInBook(book,delimiterToken[index],3,fileToCompress);
              index = 0;
      }
      else if (charFCompress == '\n'){
             if (top !=0){
                 currentToken[index][top] = '\0';
                 searchInBook(book,currentToken[index],top,fileToCompress);
                 index = 0;
                top =0;
            }
            delimiterToken[j]= "$%0";
            searchInBook(book,delimiterToken[j],3,fileToCompress);
            j = 0;
      
      }
      else if (charFCompress == '\r'){
            if (top !=0){
                currentToken[index][top] = '\0';
                searchInBook(book,currentToken[index],3,fileToCompress);
                index = 0;
                top =0;
            }
            delimiterToken[j]= "$1%";
            searchInBook(book,delimiterToken[j],3,fileToCompress);
            j = 0;
      }
      else if (charFCompress == '\v'){ 
           if (top !=0){
              currentToken[index][top] = '\0';
              searchInBook(book, currentToken[index],top,fileToCompress);
              index = 0;
              top =0;
           }
          delimiterToken[index]= "1$%";
          searchInBook(book,delimiterToken[j],3,fileToCompress);
          j = 0;
      }        
          }
          else{// if it is regular character just add it into the current token.
             currentToken[index][top] = charFCompress;
             top++;        
          }
        
        }
     }while (statusCompress >0);// keeps reading until the end of the file we want to compress
  close(fcompress);
  close(fbook);
}
SingleNode* minHeapNode(){ // this makes a single node of the minHeap.
   SingleNode * newNode = (SingleNode*)malloc(sizeof (SingleNode));
   if (newNode == NULL){
      printf("sorry malloc returned NULL\n");
      return newNode;
   }
   newNode ->left = cursor; //sets the left node to be the one with the least frequency.
   newNode->right = cursor->next; //sets the left node to be the one with the highest frequency.
   newNode->frequency = cursor->frequency+cursor->next->frequency;// make the frequency of new the sum of the frequency of the two tokens
   return newNode;
}

SingleNode* insertHeapNode(SingleNode**insertingNode){//Once it builds at new node, it passes it into this function to be insert in the minheap
    
    SingleNode* current= cursor;
    SingleNode*nextNode = cursor->next;
    while(nextNode !=NULL){// loops until the end of the nodes are being used to build the minheap
       if (current->frequency <= ((*insertingNode)->frequency)&& (
              (*insertingNode)->frequency)<nextNode->frequency){// if the frequency of the node we are trying to insert comes between two node insert it there and and return
          (*insertingNode)->next = nextNode;
          current->next = (*insertingNode);
          return cursor;    
       }
       current=current->next;
       nextNode = nextNode->next;
    }
    if(nextNode == NULL){//check to see if we reached the end of the node without inserting the new node
        if((*insertingNode)->frequency <cursor->frequency){// if the last node has a higher frequency than the one we are trying to insert, then insert it before the last node
           (*insertingNode)->next =cursor;
            cursor = (*insertingNode);        
        }
        else
           current->next= (*insertingNode);//just insert it at the end
    }
return cursor; 
} 
SingleNode* minHeapBuilder(){//build minHeap
    frequencyShorter(); //sure nodes are shorted in ascending order we start to build minHeap
    SingleNode*newNode;
    if (cursor ==NULL){
       printf("no tokens to build min Heap\n");
       return cursor;
    }
    while (cursor ->next->next !=NULL){
        newNode = minHeapNode();//call minHeapNode to make a new
        cursor = cursor->next->next; //rather than deleting the nodes the just used to create  the new node of minHeap, just ignore by moving the cursor after the last one that we used    
        insertHeapNode(&newNode);// insert the new node we just created
        frequencyShorter();//short the frequency
        
    }
   newNode= minHeapNode();
   heapRoot = newNode;// when the reach to the end of the of our nodes, make the last node we created to be the root
  return heapRoot;
}

int isALeaf(SingleNode *root){//just check to see if a node is a leaf
   return !(root->left)&&!(root->right);
}

void printArray(char*array, int number,int file){
   int i;
   for (i=0; i <number; i++){//write the string bit of any given token
     write(file,&array[i],1);
   }
   write(file,"\n",1);

}
void codeBook(SingleNode * root, char* array, int top,int file){
   if(root == NULL){
      printf("sorry you do not have tokens to build a codebook\n");
      return;
   }
   if (root ->left){//starting from the root if we go to the left, make that corresponding bit to be 0
      array[top]= '0';
      codeBook (root->left, array, top+1,file);
   }
   if (root->right){//if we go to the right, make that corresponding bit to be 1 
      array[top]='1';
      codeBook(root->right, array, top+1,file);
   }
   if (isALeaf(root)){// if we reach a  node that is a leaf, write the corresponding token in the code book.
      char*temp = malloc (sizeof(root->string));
      temp = root->string;
      int i =0;
      while (temp[i] !='\0'){
         write(file,&temp[i],1);
         i++;
      }
      write(file,&"\t",1);
      printArray(array, top,file);//call print array to print the corresponding bit string
   }
}

int maxHeightOfTree(SingleNode*root){ //just compute the heigh of the huffman tree
   if (root == NULL)
      return 0;
   else {
       int DepthOfLeft = maxHeightOfTree(root->left);//goes to the further leaf at the left
       int DepthOfRight = maxHeightOfTree(root->right);//goes to the further leaf at the right
       
       if(DepthOfLeft>DepthOfRight) //compare the two to return the greatest
          return DepthOfLeft +1;
       else
           return DepthOfRight+1;
   } 
}
char isEscape (char *stringToCheck){// check to see if a given string is special character that has been converted to that string
  if (strcmp(stringToCheck,"$%1")==0 ||strcmp(stringToCheck,"$%2")==0 ||strcmp(stringToCheck,"$%3")==0 || 
       strcmp(stringToCheck,"$%4")==0 ||strcmp(stringToCheck,"$%5")==0 ||strcmp(stringToCheck,"$%6")==0 ||
       strcmp(stringToCheck,"$%7")==0 || strcmp(stringToCheck,"$%8")==0 ||strcmp(stringToCheck,"$%9")==0 ||
       strcmp(stringToCheck,"$%0")==0 ||strcmp(stringToCheck,"$1%")==0 || strcmp(stringToCheck,"1$%")==0)
       
       return 'y';
  else 
    return 'n';

}

void decompressor(char* fileToDecompress, char* codeBook){
     char hasBreak = 'n';
     int possiblities =0;
     int lengthOfFileName = strlen(fileToDecompress)+5;
     char *fileName = (char*) malloc (sizeof(char)*lengthOfFileName);
     strcpy(fileName,fileToDecompress);// copies file name into a variable
     strcat(fileName, ".hcz");//concatinates file name with .hcz to form the decompressed file.
     int decompress= open(fileName,O_CREAT|O_APPEND|O_RDWR,00644);//opens a new file that will be used to write the decompressed data
     
     int fDecompress = open(fileToDecompress,O_RDONLY);//opens file we want to decompress
     int fbook =open(codeBook, O_RDONLY);//open codebook
     if (fDecompress ==-1 || fbook ==-1){//if neither is not a file return error message
        printf("Error, unable to open file\n");
     }
     char currentCharacter;
     char codeCharacter;
     int status =0;
     int codestatus=0;
     char stringbits[100];
     int index=0;
     int row =0;
     int col =0;
     char isEscapeChar;
     char hasCopied ='n';
     char possibleTokens[1000][100];
     char bookBits[1000][100];
     int j =0;
     int y=0;
     int x =0;
     do{
       hasBreak ='n';
       possiblities =0;
       status = read(fDecompress,&currentCharacter,1);
       if (status >0){
         stringbits[index] = currentCharacter;
         if(hasCopied !='y'){
           int fbook =open(codeBook, O_RDONLY);
           do{
             
             codestatus = read(fbook,&codeCharacter,1);
              if (codestatus>0){
                  while (codeCharacter !='\t'){//copy the string in the code book
                       possibleTokens[row][col] = codeCharacter;
                       col ++;
                       codestatus=read(fbook, &codeCharacter,1);
                  }
                  possibleTokens[row][col] = '\0';// add a null terminator
                  read(fbook,&codeCharacter,1);
                  col =0;
                  while (codeCharacter !='\n'){// copy the bit string of the corresponding token
                       bookBits[row][col] = codeCharacter;
                       col ++;
                       codestatus=read(fbook, &codeCharacter,1);
                  }
                  col =0;
                  row = row+1;
              
              }
           }while(codestatus>0);
          }
           
           hasCopied = 'y';// set the satus that we have already store the different bit strings with their corresponding tokens to be y.
           int i =0;
           while(i<row){
              if (bookBits[i][index] !=stringbits[index]){// check to see if the bit we just read from the file we want to decompress is the same as the bit string of a particular token at a paticular index
                 int y;
                 for (y=0; y<4;y++){// if not, make the that token and its bit string to be "zzzz"
                    bookBits[i][y]='z';
                    possibleTokens[i][y]='z';
		}
		bookBits[i][y]='\0';
                possibleTokens[i][y]='\0';
                y++;
              }
              else{ //if they are the same, increment the number of token that might the one we want to decompress
                  possiblities = possiblities +1;
                  y=4;
              }
           i++;
          }
           if (possiblities ==1){// the we only have one possible token 
             i =0;
             while(i<row){//go through the different tokens, and look for the one that is not "zzzz"
                 char *temporary= (char*) malloc(sizeof(char)*(y+1));
                 int w;
                 for (w =0; w<y;w++)
                   temporary[w] = possibleTokens[i][w]; 
                 temporary[w]='\0';
                if (strcmp(temporary,"zzzz") !=0){//if we find it,
                   j =0;
                   while (possibleTokens[i][j] !='\0')
                      j++;
                   char*temp= (char*) malloc (sizeof(char)*j+1);
                   x=0;
                   while (x<j){
                      temp[x] = possibleTokens[i][x];// copy it into variable
                       x++;
                   }
                   temp[x]='\0';
                   isEscapeChar =isEscape(temp);//check to see if is not a special character that has been converted to a string
                   if (isEscapeChar == 'y'){// if it is a special character that has been converted into a string,just write its corresponding character into the decompress file
                       if (strcmp(temp, "$%1")==0)
                          write ( decompress,&" ",1);
                       else if (strcmp(temp, "$%2")==0)
                          write ( decompress,&"\t",1);
                       else if (strcmp(temp, "$%3")==0)
                          write ( decompress,&"\b",1);
                       else if (strcmp(temp, "$%4")==0)
                          write ( decompress,&"\'",1);
                       else if (strcmp(temp, "$%5")==0)
                          write ( decompress,&"\"",1);
                       else if (strcmp(temp, "$%6")==0)
                          write ( decompress,&"\?",1);
                       else if (strcmp(temp, "$%7")==0)
                          write ( decompress,&"\\",1);
                       else if (strcmp(temp, "$%8")==0)
                          write ( decompress,&"\a",1);
                       else if (strcmp(temp, "$%9")==0)
                          write ( decompress,&"\f",1);
                       else if (strcmp(temp, "$%0")==0)
                          write ( decompress,&"\n",1);
                       else if (strcmp(temp, "$1%")==0)
                          write ( decompress,&"\r",1);
                       else if (strcmp(temp, "1$%")==0)
                          write ( decompress,&"\v",1);                
                   }
                   else{
                      x=0;
                      while(temp[x] !='\0'){// otherwise write whole token that is possible in to our decompress file
                        write ( decompress,&temp[x],1);
                        x++;                   
                      }
                  }            
              hasCopied ='n';// when we write a token into the decompress set the hasCopied to be n
              index =0; 
              row =0; col=0;
              hasBreak = 'y';//we find the token we want to write break and yet hasBreak to y
              break;
              }
             i++;
           }
        
       }
     if (hasBreak != 'y') //if we did not break increment the index of the token in which we are storing the the bit string we read from the compressed file.
     index = index +1;
    }
     
   }while(status>0);
   close(fDecompress);
   close(fbook);
   close (decompress);

}
