#include <uv.h>
#include <stdio.h>

void on_create(uv_fs_t *req) {
  printf("Directory created!\n");
  uv_fs_req_cleanup(req);
}

int main() {
  uv_loop_t *loop = uv_default_loop();

  int r;
  uv_fs_t mkdir_req;
  r = uv_fs_mkdir(loop, &mkdir_req, "./folder", O_RDWR, on_create);
  if (r < 0) {
    fprintf(stderr, "uv_fs_mkdir: %s", uv_strerror(r));
  }

  uv_run(loop, UV_RUN_DEFAULT);
}
