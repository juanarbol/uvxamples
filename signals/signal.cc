#include <stdio.h>
#include <uv.h>

void signal_handler(uv_signal_t* handle, int signum) {
  printf("Signal catched: %d\n", signum);
  uv_signal_stop(handle);
}

int main() {
  uv_loop_t *loop = uv_default_loop();

  uv_signal_t signal;

  uv_signal_init(loop, &signal);
  uv_signal_start(&signal, signal_handler, SIGINT);

  uv_run(loop, UV_RUN_DEFAULT);
}
