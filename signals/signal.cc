#include <stdio.h>
#include <uv.h>

void signal_handler(uv_signal_t* handle, int signum) {
  // Print that our signal was received
  printf("Signal catched: %d\n", signum);

  // Stop our signal listening
  uv_signal_stop(handle);
}

int main() {
  // Initialize our event loop
  uv_loop_t *loop = uv_default_loop();

  // Create a variable for our signal handler
  uv_signal_t signal;

  // Initialize signal handler
  uv_signal_init(loop, &signal);
  // In this case, we'll listening to (SIGINT or crt + c) signal
  // When that signal is triggered, will run signal_handler callback
  uv_signal_start(&signal, signal_handler, SIGINT);

  // Run our event loop
  uv_run(loop, UV_RUN_DEFAULT);
  return 0;
}
