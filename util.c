/*******************************************************
* Util.c
*
* Library of useful functions (tries)
* Brittany Deventer
********************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "util.h"

#define ALPHA 27


int main (void)
{
    insert("by");
    insert("don't");
    insert("bee");
    insert("do");
    
    search("bee");
    if(search("bee") == true)
    {
        printf("found bee!\n");
    }
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
} node;

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
bool search(char key[])
{
    struct node *p = root;
    int length = strlen(key);
    int level;
    int index;
    
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
/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    free(d);
    if(!free)
    {
        return false;
    }
    free(p);
    if(!free)
    {
        return false;
    }
    free(root);
    if(!free)
    {
        return false;
    }
    free(s);
    if(!free)
    {
        return false;
    }
    
    return true;
    printf("UNLOAD complete\n");
}

/**
* Free's each node within a trie dictionary
*/
void freeTrie(node* current)
{
    current = root;
    int count = 0;
    
    for(int i = ALHPA, i >= ALPHA, i--)
    {
        //iterate to the end of the trie ... level 27
        if(current->children[i] == NULL)
        {
            count++;
            node *temp = current; // point temp at whats to be freed
            current = current->children[i-1];// point current to the index one to the left (26, 25...)
            free(temp);// free what's stored at temp
        }
        else
        {
            counter = counter->children[index];
        }
    }
}

/**
* Free's each node within a trie dictionary
*/
bool freeTrie(node* current)
{
    int count = 0;
    int p = ALPHA-1;
    printf("where's the problem?\n");
    //start in the last index of root node
    for(int i = ALPHA; i > 0; i--)
    {
        //points to last index in root node
        current = current->children[p];
        if (current->children[p] != NULL)
        {
        
        //Once at the 
        for(int n = 0; n < p; n++)
        {
            printf("here?\n");
            //still pointing at 
            if(current->children[] != NULL)
            {
                count++;
                current = current->children[i-1];
            }
            // Get to the bottom of the branch

            //when you find the end of the branch
            else
            {
                //node *temp = current; // point temp at whats to be freed
                current = root;
                // free what's stored at temp
                //free(temp);
            }
        }
       } //need to get to the end of each root index then return to the next root index one to the left
    }
    if(root == NULL)
    {
        
        //free(root);
        return true;
        
    }
    free(current);
    return false;

    
}

/*****************
* Notes:
* 10/28: trie seems to be working!! Even the apostrophe has been taken care of.  Don't know if these arguments correspond to those in speller.c
* 10/29: search function seems to be working!! (have not checked with gdb)
*****************/



        // we must have found a whole word
        else if (index > 0)
        {
            // terminate current word
            word[index] = '\0';

            // update counter
            words++;

            // check word's spelling
            getrusage(RUSAGE_SELF, &before);
            bool misspelled = !check(word);
            getrusage(RUSAGE_SELF, &after);

            // update benchmark
            time_check += calculate(&before, &after);

            // print word if misspelled
            if (misspelled)
            {
                printf("%s\n", word);
                misspellings++;
            }

            // prepare for next word
            index = 0;
        }
