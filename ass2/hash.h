/* * * * * * *
 * Hashing module for Assignment 2.
 *
 * created for COMP20007 Design of Algorithms 2020
 * template by Tobias Edwards <tobias.edwards@unimelb.edu.au>
 * implementation by Joanne Ng (Zi Ying) <zyng@student.unimelb.edu.au>
 */

#ifndef HASH_H
#define HASH_H

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
void read_input_strings(char ***strings, int *n_str, int *hash_size);

/*
 * convert character into integer
 */
int char_to_int(char c);

/*
 * hash function for strings 
 */
int hash_string(char **string, int *hash_size);

/*
 * free memory in array 
 */ 
void free_memory(char ***arr, int *size);

/*
 * main program for problem 1a
 */ 
void problem_1_a();

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
void initialize_hash_table(char ***hash_table, int *size);

/*
 * print hash table in specified format 
 */ 
void printf_hash(char ***hash_table, int *size);

/*
 * add string to hash table at specified location if it is empty
 */
int add_to_hash(char ***hash_table, char **string, int *hash);

/*
 * resize hash table
 */
void resize_hash_table(char ***hash_table, int *size, int *step);

/*
 * insert string into hash table
 */ 
void insert_string(char ***hash_table, int *size, int *step);

/*
 * main program for problem 1b
 */ 
void problem_1_b();

#endif
