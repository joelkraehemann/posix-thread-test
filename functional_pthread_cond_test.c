#include "functional_pthread_cond_test.h"

TestThread* test_thread_alloc();

TestThread* test_thread_get_toplevel(TestThread *test_thread);

void test_thread_set_sync_all(TestThread *test_thread, int tic);
int test_thread_is_tree_ready(TestThread *test_thread);

TestThread* test_thread_main_loop_alloc();
TestThread* test_thread_midi_poll_alloc();
TestThread* test_thread_audio_processing_alloc();
TestThread* test_thread_channel_processing_alloc();
TestThread* test_thread_soundcard_poll_alloc();
TestThread* test_thread_ui_processing_alloc();

void* test_thread_loop(void *ptr);

void test_thread_main_loop_run(TestThread *test_thread);
void test_thread_midi_poll_run(TestThread *test_thread);
void test_thread_audio_processing_run(TestThread *test_thread);
void test_thread_channel_processing_run(TestThread *test_thread);
void test_thread_soundcard_poll_run(TestThread *test_thread);
void test_thread_ui_processing_run(TestThread *test_thread);

pthread_mutex_t *test_thread_tree_mutex = NULL;

TestThread*
test_thread_alloc()
{
  TestThread *test_thread;
  
  test_thread = (TestThread *) malloc(sizeof(test_thread));

  /* flags */
  test_atomic_uint_set(&(test_thread->flags),
		       0);

  /* sync - conditional lock */
  test_thread->sync_mutex = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
  pthread_mutex_init(test_thread->sync_mutex,
		     NULL);

  test_thread->sync_cond = (pthread_cond_t *) malloc(sizeof(pthread_cond_t));
  pthread_cond_init(test_thread->sync_cond,
		    NULL);
  
  //TODO:JK: implement me

  return(test_thread);
}

TestThread*
test_thread_get_toplevel(TestThread *test_thread)
{
  if(test_thread == NULL){
    return(NULL);
  }
  
  while(test_atomic_pointer_get(&(test_thread->parent)) != NULL){
    test_thread = test_atomic_pointer_get(&(test_thread->parent));
  }

  return(test_thread);
}

void
test_thread_set_sync_all(TestThread *test_thread, int tic)
{
  TestThread *main_loop;

  auto void test_thread_set_sync_all_recursive(TestThread *test_thread, int tic);

  void test_thread_set_sync_all_recursive(TestThread *test_thread, int tic){
    TestThread *child;

    unsigned int next_tic;
    unsigned int flags;
    int waiting;

    waiting = FALSE;

    pthread_mutex_lock(test_thread->sync_mutex);

    flags = test_atomic_uint_get(&(test_thread->flags));

    /* get next tic and check waiting */
    switch(tic){
    case 0:
      {
	if((TEST_THREAD_WAIT_0 & flags) != 0){
	  next_tic = 1;
	  waiting = TRUE;
	}
      }
      break;
    case 1:
      {
	if((TEST_THREAD_WAIT_1 & flags) != 0){
	  next_tic = 2;
	  waiting = TRUE;
	}
      }
      break;
    case 2:
      {
	if((TEST_THREAD_WAIT_2 & flags) != 0){
	  next_tic = 0;
	  waiting = TRUE;
	}
      }
      break;
    }

    /* unset wait flag */
    switch(tic){
    case 0:
      {
	if((TEST_THREAD_WAIT_0 & flags) != 0){
	  test_atomic_uint_and(&(test_thread->flags),
			       (~TEST_THREAD_WAIT_0));
	}
      }
      break;
    case 1:
      {
	if((TEST_THREAD_WAIT_1 & flags) != 0){
	  test_atomic_uint_and(&(test_thread->flags),
			       (~TEST_THREAD_WAIT_1));
	}
      }
      break;
    case 2:
      {
	if((TEST_THREAD_WAIT_2 & flags) != 0){
	  test_atomic_uint_and(&(test_thread->flags),
			       (~TEST_THREAD_WAIT_2));
	}
      }
      break;
    }

    /* signal waiting thread */
    test_atomic_uint_and(&(test_thread->flags),
			 (~TEST_THREAD_WAITING));

    if((TEST_THREAD_WAITING & (test_atomic_uint_get(&(test_thread->flags)))) != 0){
      pthread_cond_signal(test_thread->sync_cond);
    }    

    test_thread->current_tic = next_tic;

    /*  */
    pthread_mutex_unlock(test_thread->sync_mutex);

    /* descend the tree */
    child = test_atomic_pointer_get(&(test_thread->children));

    while(child != NULL){
      test_thread_set_sync_all_recursive(child, tic);
      
      child = test_atomic_pointer_get(&(child->next));
    }
  }

  /* entry point */
  main_loop = test_thread_get_toplevel(test_thread);

  test_thread_set_sync_all_recursive(main_loop, tic);
}

int
test_thread_is_tree_ready(TestThread *test_thread)
{
  //TODO:JK: implement me
}

/*
 * coordinates threads.
 */
TestThread*
test_thread_main_loop_alloc()
{
  TestThread *main_loop;

  main_loop = test_thread_alloc();

  //TODO:JK: implement me

  return(main_loop);
}

/*
 * does mainly copy buffers.
 */
TestThread*
test_thread_midi_poll_alloc()
{
  TestThread *midi_poll;

  midi_poll = test_thread_alloc();

  //TODO:JK: implement me

  return(midi_poll);
}

/*
 * does coordinate channel processing threads.
 */
TestThread*
test_thread_audio_processing_alloc()
{
  TestThread *audio_processing;

  audio_processing = test_thread_alloc();

  //TODO:JK: implement me

  return(audio_processing);
}

/*
 * does mainly additive mixing.
 */
TestThread*
test_thread_channel_processing_alloc()
{
  TestThread *channel_processing;

  channel_processing = test_thread_alloc();

  //TODO:JK: implement me

  return(channel_processing);
}

/*
 * does mainly copy buffers.
 */
TestThread*
test_thread_soundcard_poll_alloc()
{
  TestThread *soundcard_poll;

  soundcard_poll = test_thread_alloc();

  //TODO:JK: implement me

  return(soundcard_poll);
}

/*
 * the ui thread does basically time consuming tasks. It gets pthread_kill()
 * signals SIGUSR1 and SIGUSR2.
 */
TestThread*
test_thread_ui_processing_alloc()
{
  TestThread *ui_processing;

  ui_processing = test_thread_alloc();

  //TODO:JK: implement me

  return(ui_processing);
}

void*
test_thread_loop(void *ptr)
{
  //TODO:JK: implement me

  pthread_exit(NULL);
}

void
test_thread_main_loop_run(TestThread *test_thread)
{
  //TODO:JK: implement me
}

void
test_thread_midi_pool_run(TestThread *test_thread)
{
  //TODO:JK: implement me
}

void
test_thread_audio_processing_run(TestThread *test_thread)
{
  //TODO:JK: implement me
}

void
test_thread_channel_processing_run(TestThread *test_thread)
{
  //TODO:JK: implement me
}

void
test_thread_soundcard_poll_run(TestThread *test_thread)
{
  //TODO:JK: implement me
}

void
test_thread_ui_processing_run(TestThread *test_thread)
{
  //TODO:JK: implement me
}

int
main(int argc, char **argv)
{
  //TODO:JK: implement me

  return(0);
}
