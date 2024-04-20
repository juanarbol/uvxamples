#include <stdio.h>
#include <uv.h>

// This a quite simple callback, It will tell us that is being called and will
// print the data
void async_cb (uv_async_t* handle) {
  printf("Async callback triggered!\n");
  printf("The async CB got this data: %s\n", (char*)handle->data);
}

// This callback what I want to do from the worker thread
// Just call the async callback moving some data, the string "Hola mundo" in
// this case
void thread_cb (void* arg) {
  uv_async_t* handle = (uv_async_t*)arg;
  // Send some data, just for fun!
  handle->data = "Hola mundo";
  uv_async_send(handle);
}

int main (int argc, char** argv) {
  // Initialize our event loop
  // See docs: http://docs.libuv.org/en/v1.x/loop.html?highlight=uv_backend#c.uv_default_loop
  uv_loop_t* loop = uv_default_loop();


  // Create an async handle with its callback that will be invoked from a worker
  // thread.
  // See docs: https://docs.libuv.org/en/v1.x/async.html#c.uv_async_t
  uv_async_t async;
  int r = uv_async_init(loop, &async, async_cb);
  if (r < 0) {
    // In case of error, just print it
    // See docs: http://docs.libuv.org/en/v1.x/errors.html#c.uv_strerror
    fprintf(stderr, "uv_async_init: %s", uv_strerror(r));
    return r;
  }

  // Create a worker thread that will send the async signal.
  // See docs: https://docs.libuv.org/en/v1.x/threading.html#c.uv_thread_create
  uv_thread_t worker_thread;
  r = uv_thread_create(&worker_thread, thread_cb, &async);
  if (r < 0) {
    // In case of error, just print it
    // See docs: http://docs.libuv.org/en/v1.x/errors.html#c.uv_strerror
    fprintf(stderr, "uv_thread_create: %s", uv_strerror(r));
    return r;
  }

  // Join the worker to the game
  r = uv_thread_join(&worker_thread);
  if (r < 0) {
    // In case of error, just print it
    // See docs: http://docs.libuv.org/en/v1.x/errors.html#c.uv_strerror
    fprintf(stderr, "uv_thread_join: %s", uv_strerror(r));
    return r;
  }

  // Run the event loop
  // Docs: http://docs.libuv.org/en/v1.x/loop.html?highlight=uv_backend#c.uv_run
  return uv_run(loop, UV_RUN_ONCE);
}
