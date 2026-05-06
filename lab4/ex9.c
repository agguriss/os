/* Παράδειγμα Β3 */
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define NUM_THREADS 5

void *search(void *arg);
void print_it(void *arg);

pthread_t threads[NUM_THREADS];
pthread_mutex_t lock;
int tries;

int main(int argc, char **argv) {
  (void)argc;
  (void)argv;

  int i;
  int pid;

  pid = getpid();

  printf("Αναζήτηση του αριθμού = %d...\n", pid);

  pthread_mutex_init(&lock, NULL);

  for (i = 0; i < NUM_THREADS; i++) {
    pthread_create(&threads[i], NULL, search, (void *)(long)pid);
  }

  for (i = 0; i < NUM_THREADS; i++) {
    pthread_join(threads[i], NULL);
  }

  printf("Οι προσπάθειες που έγιναν για να βρεθεί ο αριθμός είναι %d.\n",
         tries);

  pthread_mutex_destroy(&lock);

  return 0;
}

void print_it(void *arg) {
  int *try = (int *)arg;
  pthread_t tid;

  tid = pthread_self();

  printf("Το νήμα %lu ακυρώθηκε στην %d προσπάθειά του.\n", (unsigned long)tid,
         *try);
}

void *search(void *arg) {
  int num = (int)(long)arg;
  int i, j, ntries;
  pthread_t tid;

  tid = pthread_self();

  pthread_mutex_lock(&lock);
  srand((unsigned int)(unsigned long)tid);
  i = rand() & 0xFFFFFF;
  pthread_mutex_unlock(&lock);

  ntries = 0;

  pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
  pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);

  pthread_cleanup_push(print_it, (void *)&ntries);

  while (1) {
    i = (i + 1) & 0xFFFFFF;
    ntries++;

    if (num == i) {
      while (pthread_mutex_trylock(&lock) == EBUSY) {
        pthread_testcancel();
      }

      tries = ntries;

      printf("Το νήμα %lu βρήκε τον αριθμό!\n", (unsigned long)tid);

      for (j = 0; j < NUM_THREADS; j++) {
        if (!pthread_equal(threads[j], tid)) {
          pthread_cancel(threads[j]);
        }
      }

      pthread_mutex_unlock(&lock);
      break;
    }

    if (ntries % 100 == 0) {
      pthread_testcancel();
    }
  }

  pthread_cleanup_pop(0);

  return NULL;
}