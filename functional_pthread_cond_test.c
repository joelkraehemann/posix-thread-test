#include "functional_pthread_cond_test.h"

void test_thread_set_sync_all(TestThread *test_thread, int tic);
int test_thread_is_tree_ready(TestThread *test_thread);

TestThread* test_thread_main_loop_alloc();
TestThread* test_thread_midi_poll_alloc();
TestThread* test_thread_audio_processing_alloc();
TestThread* test_thread_channel_processing_alloc();
TestThread* test_thread_soundcard_poll_alloc();
TestThread* test_thread_ui_processing_alloc();

void* test_thread_main_loop_run(void *ptr);
void* test_thread_midi_pool_run(void *ptr);
void* test_thread_audio_processing_run(void *ptr);
void* test_thread_channel_processing_run(void *ptr);
void* test_thread_soundcard_poll_run(void *ptr);
void* test_thread_ui_processing_run(void *ptr);

pthread_mutex_t *test_thread_tree_mutex = NULL;

void
test_thread_set_sync_all(TestThread *test_thread, int tic)
{
  //TODO:JK: implement me
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
