#include <stdio.h>
#include <uv.h>

void on_timeout(uv_timer_t* handle) {
  // Just print timeout in when timeout
  printf("Timeout!!\n");

  // Stop the timer
  // To this callback be called only once, we need to stop the timer
  // See docs: https://docs.libuv.org/en/v1.x/timer.html#c.uv_timer_stop
  uv_timer_stop(handle);
}

int main() {
  // Declare our event loop
  // See docs: https://docs.libuv.org/en/v1.x/loop.html#c.uv_default_loop
  uv_loop_t* loop = uv_default_loop();

  // Declare a variable for our timer
  uv_timer_t timer;

  // this is a variable for error handling
  int r;

  // Initialize our timer, in our timer variable (see line 16)
  // If r < 0, that means error
  // See docs: https://docs.libuv.org/en/v1.x/timer.html#c.uv_timer_init
  r = uv_timer_init(loop, &timer);
  if (r < 0) {
    // Print error in case of error
    // See docs: http://docs.libuv.org/en/v1.x/errors.html#c.uv_strerror
    fprintf(stderr, "uv_timer_init: %s", uv_strerror(r));
  }

  // Start our timer
  // the callback on_timeout will be called in 1 second
  // See docs: https://docs.libuv.org/en/v1.x/timer.html#c.uv_timer_start
  r = uv_timer_start(&timer, on_timeout, 1000, 1);
  if (r < 0) {
    // Print error in case of error
    fprintf(stderr, "uv_timer_start: %s", uv_strerror(r));
  }

  // Run our event loop
  // See docs: https://docs.libuv.org/en/v1.x/loop.html#c.uv_run
  uv_run(loop, UV_RUN_DEFAULT);
  return 0;
}
