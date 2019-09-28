#include <stdio.h>
#include <uv.h>

#define CHECK(code, method)                                      \
  {                                                              \
    if (code < 0) {                                              \
      fprintf(stderr, "%s error %s", method, uv_strerror(code)); \
    }                                                            \
  }

void on_poll(uv_poll_t* handle, int status, int events) {
  printf("Polledddd!");
}

int main() {
  int r;
  uv_loop_t* loop = uv_default_loop();

  uv_fs_t open_req;

  r = uv_fs_open(loop, &open_req, "./file.txt", O_RDONLY, S_IRUSR, NULL);
  CHECK(r, "uv_fs_opendir");

  uv_poll_t poll;
  r = uv_poll_init(loop, &poll, open_req.result);
  CHECK(r, "uv_poll_init");

  uv_poll_t pollhandle;
  r = uv_poll_start(&pollhandle, UV_READABLE, on_poll);
  CHECK(r, "uv_poll_start");

  uv_run(loop, UV_RUN_DEFAULT);
}
