#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void
print_array (int *array, int nmemb)
{
  for (int i = 0; i < nmemb; i++)
    {
      printf ("%d, ", array[i]);
    }
}

void
bubble_sort (int *array, int nmemb)
{
  for (int i = 0; i < nmemb - 1; i++)
    {
      for (int j = 0; j < nmemb - 1 - i; j++)
        {
          if (array[j] > array[j + 1])
            {
              int temp = array[j];
              array[j] = array[j + 1];
              array[j + 1] = temp;
            }
        }
    }
}

void
selection_sort (int *array, int nmemb)
{
  int copy_of_j;
  for (int i = 0; i < nmemb - 1; i++)
    {
      int min = array[i];
      for (int j = i + 1; j < nmemb; j++)
        {
          if (array[j] < min)
            {
              min = array[j];
              copy_of_j = j;
            }
        }
      int temp = array[i];
      array[i] = min;
      array[copy_of_j] = temp;
    }
}

void
insertion_sort (int *array, int nmemb)
{
  if (nmemb == 1)
    return;

  int copy_of_j;
  for (int i = 1; i < nmemb; i++)
    {
      int key = array[i];
      int j = i - 1;
      while (j >= 0 && array[j] > key)
        {
          array[j + 1] = array[j];
          j--;
        }
      array[j + 1] = key;
    }
}

int
main (int argc, char **argv)
{
  int array[argc - 1];
  for (int i = 1; i < argc; i++)
    {
      array[i - 1] = (int)strtol (argv[i], NULL, 10);
    }
  // selection_sort (array, argc - 1);
  // bubble_sort (array, argc - 1);
  insertion_sort (array, argc - 1);
  print_array (array, sizeof (array) / sizeof (int));
  return 0;
}
