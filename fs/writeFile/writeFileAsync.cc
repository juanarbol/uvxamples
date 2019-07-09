#include <uv.h>
#include <stdio.h>

static uv_fs_t open_req;
static uv_buf_t iov;

static int r;

void on_open(uv_fs_t *req) {
  char buf[22];
  iov = uv_buf_init(buf, 22);
  iov.base = "hello world with libuv";

  uv_fs_t write_req;
  r = uv_fs_write(req->loop, &write_req, req->result, &iov, 1, 0, NULL);
  if (r < 0) {
    fprintf(stderr, "uv_fs_write: %s", uv_strerror(r));
  }

  uv_fs_t close_req;
  r = uv_fs_close(req->loop, &close_req, req->result, NULL);
  if (r < 0) {
    fprintf(stderr, "uv_fs_close: %s", uv_strerror(r));
  }

  uv_fs_req_cleanup(req);
  uv_fs_req_cleanup(&write_req);
  uv_fs_req_cleanup(&close_req);
}

int main() {
  uv_loop_t *loop = uv_default_loop();

  r = uv_fs_open(loop, &open_req, "output.txt", O_TRUNC | O_CREAT | O_RDWR, S_IRUSR | S_IWUSR, on_open);
  if (r < 0) {
    fprintf(stderr, "uv_fs_open: %s", uv_strerror(r));
  }

  uv_run(loop, UV_RUN_DEFAULT);

  return 0;
}
