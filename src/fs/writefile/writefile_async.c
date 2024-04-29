#include <stdio.h>
#include <uv.h>

// Declare a variable for our error handling
int r;

void on_open(uv_fs_t* req) {
  // Declare a variable for our buffer
  uv_buf_t iov;

  // Initialize our buffer
  // See docs: https://docs.libuv.org/en/v1.x/misc.html#c.uv_buf_init
  char* buf = "My uv string\n";
  iov = uv_buf_init(buf, strlen(buf));
  iov.base = buf;

  // Write file using our buffer content
  uv_fs_t write_req;
  r = uv_fs_write(req->loop, &write_req, req->result, &iov, 1, 0, NULL);
  if (r < 0) {
    // In case of error, just print it
    // See docs: http://docs.libuv.org/en/v1.x/errors.html#c.uv_strerror
    fprintf(stderr, "uv_fs_write: %s\n", uv_strerror(r));
  }

  // Declare a variable for closing request
  uv_fs_t close_req;
  // Close our wrote file declared on open_req (see line 52)
  // See docs: http://docs.libuv.org/en/v1.x/fs.html#c.uv_fs_close
  r = uv_fs_close(req->loop, &close_req, req->result, NULL);
  if (r < 0) {
    // In case of error, just print it
    // See docs: http://docs.libuv.org/en/v1.x/errors.html#c.uv_strerror
    fprintf(stderr, "uv_fs_close: %s\n", uv_strerror(r));
  }

  // Cleanup our memory
  uv_fs_req_cleanup(req);
  uv_fs_req_cleanup(&write_req);
  uv_fs_req_cleanup(&close_req);
}

int main (int argc, char** argv) {
  if (argc <= 1) {
    fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
    fprintf(stderr, "And <file> will be written with \"My uv string\"\n");
    return 1;
  }
  // Declare our event loop
  uv_loop_t* loop = uv_default_loop();

  // We'll create a file called output.txt, if it exists, it will be truncated
  // When file is created, on_open callback will be called
  // If result is less than 0, that means error
  // See all flags docs:
  // https://pubs.opengroup.org/onlinepubs/007908799/xsh/open.html
  uv_fs_t open_req;
  r = uv_fs_open(loop,
                 &open_req,
                 argv[1],
                 O_TRUNC | O_CREAT | O_RDWR,
                 S_IRUSR | S_IWUSR,
                 on_open);
  if (r < 0) {
    // In case of error, just print it
    // See docs: http://docs.libuv.org/en/v1.x/errors.html#c.uv_strerror
    fprintf(stderr, "uv_fs_open: %s\n", uv_strerror(r));
  }

  // Run our event loop
  uv_run(loop, UV_RUN_DEFAULT);
  return 0;
}
