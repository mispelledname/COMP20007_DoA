/* * * * * * *
 * Park Ranger module for Assignment 1
 *
 * created for COMP20007 Design of Algorithms 2020
 * template by Tobias Edwards <tobias.edwards@unimelb.edu.au>
 * implementation by Joanne (Zi Ying) Ng <zyng@student.unimelb.edu.au>
 */

#ifndef PARKRANGER_H
#define PARKRANGER_H

#include <stdbool.h>
#include "deque.h"

// This function must read in a ski slope map and determine whether or not
// it is possible for the park ranger to trim all of the trees on the ski slope
// in a single run starting from the top of the mountain.
//
// The ski slope map is provided via stdin in the following format:
//
//   n m
//   from to
//   from to
//   ...
//   from to
//
// Here n denotes the number of trees that need trimming, which are labelled
// {1, ..., n}. The integer m denotes the number "reachable pairs" of trees.
// There are exactly m lines which follow, each containing a (from, to) pair
// which indicates that tree `to` is directly reachable from tree `from`.
// `from` and `to` are integers in the range {0, ..., n}, where {1, ..., n}
// denote the trees and 0 denotes the top of the mountain.
//
// For example the following input represents a ski slope with 3 trees and
// 4 reachable pairs of trees.
//
// input:            map:          0
//   3 4                          / \
//   0 1                         /  1
//   0 2                        / /
//   1 2                        2
//   2 3                          \
//                                 3
//
// In this example your program should return `true` as there is a way to trim
// all trees in a single run. This run is (0, 1, 2, 3).
//
// Your function should must:
//  - Read in this data from stdin
//  - Store this data in an appropriate data structure
//  - Run the algorithm you have designed to solve this problem
//  - Do any clean up required (e.g., free allocated memory)
//  - Return `true` or `false` (included in the stdbool.h library)
//
// For full marks your algorithm must run in O(n + m) time.

bool is_single_run_possible();

// Read in the input and construct an adjacency list of the graph
void scanf_input(int *n_nodes, int *n_edges, Deque ***adj);

// Topologically sort the nodes in the graph using Depth-First-Search,
// by noting the order in which nodes are popped off the stack.
void dfs_topological_sort(Deque ***adj, Deque **nodes, int *n_nodes);

// Recursive function to topologically sort the nodes by DFS
void dfs_explore(int v, Deque ***adj, Deque **nodes, int *n_nodes, 
    int **visited, Deque **trav_stack);

// Check if a single run is possible
bool check_run(Deque ***adj, Deque **nodes, int *n_nodes);

// free memory from adjacency list 
void free_adj_list(Deque ***adj, int *n_nodes);

#endif
