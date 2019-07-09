#include <uv.h>
#include <stdio.h>

int main() {
  uv_loop_t *loop = uv_default_loop();

  int r;
  uv_fs_t chmod_req;
  r = uv_fs_chmod(loop, &chmod_req, "file.txt", S_IRGRP, NULL);
  if (r < 0) {
    fprintf(stderr, "uv_fs_chmod: %s", uv_strerror(r));
  }

  uv_run(loop, UV_RUN_DEFAULT);
}