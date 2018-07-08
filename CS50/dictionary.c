/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 * Brittany Deventer
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"

#define alphabet 26


/**
* Setup trie structure and necessary functions for use in LOAD function.
* Sources:
* http://programminggeeks.com/c-code-for-radix-tree-or-trie/
*/
 // define node structure
typedef struct node
{
    bool is_word;
    struct node *children[ALPHA];
}node;


//declare root node TBM
struct node *root = NULL;
//declare current node TBM
struct node *current = NULL;
//declare counter variable
unsigned int counter = 0;


/*Creates a new node*/
struct node* create_node()
{
    //make all elements of children array == NULL
    struct node *p = (struct node*)calloc(1, sizeof(struct node));
    for(int i=0; i<ALPHA; i++)
    {
        p->children[i] = NULL;
    }
    //initialize word to false
    p->is_word = false;
    //function returns a pointer, p, to a struct, size node, with all elements of the node initialized
 
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

    //point current to root node
    current = root;    
    
    //iterate through the word
    for(level = 0; level <= length; level++) 
    {
        //at each level, find index to the corresponding character
        if(key[level] == '\n') //if end of word
        {
            current->is_word = true;
            break;
        }
        else if(key[level] != '\'') //if regular alphabetic character
        {
            index = tolower(key[level]) - 'a';
            
            if(current->children[index] == NULL)
            {          
                //create a new node within this index
                current->children[index] = create_node();
            }
            
            //move to the next level 
            current = current->children[index];
    
        }
        else //if character is an apostrophe
        {
            index = 26;
            
            if(current->children[index] == NULL)
            {          
                //create a new node within this index
                current->children[index] = create_node(); 
            }
            
            //move to the next level 
            current = current->children[index];
        }
    }
}

/***
* Search function for use in check function.
* Sources:
* http://programminggeeks.com/c-code-for-radix-tree-or-trie/
****/
bool search(const char key[])
{
    current = root;
    int length = strlen(key);
    int level;
    int index;

    for(level = 0; level < length; level ++)
    {
        //at each level, find index to the corresponding character
        if(key[level] == '\0') //if found word
        {
            break;
        }
        else if(key[level] != '\'') //if regular alphabetic character
        {
            index = tolower(key[level]) - 'a';
            //if index isn't NULL
            if(current->children[index] != NULL)
            {          
                //go to the next node
                current = current->children[index];
            }
            else
            {
                return false;
            }
        }
        else //if character is an apostrophe
        {
            index = 26;
            //if index isn't NULL
            if(current->children[index] != NULL)
            {          
                //go to the next node
                current = current->children[index];
            }
            else
            {
                return false;
            }
        }
    }
    if(key[level] == '\0')
    {
        if(current->is_word == true)
        {
            return true;
        }
    }
    return false;  
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    if(search(word) == true)
    {
        return true;
    }
    else
    {
        return false;
    }   
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    //open dictionary
    FILE *d = fopen(dictionary, "r");
    if(d == NULL)
    {
        printf("load function could not load dictionary file\n"); 
        return false;
    }

    char key[LENGTH + 2];
    char *s = key;
    //iterate through dictionary 
    while(fgets(s, LENGTH + 2, d) != NULL)
    {
        //run insert function to insert string to the trie
        insert(s);
        counter ++;
    }
    fclose(d);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return counter;   
}

/**
* Free's each node within a trie dictionary
*/
void freeTrie(struct node* ptr)
{
    //iterate through root node
    for(int i = 0; i < ALPHA; i++)
    {
        //check if index has NULL pointer
        if(ptr->children[i] != NULL)
        {
            //if so, move ptr to next level and check again
            freeTrie(ptr->children[i]);
        }
    }
    // once found bottom of branch, free ptr
    free(ptr);
    return; 
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{   
    //store root in temp node
    node* temp = root;
    //run root through unload function
    freeTrie(temp);
    return true;
}

