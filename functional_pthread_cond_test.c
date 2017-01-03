#include "functional_pthread_cond_test.h"

TestThread* test_thread_alloc(TestThread *test_thread);

TestThread* test_thread_get_toplevel(TestThread *test_thread);

void test_thread_set_sync_all(TestThread *test_thread, int tic);
int test_thread_is_tree_ready(TestThread *test_thread);

TestThread* test_thread_main_loop_alloc();
TestThread* test_thread_midi_poll_alloc();
TestThread* test_thread_audio_processing_alloc();
TestThread* test_thread_channel_processing_alloc();
TestThread* test_thread_soundcard_poll_alloc();
TestThread* test_thread_ui_processing_alloc();

void* test_thread_main_loop_run(void *ptr);
void* test_thread_midi_poll_run(void *ptr);
void* test_thread_audio_processing_run(void *ptr);
void* test_thread_channel_processing_run(void *ptr);
void* test_thread_soundcard_poll_run(void *ptr);
void* test_thread_ui_processing_run(void *ptr);

pthread_mutex_t *test_thread_tree_mutex = NULL;

TestThread*
test_thread_alloc(TestThread *test_thread)
{
}

TestThread*
test_thread_get_toplevel(TestThread *test_thread)
{
  if(test_thread == NULL){
    return(NULL);
  }
  
  while(test_atomic_pointer_get(&(thread->parent)) != NULL){
    thread = test_atomic_pointer_get(&(thread->parent));
  }

  return(thread);
}

void
test_thread_set_sync_all(TestThread *test_thread, int tic)
{
  TestThread *main_loop;

  auto void test_thread_set_sync_all_recursive(TestThread *thread, int tic);
  TestThread *child;

  guint next_tic;
  guint flags;
  gboolean waiting;

  waiting = FALSE;

  pthread_mutex_lock(thread->sync_mutex);

  flags = test_atomic_uint_get(&(thread->flags));

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
	test_atomic_uint_and(&(thread->flags),
			     (~TEST_THREAD_WAIT_0));
      }
    }
    break;
  case 1:
    {
      if((TEST_THREAD_WAIT_1 & flags) != 0){
	test_atomic_uint_and(&(thread->flags),
			     (~TEST_THREAD_WAIT_1));
      }
    }
    break;
  case 2:
    {
      if((TEST_THREAD_WAIT_2 & flags) != 0){
	test_atomic_uint_and(&(thread->flags),
			     (~TEST_THREAD_WAIT_2));
      }
    }
    break;
  }

  /* signal waiting thread */
  test_atomic_uint_and(&(thread->flags),
		       (~TEST_THREAD_WAITING));

  if((TEST_THREAD_WAITING & (test_atomic_uint_get(&(thread->flags)))) != 0){
    pthread_cond_signal(thread->sync_cond);
  }    

  thread->current_tic = next_tic;

  /*  */
  pthread_mutex_unlock(thread->sync_mutex);

  /* descend the tree */
  child = test_atomic_pointer_get(&(thread->children));

  while(child != NULL){
    test_thread_set_sync_all_recursive(child, tic);
      
    child = test_atomic_pointer_get(&(child->next));
  }
}

/* entry point */
main_loop = test_thread_get_toplevel(thread);

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

  main_loop = (TestThread *) malloc(sizeof(test_thread));

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

  midi_poll = (TestThread *) malloc(sizeof(test_thread));

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

  audio_processing = (TestThread *) malloc(sizeof(test_thread));

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

  channel_processing = (TestThread *) malloc(sizeof(test_thread));

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

  soundcard_poll = (TestThread *) malloc(sizeof(test_thread));

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

  ui_processing = (TestThread *) malloc(sizeof(test_thread));

  //TODO:JK: implement me

  return(ui_processing);
}

void*
test_thread_main_loop_run(void *ptr)
{
  //TODO:JK: implement me
}

void*
test_thread_midi_pool_run(void *ptr)
{
  //TODO:JK: implement me
}

void*
test_thread_audio_processing_run(void *ptr)
{
  //TODO:JK: implement me
}

void*
test_thread_channel_processing_run(void *ptr)
{
  //TODO:JK: implement me
}

void*
test_thread_soundcard_poll_run(void *ptr)
{
  //TODO:JK: implement me
}

void*
test_thread_ui_processing_run(void *ptr)
{
  //TODO:JK: implement me
}

int
main(int argc, char **argv)
{
  //TODO:JK: implement me

  return(0);
}
