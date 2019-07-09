#include <uv.h>
#include <stdio.h>

void on_timeout (uv_timer_t *handle) {
  printf("Timeout!!\n");

  uv_timer_stop(handle);
  // uv_timer_again(handle);
  // uv_timer_set_repeat(handle, 1000);
}

int main() {
  uv_loop_t *loop = uv_default_loop();

  uv_timer_t timer;
  
  int r;

  r = uv_timer_init(loop, &timer);
  if (r < 0) {
    fprintf(stderr, "uv_timer_init: %s", uv_strerror(r));
  }

  r = uv_timer_start(&timer, on_timeout, 3000, 1);
  if (r < 0) {
    fprintf(stderr, "uv_timer_start: %s", uv_strerror(r));
  }

  uv_run(loop, UV_RUN_DEFAULT);
  return 0;
}
