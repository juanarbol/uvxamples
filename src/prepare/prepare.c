#include <stdio.h>
#include <uv.h>

// Prepare handles will run the given callback once per loop iteration, right
// before polling for i/o.
// http://docs.libuv.org/en/v1.x/prepare.html#uv-prepare-t-prepare-handle
static int r;
static void on_prepare(uv_prepare_t*);

int main(int argc, char* argv[]) {
  // Initialize our main event loop:
  // See docs: http://docs.libuv.org/en/v1.x/loop.html#uv-loop-t-event-loop
  uv_loop_t* loop = uv_default_loop();

  // Initialize our prepare handle and handle errors.
  // See docs: http://docs.libuv.org/en/v1.x/prepare.html#c.uv_prepare_init
  uv_prepare_t prepare;
  r = uv_prepare_init(loop, &prepare);
  if (r < 0) {
    fprintf(stderr, "%s error %s", "uv_prepare_init", uv_strerror(r));
  }

  // Just keep a ref to the event loop
  prepare.data = loop;

  // Start our prepare handle and handle error if any.
  // See docs: http://docs.libuv.org/en/v1.x/prepare.html#c.uv_prepare_start
  r = uv_prepare_start(&prepare, on_prepare);
  if (r < 0) {
    fprintf(stderr, "%s error %s", "uv_prepare_start", uv_strerror(r));
  }

  // Run our event loop.
  uv_run(loop, UV_RUN_DEFAULT);
  return 0;
}

// This is our callback called on_prepare event
// Here, we just call our callback n times, default 1.
static void on_prepare(uv_prepare_t* handle) {
  // Print that event is called.
  printf("Loop will start blocking for I/O polling\n");

  // Stop our listening event:
  // See docs: http://docs.libuv.org/en/v1.x/prepare.html#c.uv_prepare_start
  r = uv_prepare_stop(handle);
  if (r < 0) {
    fprintf(stderr, "%s error %s", "uv_prepare_stop", uv_strerror(r));
  }
  uv_loop_close(handle->loop);
}
