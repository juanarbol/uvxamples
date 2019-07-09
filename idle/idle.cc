#include <uv.h>
#include <stdio.h>

int i = 0;

void on_idle (uv_idle_t* handle) {
  i++;
  printf("Event loop!!\n");

  if (i >= 1000) {
    uv_idle_stop(handle);
  }
}

int main() {
  uv_loop_t *loop = uv_default_loop();

  int r;

  uv_idle_t handle;
  r = uv_idle_init(loop, &handle);
  if (r < 0) {
    fprintf(stderr, "uv_idle_init: %s", uv_strerror(r));
  }

  r = uv_idle_start(&handle, on_idle);
  if (r < 0) {
    fprintf(stderr, "uv_idle_start: %s", uv_strerror(r));
  }

  uv_run(loop, UV_RUN_DEFAULT);
  return 0;
}
