#include <stdio.h>
#include <uv.h>
#include <stdlib.h>

static int kHandleTimes = 1;

void signal_handler(uv_signal_t* handle, int signum) {
  kHandleTimes--;

  // Print that our signal was received
  printf("Signal received: %d\n", signum);

  if (kHandleTimes == 0) {
    // Stop our signal listening
    // at this point, the process will finish.
    // See docs: https://docs.libuv.org/en/v1.x/signal.html#c.uv_signal_stop
    uv_signal_stop(handle);
  }
}

int main(int argc, char *argv[]) {
  // Handle signal k times using argv.
  if (argc > 1) {
    kHandleTimes = atoi(argv[1]);
  }

  printf("Will handle SIGINT signal %d time(s)\n", kHandleTimes);

  // Initialize our event loop
  // See docs: https://docs.libuv.org/en/v1.x/loop.html#c.uv-loop-t-event-loop
  uv_loop_t* loop = uv_default_loop();

  // Create a variable for our signal handler
  // See docs: https://docs.libuv.org/en/v1.x/signal.html#c.uv-signal-t
  uv_signal_t signal;

  // Initialize signal handler.
  // See docs: https://docs.libuv.org/en/v1.x/signal.html#c.uv_signal_init
  uv_signal_init(loop, &signal);

  // In this case, we'll listening to SIGINT (ctrl + c) signal.
  // When that signal is triggered, will run signal_handler callback.
  // See docs: https://docs.libuv.org/en/v1.x/signal.html#c.uv_signal_start
  uv_signal_start(&signal, signal_handler, SIGINT);

  // Run our event loop
  uv_run(loop, UV_RUN_DEFAULT);
  return 0;
}
