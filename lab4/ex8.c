/* Παράδειγμα Β2 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *reader_function(void *arg);
void writer_function(void);

char buffer;
int buffer_has_item = 0;
pthread_mutex_t mutex;

char make_new_item(void) {
  char c;

  printf("Δώσε χαρακτήρα: ");
  scanf(" %c", &c);

  return c;
}

void consume_item(char item) { printf("Ο αναγνώστης διάβασε: %c\n", item); }

int main(void) {
  pthread_t reader;

  pthread_mutex_init(&mutex, NULL);

  pthread_create(&reader, NULL, reader_function, NULL);

  writer_function();

  pthread_join(reader, NULL);
  pthread_mutex_destroy(&mutex);

  return 0;
}

void writer_function(void) {
  while (1) {
    pthread_mutex_lock(&mutex);

    if (buffer_has_item == 0) {
      buffer = make_new_item();

      if (buffer == 'e') {
        pthread_mutex_unlock(&mutex);
        exit(0);
      }

      buffer_has_item = 1;
    }

    pthread_mutex_unlock(&mutex);
    sleep(2);
  }
}

void *reader_function(void *arg) {
  (void)arg;

  while (1) {
    pthread_mutex_lock(&mutex);

    if (buffer_has_item == 1) {
      consume_item(buffer);
      buffer_has_item = 0;
    }

    pthread_mutex_unlock(&mutex);
    sleep(2);
  }

  return NULL;
}