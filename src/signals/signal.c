#include <stdio.h>
#include <uv.h>
#include <stdlib.h>

static int kHandleTimes = 1;

void signal_handler(uv_signal_t* handle, int signum) {
  kHandleTimes--;

  // Print that our signal was received
  printf("Signal catched: %d\n", signum);

  if (kHandleTimes == 0) {
    // Stop our signal listening
    // at this point, the process will finish.
    uv_signal_stop(handle);
  }
}

int main(int argc, char *argv[]) {
  // Handle signal k times using argv.
  if (argc > 1) {
    kHandleTimes = atoi(argv[1]);
  }

  // Initialize our event loop
  uv_loop_t* loop = uv_default_loop();

  // Create a variable for our signal handler
  uv_signal_t signal;

  // Initialize signal handler.
  uv_signal_init(loop, &signal);

  // In this case, we'll listening to SIGINT (ctrl + c) signal.
  // When that signal is triggered, will run signal_handler callback.
  uv_signal_start(&signal, signal_handler, SIGINT);

  // Run our event loop
  uv_run(loop, UV_RUN_DEFAULT);
  return 0;
}
