#include <stdio.h>
#include <uv.h>

static int r;
static void on_prepare(uv_prepare_t*);

#define CHECK(code, method)                                                    \
  {                                                                            \
    if (code < 0) {                                                            \
      fprintf(stderr, "%s error %s", method, uv_strerror(code));               \
    }                                                                          \
  }

int main() {
  uv_loop_t* loop = uv_default_loop();

  uv_prepare_t prepare;
  r = uv_prepare_init(loop, &prepare);
  CHECK(r, "uv_prepare_init");

  r = uv_prepare_start(&prepare, on_prepare);
  CHECK(r, "uv_prepare_start");

  return uv_run(loop, UV_RUN_NOWAIT);
}

static void on_prepare(uv_prepare_t* handle) {
  r = uv_prepare_stop(handle);
  CHECK(r, "uv_prepare_stop");

  printf("Loop iteration\n");
}
