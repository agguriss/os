/* Παράδειγμα Α4 */
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *print_message(void *ptr);

int main(void) {
  int retval;
  pthread_t thread1, thread2;
  char *message1 = "Hello";
  char *message2 = "World";

  pthread_create(&thread1, NULL, print_message, message1);

  retval = pthread_join(thread1, NULL);

  if (retval != 0) {
    printf("Σφάλμα στην αναμονή του thread1, %d\n", errno);
    abort();
  }

  printf("\nΤο thread1 δημιουργήθηκε και τερμάτισε\n");

  pthread_create(&thread2, NULL, print_message, message2);

  retval = pthread_join(thread2, NULL);

  if (retval != 0) {
    printf("Σφάλμα στην αναμονή του thread2, %d\n", errno);
    abort();
  }

  printf("\nΤο thread2 δημιουργήθηκε και τερμάτισε\n");

  return 0;
}

void *print_message(void *ptr) {
  char *message;

  message = (char *)ptr;
  printf("%s ", message);

  return NULL;
}