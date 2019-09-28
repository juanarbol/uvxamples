#include <stdio.h>
#include <uv.h>

// Deaclare a variable for our buffer
static uv_buf_t iov;

// Declare a variable for our open request
static uv_fs_t open_req;

int main() {
  // Initialize our event loop
  uv_loop_t* loop = uv_default_loop();

  // Declare a variable for error handling
  int r;

  // We'll create a file called output.txt, if it exists, it will be truncated
  // If result is less than 0, that means error
  // See all flags docs:
  // https://pubs.opengroup.org/onlinepubs/007908799/xsh/open.html
  r = uv_fs_open(loop, &open_req, "output.txt", O_TRUNC | O_CREAT | O_RDWR,
                 S_IRUSR | S_IWUSR, NULL);
  if (r < 0) {
    // In case of error, just print it
    // See docs: http://docs.libuv.org/en/v1.x/errors.html#c.uv_strerror
    fprintf(stderr, "uv_fs_open: %s\n", uv_strerror(r));
  }

  // Initialize our buffer
  char buf[21];
  iov = uv_buf_init(buf, 21);

  // write "This a literal string" as his content
  iov.base = "This a literal string";

  // Write file using our buffer content
  uv_fs_t write_req;
  r = uv_fs_write(loop, &write_req, open_req.result, &iov, 1, 0, NULL);
  if (r < 0) {
    // In case of error, just print it
    // See docs: http://docs.libuv.org/en/v1.x/errors.html#c.uv_strerror
    fprintf(stderr, "uv_fs_write: %s\n", uv_strerror(r));
  }

  // Declare a variable for closing request
  uv_fs_t close_req;

  // Close our wrote file declared on open_req (see line 20)
  r = uv_fs_close(loop, &close_req, open_req.result, NULL);
  if (r < 0) {
    // In case of error, just print it
    // See docs: http://docs.libuv.org/en/v1.x/errors.html#c.uv_strerror
    fprintf(stderr, "uv_fs_close: %s\n", uv_strerror(r));
  }

  // Cleanup our memory
  uv_fs_req_cleanup(&open_req);
  uv_fs_req_cleanup(&write_req);
  uv_fs_req_cleanup(&close_req);

  // Run our event loop
  uv_run(loop, UV_RUN_DEFAULT);
  return 0;
}
