#include <stdio.h>
#include <uv.h>
#include <cstdlib>

// Prepare handles will run the given callback once per loop iteration, right
// before polling for i/o.
// http://docs.libuv.org/en/v1.x/prepare.html#uv-prepare-t-prepare-handle

static uv_loop_t* loop;
static uv_timer_t timer;

static int listenKTimes = 1;
static int r;
static void on_prepare(uv_prepare_t*);

void time_callback(uv_timer_t* handle) {
  if (listenKTimes == 0) {
    uv_timer_stop(handle);
  }
}

void setupTimer() {
  uv_timer_init(loop, &timer);
  uv_timer_start(&timer, time_callback, 9000, 1);
}

// Function for error handing.
#define CHECK(code, method)                                                    \
  {                                                                            \
    if (code < 0) {                                                            \
      fprintf(stderr, "%s error %s", method, uv_strerror(code));               \
    }                                                                          \
  }

int main(int argc, char* argv[]) {
  // Initialize our main event loop:
  // See docs: http://docs.libuv.org/en/v1.x/loop.html#uv-loop-t-event-loop
  loop = uv_default_loop();

  if (argc > 1) {
    listenKTimes = atoi(argv[1]);
    // Create timer requests for keeps event loop busy.
    setupTimer();
  }

  // Initialize our prepare handle and handle errors.
  // See docs: http://docs.libuv.org/en/v1.x/prepare.html#c.uv_prepare_init
  uv_prepare_t prepare;
  r = uv_prepare_init(loop, &prepare);
  CHECK(r, "uv_prepare_init");

  // Start our prepare handle and handle error if any.
  // See docs: http://docs.libuv.org/en/v1.x/prepare.html#c.uv_prepare_start
  r = uv_prepare_start(&prepare, on_prepare);
  CHECK(r, "uv_prepare_start");

  // Run our event loop.
  uv_run(loop, UV_RUN_DEFAULT);
  return 1;
}

// This is our callback called on_prepare event
// Here, we just call our callback n times, default 1.
static void on_prepare(uv_prepare_t* handle) {
  // One time less to be called the callback.
  listenKTimes--;

  // Print that event is called.
  printf("Loop iteration\n");

  if (listenKTimes == 0) {
    // Stop our listening event:
    // See docs: http://docs.libuv.org/en/v1.x/prepare.html#c.uv_prepare_start
    r = uv_prepare_stop(handle);
    CHECK(r, "uv_prepare_stop");
    uv_loop_close(loop);
    return;
  }
}
