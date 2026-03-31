#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define LIMIT 50

struct fibo_entry
{				/* Definition of each table entry */
  int n;
  unsigned long long int lli;	/* 64-bit integer */
  char *str;
};

void
panic (char *m)
{
  fprintf (stderr, "%s\n", m);
  exit (0);
}

void
free_memory (struct fibo_entry *table, int size)
{
/* Your code starts here */
  int i;
  for (i = 0; i < size; i++) {
    free (table[i].str); // free each string
  }
  free (table); // free the entire table
/* Your code ends here */
}

int
main (int argc, char *argv[])
{
  int n;
  int i;
  struct fibo_entry *fibo_table;

  if (argc != 2)
    panic ("wrong parameters");

  n = atoi (argv[1]);
  if (n < 2)
    panic ("n too small");
  if (n > LIMIT)
    panic ("n too big");

/* Your code starts here */
  //Reserve memory for the complete table (n+1 elements)
  fibo_table = (struct fibo_entry *) malloc ((n + 1) * sizeof(struct fibo_entry));
  if (fibo_table == NULL) {
    panic ("malloc failed"); // Check if malloc failed
  }

  // First number of Fibonacci f0 = 0
  fibo_table[0].n = 0;
  fibo_table[0].lli = 0;
  // Calculate the number of digits to reserve the exact string
  int digits = 1;
  fibo_table[0].str = (char *) malloc ((n + 1) * sizeof (char)); // +1 for \0
  if (fibo_table[0].str == NULL) {
    panic ("malloc failed");
  }
  sprintf (fibo_table[0].str, "%llu", fibo_table[0].lli); // Convert to string

  // Second number of Fibonacci f1 = 1
  fibo_table[1].n = 1;
  fibo_table[1].lli = 1;
  digits = (int) log10(fibo_table[1].lli) + 1; // Calculate numbers of digits
  fibo_table[1].str = (char *) malloc ((n + 1) * sizeof (char));
  if (fibo_table[1].str == NULL) {
    panic ("malloc failed");
  }
  sprintf (fibo_table[1].str, "%llu", fibo_table[1].lli);

  // Remainder of Fibonacci series fn = fn-1 + fn-2
  for (int i = 2; i <= n; i++) {
    fibo_table[i].n = i; // save index
    fibo_table[i].lli = fibo_table[i - 1].lli + fibo_table[i - 2].lli; // Calculate Fibonacci
    digits = (int) log10(fibo_table[i].lli) + 1; // Calculate numbers of digits for string
    // Reserve exact memory for the string
    fibo_table[i].str = (char *) malloc ((n + 1) * sizeof (char));
    if (fibo_table[i].str == NULL) {
      panic ("malloc failed");
    }

    // Convert the number to a string
    sprintf (fibo_table[i].str, "%llu", fibo_table[i].lli);
  }
/* Your code ends here */

  for (i = 0; i <= n; i++)
    {
      printf ("%d %llu %s\n", fibo_table[i].n, fibo_table[i].lli,
	      fibo_table[i].str);
    }

  free_memory (fibo_table, n);

  return 0;
}
