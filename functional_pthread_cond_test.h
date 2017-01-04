#include <stdlib.h>

#include <pthread.h>

#define FALSE (0)
#define TRUE (1)

typedef struct _TestThread TestThread;

typedef enum{
  TEST_THREAD_RT_SETUP                = 1,
  TEST_THREAD_INITIAL_SYNC            = 1 <<  1,
  TEST_THREAD_INITIAL_RUN             = 1 <<  2,
  TEST_THREAD_WAIT_0                  = 1 <<  3,
  TEST_THREAD_WAIT_1                  = 1 <<  4,
  TEST_THREAD_WAIT_2                  = 1 <<  5,
  TEST_THREAD_READY                   = 1 <<  6,
  TEST_THREAD_WAITING                 = 1 <<  7,
  TEST_THREAD_INTERMEDIATE_PRE_SYNC   = 1 <<  8,
  TEST_THREAD_INTERMEDIATE_POST_SYNC  = 1 <<  9,
}TestThreadFlags;

struct _TestThread
{
  volatile unsigned int flags;

  int current_tic;
  
  pthread_mutex_t *sync_mutex;
  pthread_cond_t *sync_cond;

  char *buffer;

  pthread_t *thread;

  volatile TestThread *parent;

  volatile TestThread *next;
  volatile TestThread *prev;

  volatile TestThread *children;

  void (*run)(TestThread *test_thread);
};

#define test_atomic_uint_get(atomic)					\
  (__extension__ ({							\
      (void) (0 ? *(atomic) ^ *(atomic) : 0);				\
      __sync_synchronize ();						\
      (unsigned int) *(atomic);						\
    }))
#define test_atomic_uint_set(atomic, newval)				\
  (__extension__ ({							\
      (void) (0 ? *(atomic) ^ (newval) : 0);				\
      *(atomic) = (newval);						\
      __sync_synchronize ();						\
    }))

#define test_atomic_pointer_get(atomic)				\
  (__extension__ ({						\
      __sync_synchronize ();					\
      (void *) *(atomic);					\
    }))
#define test_atomic_pointer_set(atomic, newval)			\
  (__extension__ ({						\
      (void) (0 ? (void *) *(atomic) : 0);			\
      *(atomic) = (__typeof__ (*(atomic))) (gsize) (newval);	\
      __sync_synchronize ();					\
    }))

#define test_atomic_uint_and(atomic, val)				\
  (__extension__ ({							\
      (void) (0 ? *(atomic) ^ (val) : 0);				\
      (unsigned int) __sync_fetch_and_and ((atomic), (val));			\
    }))
#define test_atomic_uint_or(atomic, val)				\
  (__extension__ ({							\
      (void) (0 ? *(atomic) ^ (val) : 0);				\
      (unsigned int) __sync_fetch_and_or ((atomic), (val));			\
    }))
