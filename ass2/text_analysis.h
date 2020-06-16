/* * * * * * *
 * Text Analysis module for Assignment 2.
 *
 * created for COMP20007 Design of Algorithms 2020
 * template by Tobias Edwards <tobias.edwards@unimelb.edu.au>
 * implementation by Joanne Ng (Zi Ying) <zyng@student.unimelb.edu.au>
 */

#ifndef TEXT_ANALYSIS_H
#define TEXT_ANALYSIS_H

typedef struct trie Trie; 

typedef struct trieNode TrieNode; 

struct trie {
    TrieNode *root;
    int height; 
};

struct trieNode {
    char key; 
    int value; 
    TrieNode **children; 
};

// Create a new empty string
char *new_string();

// Create a new empty Trie and return a pointer to it
Trie *new_trie();

// Free the memory associated with a Trie recursively
void free_node(TrieNode *node);

// Iniitialize array of children for node 
TrieNode **init_children();

// Create a new Node with a given piece of data
TrieNode *new_node(char key, int value);

// get position of char in array of children of a TrieNode
int get_pos(char c);

// insert a character as a child of a TrieNode 
void trie_insert_node(TrieNode *node, char c);

// Add a new word into the trie 
void trie_insert(Trie *trie, char *string);

// print node in trie
void print_node(TrieNode *node);

// return maximum of two integers 
int max(int a, int b);

// Pre-order traversal of a trie
void pre_order_traversal(TrieNode *node);

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

void problem_2_a();

// recursively prints every word and its frequency in a character level trie 
void word_freq_traversal(TrieNode *node, char *string, int k);

// prints all prefixes of a fixed length and their frequencies
void get_prefixes(TrieNode *root, int str_len);

// recursively build count of prefixes 
void build_prefixes(Trie *prefix_trie, TrieNode *node, char *string, 
    int str_len, int k);

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
void problem_2_b();

// checks if a string starts with a given prefix 
int starts_with(char *prefix, char *string);

// scans input strings from stdin and adds them to the trie if they
// begin with the required word
Trie *build_suggestion_trie(int n_string, char *word_stub, int *n_words);

// inserts words from a trie of suggestion words into an array
// of character level tries based on frequency
void word_freq(Trie **freq_trie, TrieNode *node, char *string, int k);

// recursively prints suggestions as well as their probabilities until 
// a maximum number of suggestions have been printed
void suggestion_traversal(TrieNode *node, char *string, int k, double prob, 
    int *n_suggestions);

// helper function to determine the top suggestions in decreasing
// order of frequency, by traversing the tries in the array of
// tries by frequency 
void get_suggestions(Trie **freq_tries, TrieNode *root, int n_words);

// determine and print suggestions based on the trie of 
// possible words 
void print_suggestions(TrieNode *root, int n_words);

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
void problem_2_c();

#endif
