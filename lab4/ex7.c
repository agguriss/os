/* Παράδειγμα Β1 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *thread_reader_routine(void *arg);
void process_writer_routine(void);

char buffer;
int bufferstatus = 0;
pthread_mutex_t mutex;

int main(void) {
  int retval;
  pthread_t thread;

  pthread_mutex_init(&mutex, NULL);

  retval = pthread_create(&thread, NULL, thread_reader_routine, NULL);

  if (retval == 0) {
    printf("Επιτυχής δημιουργία του νήματος\n");
  } else {
    printf("Σφάλμα στη δημιουργία του νήματος\n");
    exit(1);
  }

  process_writer_routine();

  pthread_join(thread, NULL);
  pthread_mutex_destroy(&mutex);

  return 0;
}

void *thread_reader_routine(void *arg) {
  (void)arg;

  while (1) {
    pthread_mutex_lock(&mutex);

    if (bufferstatus == 1) {
      printf("Ο χαρακτήρας είναι %c\n", buffer);
      bufferstatus = 0;
    }

    pthread_mutex_unlock(&mutex);
  }

  return NULL;
}

void process_writer_routine(void) {
  while (1) {
    pthread_mutex_lock(&mutex);

    if (bufferstatus == 0) {
      printf("Δώσε χαρακτήρα καταχώρησης: ");
      scanf(" %c", &buffer);

      if (buffer == 'e') {
        pthread_mutex_unlock(&mutex);
        exit(0);
      }

      bufferstatus = 1;
    }

    pthread_mutex_unlock(&mutex);
  }
}