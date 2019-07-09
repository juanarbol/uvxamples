#include <uv.h>
#include <stdio.h>

static uv_buf_t iov;
static uv_fs_t open_req;
static int r;

void read_cb(uv_fs_t* read_req) {
  uv_fs_t close_req;

  r = uv_fs_close(read_req->loop, &close_req, open_req.result, NULL);
  if (r < 0) {
    fprintf(stderr, "uv_fs_close %s", uv_strerror(r));
  }

  uv_fs_req_cleanup(read_req);
  uv_fs_req_cleanup(&open_req);
  uv_fs_req_cleanup(&close_req);
}


int main() {
  uv_loop_t *loop = uv_default_loop();

  r = uv_fs_open(loop, &open_req, "./file.txt", O_RDONLY, S_IRUSR, NULL);
  if (r < 0) {
    fprintf(stderr, "uv_fs_open: %s", uv_strerror(r));
  }

  char buf[23];
  iov = uv_buf_init(buf, 23);

  uv_fs_t read_req;
  r = uv_fs_read(loop, &read_req, open_req.result, &iov, 1, 0, read_cb);
  if (r < 0) {
    fprintf(stderr, "uv_fs_read: %s", uv_strerror(r));
  }

  uv_run(loop, UV_RUN_DEFAULT);
  return 0;
}
