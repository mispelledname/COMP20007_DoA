/* 
 * Linked list module implementation.
 * 
 * Written by Joanne (Zi Ying) Ng <zyng@student.unimelb.edu.au>
 */

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

typedef struct{
    int value;
    node *next;
} node;

