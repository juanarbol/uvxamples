#include <stdio.h>
#include <uv.h>


// This is the function that will be executed in the new thread
void thread_cb (void* arg) {
  // Print the callback argument
  printf("Thread arg is: %s\n", (char*)arg);
}

int main(int argc, char* argv[]) {
  // Initialize our main event loop:
  // See docs: http://docs.libuv.org/en/v1.x/loop.html#uv-loop-t-event-loop
  uv_loop_t* loop = uv_default_loop();

  // Create a new thread
  // And pass the callback function and the argument
  // See docs: https://docs.libuv.org/en/v1.x/threading.html#c.uv_thread_create
  uv_thread_t thread;
  int r = uv_thread_create(&thread, thread_cb, "Hola mundo");
  if (r < 0) {
    // In case of error, print the error
    // See docs: http://docs.libuv.org/en/v1.x/errors.html#c.uv_strerror
    fprintf(stderr, "uv_thread_create: %s\n", uv_strerror(r));
    return r;
  }

  // Run the event loop
  // I want to run this before the thread join
  // See docs: http://docs.libuv.org/en/v1.x/loop.html#c.uv_run
  r = uv_run(loop, UV_RUN_DEFAULT);
  if (r < 0) {
    // In case of error, print the error
    // See docs: http://docs.libuv.org/en/v1.x/errors.html#c.uv_strerror
    fprintf(stderr, "uv_run: %s\n", uv_strerror(r));
    return r;
  }

  // Join the thread
  r = uv_thread_join(&thread);
  if (r < 0) {
    // In case of error, print the error
    // See docs: http://docs.libuv.org/en/v1.x/errors.html#c.uv_strerror
    fprintf(stderr, "uv_thread_join: %s\n", uv_strerror(r));
    return r;
  }

  return r;
}
