/*******************************************************
* Trie_test.c
*
* Stores words in a dictionary of type trie
********************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"

#define ALPHABET 26


int main (void)
{
    insert("by");
    insert("don't");
    
}

/**
* Setup trie structure and necessary functions for use in load/check functions.
* Sources:
* http://programminggeeks.com/c-code-for-radix-tree-or-trie/
*/
 // define node structure
typedef struct node
{
    bool word;
    struct node *children[ALPHA];
}node;

//declare root node
struct node *root = NULL;

/*Creates a new node*/
struct node* create_node()
{
    //malloc some space for this node
    struct node *p = (struct node*)malloc(sizeof(struct node));
    //make all elements of children array == NULL
    for(int i=0; i<ALPHA; i++)
    {
        p->children[i] = NULL;
    }
    //initiate word to false
    p->word = false;
    return p;
} 

/*Inserts keys (strings from dictionary) into the trie*/
void insert(char key[])
{
    int length = strlen(key);
    int index;
    int level;
    
    //creat root node
    if(root == NULL)
    {
        root = create_node(); //root = p
        
    }
    
    struct node *p = root; //now pointer p is pointing to the root node    
    
    //iterate through the word
    for(level = 0; level < length; level++) 
    {
        printf("%c\n", key[level]);
        //at each level, find index to the corresponding character
        if(key[level] != '\'')
        {
            index = tolower(key[level]) - 'a';
        }
        else //if character is an apostrophe
        {
            index = 26;
        }
        
        //if index is NULL
        if(p->children[index] == NULL)
        {          
            //create a new node within this index
            p->children[index] = create_node();
        }
        
        //change to the next level (this will make sure that even if index has already been made, we still move to the next level
        p = p->children[index];
    }
}

/***
* Search function for use in check function.
****/
int search(char key[])
{
    struct node *p = root;
    int length = strlen(key);
    int level;
    
    for(level = 0; level < length; level ++)
    {
        printf("%c\n", key[level]);
        //at each level, find index to the corresponding character
        if(key[level] == '\0') //if end of word
        {
            p->word = true;
        }
        else if(key[level] != '\'') //if regular alphabetic character
        {
            index = tolower(key[level]) - 'a';
        }
        else //if character is an apostrophe
        {
            index = 26;
        }
        
        //if index isn't NULL
        if(p->children[index] != NULL)
        {          
            //go to the next node
            p = p->children[index];
        }
        //otherwise, reached end of word
        else
        {
            //leave the for loop b/c the word has reached NULL
            break;
        }
    }
    
    //if truly reached end of word
    if(key[level] == '\0')
    {
        return true;
    }
    else
    {
        return false;
    }
}


/*****************
* Notes:
* 10/28: trie seems to be working!! Even the apostrophe has been taken care of.  Don't know if these arguments correspond to those in speller.c
*****************/
