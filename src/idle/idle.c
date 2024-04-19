#include <stdio.h>
#include <uv.h>

void on_idle(uv_idle_t* handle) {

  // Just tell that our event loop is idling
  printf("Loop iteration before prepare handles!!\n");

  uv_idle_stop(handle);
}

int main() {
  // Initialize our event loop
  uv_loop_t* loop = uv_default_loop();

  // Initialize our variable for error handling
  int r;

  // Initialize uor idle
  // When r less than 0, that means error
  // See docs:
  // http://docs.libuv.org/en/v1.x/idle.html?highlight=uv_idle_init#c.uv_idle_init
  uv_idle_t handle;
  r = uv_idle_init(loop, &handle);
  if (r < 0) {
    // In case of error, just print it
    // See docs: http://docs.libuv.org/en/v1.x/errors.html#c.uv_strerror
    fprintf(stderr, "uv_idle_init: %s", uv_strerror(r));
  }

  // Start our idle listening
  // And calle on_idle callback when event loop is idling
  // See docs: http://docs.libuv.org/en/v1.x/idle.html?highlight=uv_idle_start#c.uv_idle_start
  r = uv_idle_start(&handle, on_idle);
  if (r < 0) {
    // In case of error, just print it
    // See docs: http://docs.libuv.org/en/v1.x/errors.html#c.uv_strerror
    fprintf(stderr, "uv_idle_start: %s", uv_strerror(r));
  }

  // Run our event loop
  // See docs: http://docs.libuv.org/en/v1.x/loop.html#c.uv_run
  uv_run(loop, UV_RUN_DEFAULT);
  return 0;
}
