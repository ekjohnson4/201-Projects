/*
Author: Ethan Johnson
Class: CS 201
Fall 2016
*/

#include "stdio.h"
#include "stdlib.h"
#include "ctype.h"
#include "string.h"
#include "math.h"
#include "stdbool.h"

#include "scanner.h"
#include "BSTree.h"
#include "AVLTree.h"
#include "queue.h"

void
removePunct(char *s){
  for(char *p = s; *p; ++p)
    if(isalpha(*p))
      *s++ = *p;
  *s = '\0';
}

char *
removeCap(char *str){
  for(int i=0;i<=strlen(str);i++){
     if(str[i]>=65&&str[i]<=90)
        str[i]=str[i]+32;
  }
  return str;
}

bool
isEmpty(FILE *file){
    long savedOffset = ftell(file);
    fseek(file, 0, SEEK_END);

    if (ftell(file) == 0){
        return true;
    }

    fseek(file, savedOffset, SEEK_SET);
    return false;
}

void
replaceSpace(char *str)
{
    char *dst = str;

    for (; *str; ++str) {
        *dst++ = *str;

        if (isspace(*str)) {
            do ++str;

            while (isspace(*str));

            --str;
        }
    }

    *dst = 0;
}

char *
readNextToken(FILE *fp) {
    char *s;
    if(stringPending(fp)){
        s = readString(fp);
      }
    else{
        s = readToken(fp);
      }
    return s;
};

int
main(int argc,char **argv) {
  //Check to see if user has implemented all necessary arguments
  if (argc != 4){
    printf("Need four arguments!");
    return EXIT_FAILURE;
  }

  //Set arguments to variables to determine bst or avl
  char *tree = "-b";
  char *argv1 = argv[1];

  /*************
  BST variables
  *************/
  //Set root as null
  node *root;
  root = NULL;
  node *par;

  //Node for holding parent
  node *temp = NULL;

  /*************
  AVL variables
  *************/
  //Set root as null
  anode *aroot;
  aroot = NULL;
  anode *apar;

  //Node for holding AVL parent
  anode *atemp = NULL;

  //Open file
	FILE* file = fopen(argv[2], "r");

  //Check to see if file is Empty
  bool p = isEmpty(file);

  //If empty, report empty tree
  if(p==true){
    printf("Empty tree!");
    exit(0);
  }

  //Read root from file
	char *a = readNextToken(file);

  //Strcmp argv1 and tree to determine what argv[1] is
  if (strcmp(argv1, tree) == 0){
    //while not end of text file
  	while(1){
      //Remove all punctuation and capitalization
  		removePunct(a);
  		char *b = removeCap(a);

      //Insert root
      if (root == NULL){
        par = insert(root,b);
        root = par;
      }

      //Insert other words from file into bst
      else{
        if(b[0]!='\0'){
          par = insert(root,b);
        }
      }

      //Read next item from file
  		a = readNextToken(file);

      //If end of file, break out of loop
  		if(feof(file)){
  			break;
  		}
  	}

    //Open command file
  	FILE* com = fopen (argv[3], "r");

    //Check to see if file is Empty
    bool q = isEmpty(com);

    //If empty, report empty tree
    if(q==true){
      printf("Need arguments in %s!",argv[3]);
      exit(0);
    }

    //Read first command
  	char c = readChar(com);

    //While not end of command file
    while(1){
      //Print level order
      if(c=='s'){
        printLevelOrder(root);
        printf("\n");
      }

      //Insert a word into tree
      else if(c=='i'){
        //Read word to insert
        char *d;
        d = (readNextToken(com));

        //Remove punctuation and capitalization
        removePunct(d);
        d = removeCap(d);

        //Reduce large space to a single space
        replaceSpace(d);

        //Check you're not inserting empty string
        if(d[0]!='\0'){
          //Insert read word
          par = insert(root,d);
        }
      }

      //Delete a word from tree
      else if(c=='d'){
        //Read word to delete
        char *d = readNextToken(com);

        //Reduce large space to a signle space
        replaceSpace(d);

        //Delete read word
        root = deleteNode(root, d);
      }

      //Report occurences
      else if(c=='f'){
        //Read word to find
        char *d = readNextToken(com);

        //Reduce large space to a signle space
        replaceSpace(d);

        //Search tree for node to access occurences
        searchTree(root,d);
      }

      //Report statistics
      else if(c=='r'){
        int c = 0;
        int m = 0;
        int n = 0;

        //Find number of nodes
        c = count(root);
        //Find min-depth
        m = minDepth(root);
        //Find max-depth
        n = maxDepth(root);

        printf("Number of nodes in tree: %d\n",c);
        printf("Distance from root to closest null child pointer: %d\n",m-1);
        printf("Distance from root to furthest null child pointer: %d\n",n-1);
        printf("\n");
      }

      //Read next item from file
      c = readChar(com);

      //If end of file, break out of loop
      if(feof(com)){
        break;
      }
    }
    return 0;
  }
  else{
    //while not end of text file
  	while(1){
      //Remove all punctuation and capitalization
  		removePunct(a);
  		char *b = removeCap(a);

      //Insert root
      if (aroot == NULL){
        apar = insertA(aroot,b);
        aroot = apar;
      }

      //Insert other words from file into bst
      else{
        if(b[0]!='\0'){
          aroot = insertA(aroot,b);
        }
      }

      //Read next item from file
  		a = readNextToken(file);

      //If end of file, break out of loop
  		if(feof(file)){
  			break;
  		}
  	}

    //Open command file
  	FILE* com = fopen (argv[3], "r");

    //Check to see if file is Empty
    bool q = isEmpty(com);

    //If empty, report empty tree
    if(q==true){
      printf("Need arguments in %s!",argv[3]);
      exit(0);
    }

    //Read first command
    char c = readChar(com);

    //While not end of command file
    while(1){
      //Print level order
      if(c=='s'){
        printLevelOrderA(aroot);
        printf("\n");
      }

      //Insert a word into tree
      else if(c=='i'){
        //Read word to insert
        char *d;
        d = (readNextToken(com));

        //Remove punctuation and capitalization
        removePunct(d);
        d = removeCap(d);

        //Reduce large space to a signle space
        replaceSpace(d);

        //Insert read word
        if(d[0]!='\0'){
          apar = insertA(aroot,d);
        }
      }

      //Delete a word from tree
      else if(c=='d'){
        //Read word to delete
        char *d = readNextToken(com);

        //Reduce large space to a signle space
        replaceSpace(d);

        //Delete read word
        aroot = deleteNodeA(aroot, d);
      }

      //Report occurences
      else if(c=='f'){
        //Read word to find
        char *d = readNextToken(com);

        //Reduce large space to a signle space
        replaceSpace(d);

        //Search tree for node to access occurences
        searchTreeA(aroot,d);
      }

      //Report statistics
      else if(c=='r'){
        int c = 0;
        int m = 0;
        int n = 0;

        //Find number of nodes
        c = countA(aroot);
        //Find min-depth
        m = minDepthA(aroot);
        //Find max-depth
        n = maxDepthA(aroot);

        printf("Number of nodes in tree: %d\n",c);
        printf("Distance from root to closest null child pointer: %d\n",m-1);
        printf("Distance from root to furthest null child pointer: %d\n",n-1);
        printf("\n");
      }

      //Read next item from file
      c = readChar(com);

      //If end of file, break out of loop
      if(feof(com)){
        break;
      }
    }
    return 0;
  }
}
