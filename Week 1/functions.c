/*
 * Starter file for Week 2 Question 2.
 *
 * Created for COMP20007 Design of Algorithms 2020
 * Template written by Tobias Edwards <tobias.edwards@unimelb.edu.au>
 * Implementation by YOUR NAME HERE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
 * Recall, these are called function prototypes and they declare the function
 * names, argument types and return types that will be implemented in this file.
 */

/* Takes numbers x and y and returns their product, i.e., x times y. */
double product(double x, double y);

/*
 * Takes integers a and b and prints "a + b = c" to the terminal,
 * where a, b and c are replaced by the appropriate values.
 */
void print_sum(int a, int b);

/* Increase the integer which is pointed to by the pointer ptr by k. */
void increase_by_k(int *ptr, int k);

/* Find the maximum value in the array arr, which has length n. */
int max_in_array(int *arr, int n);

/*
 * Return the length of the null terminated string str, without using the
 * strlen function from the string.h library.
 */
int my_strlen(char *str);

/*
 * The following functions run some tests to confirm the corresponding
 * functions work as expected.
 */

/* Test the product() function. */
void test_product();

/* Test the print_sum() function. */
void test_print_sum();

/* Test the increase_by_k() function. */
void test_increase_by_k();

/* Test the max_in_array() function. */
void test_max_in_array();

/* Test the my_strlen() function. */
void test_my_strlen();

/*
 * This is the main function, which is the entry point to your program.
 *
 * Recall that argc is the number of command line arguments, and argv
 * is an array of those arguments (an array of pointers to null terminated
 * strings).
 */
int main(int argc, char **argv) {

  test_product();
  test_print_sum();
  test_increase_by_k();
  test_max_in_array();
  test_my_strlen();

  /*
   * All main functions should finish with return 0, indicating that the
   * program exited successfully. Otherwise, a non-zero status code should be
   * returned.
   */
  return 0;
}

/* Test the product() function. */
void test_product() {
  printf("testing product() function\n---\n");
  /* Note: we should really be #defining these magic numbers. */
  printf("product(100, 3.25) = %lf\n", product(100, 3.25));
  printf("product(2, 2.0007) = %lf\n", product(2, 2.0007));
  printf("---\n\n");
}

/* Test the print_sum() function. */
void test_print_sum() {
  printf("testing print_sum() function\n---\n");
  printf("print_sum(10002, 10005)\n");
  /* Note: we should really be #defining these magic numbers. */
  print_sum(10002, 10005);
  printf("print_sum(10, 0)\n");
  print_sum(10, 0);
  printf("---\n\n");
}

/* Test the increase_by_k() function. */
void test_increase_by_k() {
  int x = 0;

  printf("testing increase_by_k() function\n---\n");
  printf("x = %d\n", x);
  printf("increase_by_k(&x, 3)\n");
  /* Note: we should really be #defining these magic numbers. */
  increase_by_k(&x, 3);
  printf("x = %d\n", x);
  printf("increase_by_k(&x, -50)\n");
  /* Note: we should really be #defining these magic numbers. */
  increase_by_k(&x, -50);
  printf("x = %d\n", x);
  printf("---\n\n");
}

/* Test the max_in_array() function. */
void test_max_in_array() {
/* Note: we should really be #defining these magic numbers. */
  int arr[] = {2, 0, 0, 0, 7, 3, 0, 5, 2, -1, 1, 4, 7};
  int n = 13;

  printf("testing max_in_array() function\n---\n");
  printf("max_in_array(arr, n) = %d\n", max_in_array(arr, n));

  /* Note: we should really be #defining these magic numbers. */
  arr[3] = 100;
  printf("max_in_array(arr, n) = %d\n", max_in_array(arr, n));
  printf("---\n\n");
}

/* Test the my_strlen() function. */
void test_my_strlen() {
  char *subject = "Design of Algorithms";

  printf("testing my_strlen() function\n---\n");
  printf("my_strlen(subject) = %d\n", my_strlen(subject));
  printf("---\n\n");
}


/* ------------------ IMPLEMENT THE FOLLOWING FUNCTIONS -------------------- */

/* Takes numbers x and y and returns their product, i.e., x times y. */
double product(double x, double y) {
  /* YOUR CODE HERE */
  double prod = x * y;
  return prod;
}

/*
 * Takes integers a and b and prints "a + b = c" to the terminal,
 * where a, b and c are replaced by the appropriate values.
 */
void print_sum(int a, int b) {
  /* YOUR CODE HERE */
  int c = a + b;
  printf("%d + %d = %d\n", a, b, c);
}

/* Increase the integer which is pointed to by the pointer ptr by k. */
void increase_by_k(int *ptr, int k) {
  /* YOUR CODE HERE */
  *ptr = *ptr + k;
}

/* Find the maximum value in the array arr, which has length n. */
int max_in_array(int *arr, int n) {
  /* YOUR CODE HERE */
  int i;
  int max = arr[0];
  for (i = 0; i < n; i++) {
    if (arr[i] > max) {
        max = arr[i];
    }
  }
  return max;
}

/*
 * Return the length of the null terminated string str, without using the
 * strlen function from the string.h library.
 */
int my_strlen(char *str) {
  /* YOUR CODE HERE */

  /* int n = sizeof(str) / sizeof(str[0]); */

  int n = 1;
  while (str[n] != '\0') {
    n++;
  }
  n++;

  return n;
}
