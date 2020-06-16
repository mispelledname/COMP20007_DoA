/* * * * * * *
 * Text Analysis module for Assignment 2.
 *
 * created for COMP20007 Design of Algorithms 2020
 * template by Tobias Edwards <tobias.edwards@unimelb.edu.au>
 * implementation by Joanne Ng (Zi Ying) <zyng@student.unimelb.edu.au>
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "text_analysis.h"

#define MAX_CHAR 99
#define MAX_CHILDREN 27 // 26 lowercase alphabets and one end string char 
#define START_STRING '^'
#define END_STRING '$'
#define FIRST_CHAR 'a'
#define CHAR_OFFSET 1
#define CHAR_ARR_END '\0'
#define INIT_NODE_VAL 1
#define END_STRING_POS 0
#define MAX_SUGGESTIONS 5

// Create a new empty string
char *new_string() {
  return (char*) malloc((MAX_CHAR+1) * sizeof(char*));
}

// Create a new empty Trie and return a pointer to it
Trie *new_trie() {
  Trie *trie; 
  trie = malloc(sizeof(Trie));
  assert(trie);
  trie->root = NULL;
  trie->height = 0; 
  return trie; 
}

// Free memory associated with a Trie 
void free_trie(Trie *trie) {
  free_node(trie->root);
  free(trie);
}

// Free the memory associated with a Trie recursively
void free_node(TrieNode *node) {
  int i;
  if (node == NULL) {
    return; 
  }
  // remove all nodes
  for (i=0; i<MAX_CHILDREN; i++) {
    if (node->children != NULL && node->children[i] != NULL) {
      free_node(node->children[i]);
    }
  }
  if (node->children != NULL) {
    free(node->children);
  }
  free(node);
}

// Iniitialize array of children for node 
TrieNode **init_children() {
  int i;
  TrieNode **children;
  children = (TrieNode**) malloc((MAX_CHILDREN+1) * sizeof(TrieNode**));
  for (i=0; i<MAX_CHILDREN; i++) {
    children[i] = NULL; 
  }
  return children; 
}

// Create a new Node with a given piece of data
TrieNode *new_node(char key, int value) {
  TrieNode *node; 
  node = malloc(sizeof(TrieNode));
  assert(node);
  node->children = NULL; 
  node->key = key;
  node->value = value; 
  return node; 
}

// get position of char in array of children of a TrieNode
int get_pos(char c) {
  if (c == END_STRING) {
    return END_STRING_POS;
  }
  return (c - FIRST_CHAR + CHAR_OFFSET); 
}

// insert a character as a child of a TrieNode 
void trie_insert_node(TrieNode *node, char c) {
  int pos; 
  pos = get_pos(c);
  if (node->children==NULL) {
    node->children = init_children();
  } 
  if (node->children[pos] == NULL) {
    node->children[pos] = new_node(c, INIT_NODE_VAL); 
  }
  else {
    node->children[pos]->value++; 
  }
}

// return maximum of two integers 
int max(int a, int b) {
  if (a >= b) {
    return a;
  }
  return b;
}

// Add a new word into the trie 
void trie_insert(Trie *trie, char *string) {
  char c;
  int i;
  TrieNode *curr; 
  i = 0; 
  // initialize root if new trie 
  if (trie->root==NULL) {
    trie->root = new_node(START_STRING, INIT_NODE_VAL);
  } else {
    trie->root->value++;
  }
  curr = trie->root;
  // insert characters into trie 
  while ((c=string[i]) != CHAR_ARR_END) {
    trie_insert_node(curr, c);
    curr = curr->children[get_pos(c)];
    i++;
  }
  // add end string char
  trie_insert_node(curr, END_STRING);
  trie->height = max(trie->height, i);
}

// print node in trie
void print_node(TrieNode *node) {
  assert(node);
  printf("%c\n", node->key);
}

// Pre-order traversal of a trie
void pre_order_traversal(TrieNode *node) {
  int i;
  print_node(node);
  for (i=0; i<MAX_CHILDREN; i++) {
    if (node->children != NULL && node->children[i] != NULL) {
      pre_order_traversal(node->children[i]);
    }
  }
}

// scans input of strings and builds a character level trie
Trie *build_trie(int n_strings) {
  int i; 
  char *string;
  Trie *trie;
  string = new_string();
  trie = new_trie();
  // insert strings into trie 
  for (i=0; i<n_strings; i++) {
    scanf("%s\n", string);
    trie_insert(trie, string);
  }
  free(string);
  return trie; 
}

// Build a character level trie for a given set of words.
//
// The input to your program is an integer N followed by N lines containing
// words of length < 100 characters, containing only lowercase letters.
//
// Your program should built a character level trie where each node indicates
// a single character. Branches should be ordered in alphabetic order.
//
// Your program must output the pre-order traversal of the characters in
// the trie, on a single line.
void problem_2_a() {
  int n_string; 
  Trie *trie;
  scanf("%d\n", &n_string);
  trie = build_trie(n_string);
  pre_order_traversal(trie->root);
  free_trie(trie);
}

// recursively prints every word and its frequency in a character level trie 
void word_freq_traversal(TrieNode *node, char *string, int k) {
  char c;
  int i;
  c = node->key;
  // recurse deeper until reach end of node 
  if (c!=END_STRING) {
    // add char to current string
    if (c != START_STRING) {
      string[k++] = c;
      string[k] = CHAR_ARR_END;
    }
    // iteratively recurse through children of node 
    for (i=0; i<MAX_CHILDREN; i++) {
      if (node->children!=NULL && node->children[i]!=NULL) {
        word_freq_traversal(node->children[i], string, k);
      }
    }
  }
  // print if reach end of a word 
  else {
    printf("%s %d\n", string, node->value);
  }
}

// prints all prefixes of a fixed length and their frequencies
void get_prefixes(TrieNode *root, int str_len) {
  int i;
  char *string;
  char *another_string; 
  Trie *prefix_trie; 
  // fill in tree of prefixes 
  string = new_string();
  prefix_trie = new_trie();
  for (i=0; i<MAX_CHILDREN; i++) {
    if (root->children!=NULL && root->children[i]!=NULL) {
      build_prefixes(prefix_trie, root->children[i], string, str_len, 0);
    }
  }
  // traverse tree of prefixes while printing all words 
  another_string = new_string();
  word_freq_traversal(prefix_trie->root, another_string, 0);
  // free all memory 
  free(string);
  free(another_string);
  free_trie(prefix_trie);
}

// recursively build count of prefixes 
void build_prefixes(Trie *prefix_trie, TrieNode *node, char *string, 
  int str_len, int k) {

  int i;
  int j;
  // if reach required prefix length, add to prefix trie 
  if (k == str_len) {
    for (j=0; j<node->value; j++) {
      trie_insert(prefix_trie, string);
    }
    return; 
  }
  // add char to current string 
  string[k++] = node->key;
  string[k] = CHAR_ARR_END;
  // build prefix count with children of node 
  for (i=0; i<MAX_CHILDREN; i++) {
    if (node->children!=NULL && node->children[i]!=NULL) {
      build_prefixes(prefix_trie, node->children[i], string, str_len, k);
    }
  }
}

// Using the trie constructed in Part (a) this program should output all
// prefixes of length K, in alphabetic order along with their frequencies
// with their frequencies. The input will be:
//   n k
//   str_0
//   ...
//   str_(n-1)
// The output format should be as follows:
//   an 3
//   az 1
//   ba 12
//   ...
//   ye 1
void problem_2_b() {
  int n_string;
  int str_len;
  Trie *trie;
  scanf("%d %d\n", &n_string, &str_len);
  trie = build_trie(n_string);
  get_prefixes(trie->root, str_len);
  free_trie(trie);
}

// checks if a string starts with a given prefix 
int starts_with(char *prefix, char *string) {
  int i;
  i = 0;
  while (prefix[i] != CHAR_ARR_END) {
    // early exit if chars differ 
    if (prefix[i] != string[i]) {
      return 0;
    }
    i++;
  }
  return 1;
}

// scans input strings from stdin and adds them to the trie if they
// begin with the required word
Trie *build_suggestion_trie(int n_string, char *word_stub, int *n_words) {
  int i; 
  char *string;
  Trie *trie;
  *n_words = 0; 
  string = new_string();
  trie = new_trie();
  // insert strings into trie if start with word stub
  for (i=0; i<n_string; i++) {
    scanf("%s\n", string);
    if (starts_with(word_stub, string) == 1) {
      trie_insert(trie, string);
      (*n_words)++; 
    } 
  }
  // free memory
  free(string);
  return trie; 
}

// inserts words from a trie of suggestion words into an array
// of character level tries based on frequency
void word_freq(Trie **freq_trie, TrieNode *node, char *string, int k) {
  char c;
  int i;
  int freq; 
  c = node->key;
  if (c!=END_STRING) {
    // add char to current string
    if (c != START_STRING) {
      string[k++] = c;
      string[k] = CHAR_ARR_END;
    }
    // recurse on the node's children alphabetically
    for (i=0; i<MAX_CHILDREN; i++) {
      if (node->children!=NULL && node->children[i]!=NULL) {
        word_freq(freq_trie, node->children[i], string, k);
      }
    }
  }
  // insert into correct trie based on frequency
  else {
    freq = node->value; 
    trie_insert(freq_trie[freq], string);
  }
}

// recursively prints suggestions as well as their probabilities until 
// a maximum number of suggestions have been printed
void suggestion_traversal(TrieNode *node, char *string, int k, double prob, 
  int *n_suggestions) {

  char c;
  int i;
  c = node->key;
  // just return if already printed enough suggestions
  if (*n_suggestions == MAX_SUGGESTIONS) {
    return; 
  }
  // pre-order traversal 
  if (c!=END_STRING) {
    // add char to current string
    if (c != START_STRING) {
      string[k++] = c;
      string[k] = CHAR_ARR_END;
    }
    // recurse on children
    for (i=0; i<MAX_CHILDREN; i++) {
      if (node->children!=NULL && node->children[i]!=NULL) {
        suggestion_traversal(node->children[i], string, k, prob, n_suggestions);
      }
    }
  }
  // print if reach end of a word 
  else {
    printf("%.2f %s\n", prob, string);
    (*n_suggestions)++;
  }
}

// helper function to determine the top suggestions in decreasing
// order of frequency, by traversing the tries in the array of
// tries by frequency 
void get_suggestions(Trie **freq_tries, TrieNode *root, int n_words) {
  int n_suggestions = 0;
  float prob; 
  int i; 
  for (i=n_words-1; i>=0; i--) {
    // traverse if trie is not null
    if (freq_tries[i]->root != NULL) {
      prob = (float) i / n_words; 
      suggestion_traversal(freq_tries[i]->root, new_string(), 0, prob, 
        &n_suggestions);
    }
  }
}

// determine and print suggestions based on the trie of 
// possible words 
void print_suggestions(TrieNode *root, int n_words) {
  int i;
  Trie **freq_tries; 
  // initialize array of empty tries 
  freq_tries = (Trie**) malloc((n_words+1) * sizeof(Trie**));
  for (i=0; i<n_words; i++) {
    freq_tries[i] = new_trie();
  }
  // each trie contains words of its index's frequency 
  word_freq(freq_tries, root, new_string(), 0);
  // get the top 5 suggestions 
  get_suggestions(freq_tries, root, n_words);
  // free all memory
  for (i=0; i<n_words; i++) {
    free_trie(freq_tries[i]);
  }
  free(freq_tries);
}

// Again using the trie data structure you implemented for Part (a) you will
// provide a list (up to 5) of the most probable word completions for a given
// word stub.
//
// For example if the word stub is "al" your program may output:
//   0.50 algorithm
//   0.25 algebra
//   0.13 alright
//   0.06 albert
//   0.03 albania
//
// The probabilities should be formatted to exactly 2 decimal places and
// should be computed according to the following formula, for a word W with the
// prefix S:
//   Pr(word = W | stub = S) = Freq(word = W) / Freq(stub = S)
//
// The input to your program will be the following:
//   n
//   stub
//   str_0
//   ...
//   str_(n-1)
// That is, there are n + 1 strings in total, with the first being the word
// stub.
//
// If there are two strings with the same probability ties should be broken
// alphabetically (with "a" coming before "aa").
void problem_2_c() {
  int n_string;
  int n_words; 
  Trie *trie; 
  char *word_stub;  
  word_stub = new_string();
  scanf("%d\n", &n_string);
  scanf("%s\n", word_stub);
  trie = build_suggestion_trie(n_string, word_stub, &n_words);
  print_suggestions(trie->root, n_words);
  free_trie(trie);
}
