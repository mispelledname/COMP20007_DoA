/* * * * * * *
 * Hashing module for Assignment 2.
 *
 * created for COMP20007 Design of Algorithms 2020
 * template by Tobias Edwards <tobias.edwards@unimelb.edu.au>
 * implementation by Joanne Ng (Zi Ying) <zyng@student.unimelb.edu.au>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

#define MAX_STRING_CHAR 256
#define FIRST_CAPITAL_LETTER 'A'
#define LAST_CAPITAL_LETTER 'Z'
#define CAPITAL_LETTER_OFFSET 26
#define FIRST_LOWERCASE 'a'
#define LAST_LOWERCASE 'z'
#define FIRST_NUMERIC '0'
#define NUMERAL_OFFSET 52
#define MAX_HASH_INT 64
#define EMPTY_STRING ""
#define END_STRING_CHAR '\0'

// Implements a solution to Problem 1 (a), which reads in from stdin:
//   N M
//   str_1
//   str_2
//   ...
//   str_N
// And outputs (to stdout) the hash values of the N strings 1 per line.

/* 
 * Read N, M and strings from stdin
 */
void read_input_strings(char ***strings, int *n_str, int *hash_size) {
  int i; 
  scanf("%d %d\n", n_str, hash_size);
  *strings = (char**) malloc((*n_str+1) * sizeof(char**));
  for (i=0; i<*n_str; i++) {
    (*strings)[i] = (char*) malloc((MAX_STRING_CHAR+1) * sizeof(char*));
    scanf("%s\n", (*strings)[i]);
  }
}

/*
 * convert character into integer
 */
int char_to_int(char c) {
  int n;
  // capital letter
  if (c>=FIRST_CAPITAL_LETTER && c<=LAST_CAPITAL_LETTER) {
    n = c - FIRST_CAPITAL_LETTER + CAPITAL_LETTER_OFFSET;
  } 
  // small letter
  else if (c>=FIRST_LOWERCASE && c<=LAST_LOWERCASE) {
    n = c - FIRST_LOWERCASE;
  }
  // numerals
  else {
    n = c - FIRST_NUMERIC + NUMERAL_OFFSET;
  }
  return n;
}

/*
 * hash function for strings 
 */
int hash_string(char **string, int *hash_size) {
  int hash = 0; 
  int i = 0;
  int n; 
  char c;
  // use Horner's rule to calculate hash by character
  while ((*string)[i] != END_STRING_CHAR) {
    c = (*string)[i++];
    n = char_to_int(c);
    hash = hash * MAX_HASH_INT + n;
    hash %= *hash_size;
  }
  return hash; 
}

/*
 * free memory in array 
 */ 
void free_memory(char ***arr, int *size) {
  int i;
  for (i=0; i<*size; i++) {
    free((*arr)[i]);
  }
  free((*arr));
}

/*
 * main program for problem 1a
 */ 
void problem_1_a() {
  char **strings;
  int n_str;
  int hash_size; 
  int i;
  read_input_strings(&strings, &n_str, &hash_size);
  for (i=0; i<n_str; i++) {
    printf("%d\n", hash_string(&strings[i], &hash_size));
  }
  free_memory(&strings, &n_str);
}

// Implements a solution to Problem 1 (b), which reads in from stdin:
//   N M K
//   str_1
//   str_2
//   ...
//   str_N
// Each string is inputed (in the given order) into a hash table with size
// M. The collision resolution strategy must be linear probing with step
// size K. If an element cannot be inserted then the table size should be
// doubled and all elements should be re-hashed (in index order) before
// the element is re-inserted.
//
// This function must output the state of the hash table after all insertions
// are performed, in the following format
//   0: str_k
//   1:
//   2: str_l
//   3: str_p
//   4:
//   ...
//   (M-2): str_q
//   (M-1):

/*
 * initialize hash table
 */ 
void initialize_hash_table(char ***hash_table, int *size) {
  int i;
  *hash_table = (char**) malloc(*size * sizeof(char**));
  for (i=0; i<*size; i++) {
    (*hash_table)[i] = EMPTY_STRING;
  }
}

/* 
 * free memory associated with hash table 
 */
void free_hash_table(char **hash_table, int size) {
  int i;
  for (i=0; i<size; i++) {
    hash_table[i] = NULL;
  }
  free(hash_table);
}

/*
 * print hash table in specified format 
 */ 
void printf_hash(char ***hash_table, int *size) {
  int i;
  for (i=0; i<*size; i++) {
    printf("%d: %s\n", i, (*hash_table)[i]);
  }
}

/*
 * add string to hash table at specified location if it is empty
 */
int add_to_hash(char ***hash_table, char **string, int *hash) {
  if (strcmp((*hash_table)[*hash], EMPTY_STRING) == 0) {
    (*hash_table)[*hash] = *string; 
    return 0;
  }
  return 1;
}

/*
 * resize hash table
 */
void resize_hash_table(char ***hash_table, int *size, int *step) {
  int i;
  int hash; 
  int new_size; 
  char *string; 
  char **new_table; 
  // new hash table is double the size 
  new_size = 2 * (*size);
  initialize_hash_table(&new_table, &new_size);
  // repopulate hash table with items in old hash table 
  for (i=0; i<*size; i++) {
    string = (*hash_table)[i];
    // fill empty slots
    if (strcmp(string, EMPTY_STRING) != 0) {
      hash = hash_string(&string, &new_size);
      // handle collisions with linear probing 
      while (add_to_hash(&new_table, &string, &hash) == 1) {
        hash = (hash + (*step)) % (new_size); 
      }
    }
  }
  // reassign pointers and free memory
  free_hash_table(*hash_table, *size);
  *size = new_size;
  *hash_table = new_table;
}

/*
 * insert string into hash table
 */ 
void insert_string(char ***hash_table, int *size, int *step) {
  int hash, pos;
  char *string;
  // get string and hash 
  string = (char*) malloc((MAX_STRING_CHAR+1) * sizeof(char*));
  scanf("%s\n", string);
  hash = hash_string(&string, size);
  pos = hash; 
  // insert string into an empty spot on hash table using linear probing 
  while (add_to_hash(hash_table, &string, &pos) == 1) {
    pos = (pos + (*step)) % (*size); 
    // no space on hash table 
    if (pos == hash) {
      resize_hash_table(hash_table, size, step);
      hash = hash_string(&string, size);
      pos = hash; 
    } 
  }
}

/*
 * main program for problem 1b
 */ 
void problem_1_b() {
  int N, M, K;
  int i;
  char **hash_table; 
  // read input parameters
  scanf("%d %d %d\n", &N, &M, &K);
  // initialize new hash table 
  initialize_hash_table(&hash_table, &M); 
  // insert strings into hash table 
  for (i=0; i<N; i++) {
    insert_string(&hash_table, &M, &K);
  }
  printf_hash(&hash_table, &M);
  // free memory
  free_hash_table(hash_table, M);
}
