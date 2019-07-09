#include <uv.h>
#include <stdio.h>

static uv_buf_t iov;
static uv_fs_t open_req;

int main() {
  uv_loop_t *loop = uv_default_loop();

  int r;
  r = uv_fs_open(loop, &open_req, "output.txt", O_TRUNC | O_CREAT | O_RDWR, S_IRUSR | S_IWUSR, NULL);
  if (r < 0) {
    fprintf(stderr, "uv_fs_open: %s\n", uv_strerror(r));
  }

  char buf[21];
  iov = uv_buf_init(buf, 21);
  iov.base = "This a literal string";

  uv_fs_t write_req;
  r = uv_fs_write(loop, &write_req, open_req.result, &iov, 1, 0, NULL);
  if (r < 0) {
    fprintf(stderr, "uv_fs_write: %s\n", uv_strerror(r));
  }

  uv_fs_t close_req;
  r = uv_fs_close(loop, &close_req, open_req.result, NULL);
  if (r < 0) {
    fprintf(stderr, "uv_fs_close: %s\n", uv_strerror(r));
  }

  uv_fs_req_cleanup(&open_req);
  uv_fs_req_cleanup(&write_req);
  uv_fs_req_cleanup(&close_req);

  uv_run(loop, UV_RUN_DEFAULT);
}
