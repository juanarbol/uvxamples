#include <stdio.h>
#include <stdlib.h>
#include <uv.h>

// For facility I will a struct with the mutex and the "shared" variable
// a counter that will be incremented by the threads
typedef struct SharedData {
  uv_mutex_t mutex;
  int counter;
} SharedData;

// The increment counter for each thread
void thread_cb (void* arg) {
  // Cast the arg
  SharedData* data = (SharedData*)arg;
  // Grab the lock
  uv_mutex_lock(&data->mutex);
  // Mutate the counter
  data->counter++;
  // Relase the lock
  uv_mutex_unlock(&data->mutex);
}

int main(int argc, char* argv[]) {
  int i, r;
  // Initialize our main event loop:
  // See docs: http://docs.libuv.org/en/v1.x/loop.html#uv-loop-t-event-loop
  uv_loop_t* loop = uv_default_loop();

  // Init the mutex handle
  // See docs: https://docs.libuv.org/en/v1.x/threading.html#c.uv_mutex_init
  uv_mutex_t mutex_handle;
  r = uv_mutex_init(&mutex_handle);
  if (r < 0) {
    // In case of error, print the error
    // See docs: http://docs.libuv.org/en/v1.x/errors.html#c.uv_strerror
    fprintf(stderr, "uv_mutex_init: %s\n", uv_strerror(r));
    return r;
  }

  // Init and populate the SharedData struct
  SharedData* data = (SharedData*)malloc(sizeof(SharedData*));
  data->mutex = mutex_handle;
  data->counter = 0;

  // Create a array of threads
  // And pass the callback function and the argument
  // In our case the callback will increment our counter, that's why the struct
  // is easier here, send the lock and the protected/shared resource (counter)
  // See docs: https://docs.libuv.org/en/v1.x/threading.html#c.uv_thread_create
  uv_thread_t threads[10];
  for (i = 0; i < 10; i++) {
    r = uv_thread_create(&threads[i], thread_cb, (void*)data);
    if (r < 0) {
      // In case of error, print the error
      // See docs: http://docs.libuv.org/en/v1.x/errors.html#c.uv_strerror
      fprintf(stderr, "uv_thread_create: %s\n", uv_strerror(r));
      return r;
    }
  }

  // Run the event loop
  // I want to run this before the threads join
  // See docs: http://docs.libuv.org/en/v1.x/loop.html#c.uv_run
  r = uv_run(loop, UV_RUN_DEFAULT);
  if (r < 0) {
    // In case of error, print the error
    // See docs: http://docs.libuv.org/en/v1.x/errors.html#c.uv_strerror
    fprintf(stderr, "uv_run: %s\n", uv_strerror(r));
    return r;
  }

  // Join the threads
  for (i = 0; i < 10; i++) {
    r = uv_thread_join(&threads[i]);
    if (r < 0) {
      // In case of error, print the error
      // See docs: http://docs.libuv.org/en/v1.x/errors.html#c.uv_strerror
      fprintf(stderr, "uv_thread_join: %s\n", uv_strerror(r));
      return r;
    }
  }

  // Just after everything is finished, print the counter value
  printf("The counter value mutated is: %d\n", data->counter);

  return r;
}
