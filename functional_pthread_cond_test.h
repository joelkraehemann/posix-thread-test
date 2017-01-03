#include <stdlib.h>

#include <pthread.h>

typedef struct _TestThread TestThread;

typedef enum{
  TEST_THREAD_RT_SETUP                = 1,
  TEST_THREAD_INITIAL_SYNC            = 1 <<  1,
  TEST_THREAD_INITIAL_RUN             = 1 <<  2,
  TEST_THREAD_WAIT_0                  = 1 <<  3,
  TEST_THREAD_WAIT_1                  = 1 <<  4,
  TEST_THREAD_WAIT_2                  = 1 <<  5,
  TEST_THREAD_READY                   = 1 <<  6,
  TEST_THREAD_INTERMEDIATE_PRE_SYNC   = 1 <<  7,
  TEST_THREAD_INTERMEDIATE_POST_SYNC  = 1 <<  8,
}TestThreadFlags;

struct _TestThread
{
  volatile unsigned int flags;

  char *buffer;

  pthread_mutex_t *sync_mutex;
  pthread_cond_t *sync_cond;

  pthread_t *thread;

  volatile TestThread *parent;

  volatile TestThread *next;
  volatile TestThread *prev;

  volatile TestThread *children;
};
