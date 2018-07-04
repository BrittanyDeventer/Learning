/*************************************************
* utility.h
*
* Library of useful functions (build/use trie)
* Brittany Deventer
**************************************************/
/*****Creating a Trie********/
/*prototypes*/

/*Creates a new node*/
struct node* create_node();

/*Inserts keys (strings from dictionary) into the trie*/
void insert(char key[]);

/* Search function for use in check function*/
bool search(char key[]);
