#include <uv.h>
#include <stdio.h>

void on_check (uv_check_t *handle) {
  // Notify our event loop iteration!
  printf("Event loop iteration!!\n");

  // Stop our check handle
  // See docs: http://docs.libuv.org/en/v1.x/check.html#c.uv_check_stop
  uv_check_stop(handle);
}

int main() {
  // Initialize our event loop
  uv_loop_t *loop = uv_default_loop();

  // Declare a variable for error handling
  int r;

  // Initialize our check handler
  // If result is less than 0, means error
  // See docs: http://docs.libuv.org/en/v1.x/check.html#c.uv_check_init
  uv_check_t handle;
  r = uv_check_init(loop, &handle);
  if (r < 0) {
    // In case of error, just print it
    // See docs: http://docs.libuv.org/en/v1.x/errors.html#c.uv_strerror
    fprintf(stderr, "uv_check_init: %s", uv_strerror(r));
  }

  // Start our handler, on_check callback will be run after every loop iteration
  // See docs: http://docs.libuv.org/en/v1.x/check.html#c.uv_check_start
  r = uv_check_start(&handle, on_check);
  if (r < 0) {
    // In case of error, just print it
    // See docs: http://docs.libuv.org/en/v1.x/errors.html#c.uv_strerror
    fprintf(stderr, "uv_check_init: %s", uv_strerror(r));
  }

  // Run our event loop with UV_RUN_NOWAIT mode
  // See docs: http://docs.libuv.org/en/v1.x/loop.html#c.uv_run
  uv_run(loop, UV_RUN_NOWAIT);
  return 0;
}
