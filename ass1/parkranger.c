/* * * * * * *
 * Park Ranger module for Assignment 1
 *
 * created for COMP20007 Design of Algorithms 2020
 * template by Tobias Edwards <tobias.edwards@unimelb.edu.au>
 * implementation by Joanne (Zi Ying) Ng <zyng@student.unimelb.edu.au>
 */

#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "parkranger.h"
#include "util.h"
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
//   0 1                         /  2
//   0 2                        / /
//   2 1                        1
//   1 3                          \
//                                 3
//
// In this example your program should return `true` as there is a way to trim
// all trees in a single run. This run is (0, 2, 1, 3).
//
// Your function should must:
//  - Read in this data from stdin
//  - Store this data in an appropriate data structure
//  - Run the algorithm you have designed to solve this problem
//  - Do any clean up required (e.g., free allocated memory)
//  - Return `true` or `false` (included in the stdbool.h library)
//
// For full marks your algorithm must run in O(n + m) time.

bool is_single_run_possible() {
  
  // initialize variables 
  int n_nodes;
  int n_edges;
  Deque **adj;
  Deque *nodes;

  // build adjacency list from inputs
  scanf_input(&n_nodes, &n_edges, &adj);

  // sort nodes in topological order
  dfs_topological_sort(&adj, &nodes, &n_nodes);

  // check if run is possible
  bool answer = check_run(&adj, &nodes, &n_nodes);

  // free memory
  free_adj_list(&adj, &n_nodes);
  free_deque(nodes);

  return answer;
}

// Read in the input and construct an adjacency list of the graph
void scanf_input(int *n_nodes, int *n_edges, Deque ***adj) {
  int i;
  int node;
  int adj_node;
  
  scanf("%d %d\n", n_nodes, n_edges);
  *adj = malloc(sizeof(Deque) * (*n_nodes+1));
  
  // initialize deques for each node
  for (i=0; i<=*n_nodes; i++) {
    (*adj)[i] = new_deque();
  }
  
  // read in each edge 
  for (i=0; i<*n_edges; i++) {
    scanf("%d %d\n", &node, &adj_node);
    deque_insert((*adj)[node], adj_node);
  }
}

// Topologically sort the nodes in the graph using Depth-First-Search,
// by noting the order in which nodes are popped off the stack.
void dfs_topological_sort(Deque ***adj, Deque **nodes, int *n_nodes) {
  int i;
  int v;
  
  // array of topologically sorted nodes
  *nodes = new_deque();

  // keep track of which nodes have been visited
  int *visited = malloc(sizeof(int) * (*n_nodes+1));
  for (i=0; i<=*n_nodes; i++) {
    visited[i] = 0;
  }

  // traversal stack
  Deque *trav_stack = new_deque(); 
  deque_insert(trav_stack, 0);
  while (trav_stack->size != 0) {
    v = trav_stack->top->data;
    dfs_explore(v, adj, nodes, n_nodes, &visited, &trav_stack);
  }

  // free memory
  free_deque(trav_stack);
  free(visited);
}

// Recursive function to topologically sort the nodes by DFS
void dfs_explore(int v, Deque ***adj, Deque **nodes, int *n_nodes, int **visited, Deque **trav_stack) {
  int w;

  (*visited)[v] = 1;
  Node *curr = (*adj)[v]->top;

  while (curr != NULL) {
    w = curr->data;
    // keep going deeper into graph
    if ((*visited)[w] == 0) {
      deque_push(*trav_stack, w);
      dfs_explore(w, adj, nodes, n_nodes, visited, trav_stack);
    }
    curr = curr->next;
  }
  deque_push(*nodes, deque_pop(*trav_stack));
}

// Check if a single run is possible
bool check_run(Deque ***adj, Deque **nodes, int *n_nodes) {
  int curr_max = 0;
  int node; 
  int dist; 
  int adj_dist;
  int i;
  Node *adj_node; 

  // initialize all max node distances to zero 
  int *distances = malloc(sizeof(int) * (*n_nodes + 1));
  for (i=0; i<=*n_nodes; i++) {
    distances[i] = 0;
  }

  // go through nodes in topological order
  for (i=0; i<=*n_nodes; i++) {
    
    // graph is disconnected 
    if ((*nodes)->size == 0) {
      break;
    }
    
    node = deque_pop(*nodes);
    adj_node = (*adj)[node]->top;
    dist = distances[node];

    // update the distances
    while (adj_node != NULL) {
      adj_dist = distances[adj_node->data];
      if (adj_dist < dist + 1) {
        distances[adj_node->data] = dist + 1;
        // update max distance 
        if (dist + 1 > curr_max) {
          curr_max = dist + 1;
        }
      }
      adj_node = adj_node->next;
    }
  }

  // free memory
  free_deque(*nodes);
  free_node(adj_node);
  free(distances);

  return (curr_max == *n_nodes);
}

// free memory from adjacency list 
void free_adj_list(Deque ***adj, int *n_nodes) {
  int i;
  for (i=0; i<=*n_nodes; i++) {
    free_deque((*adj)[i]);
  }
  free(*adj);
}