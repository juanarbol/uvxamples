#include <uv.h>
#include <stdio.h>

// Declare a variable for buffer
static uv_buf_t iov;

// Declare a variable for opening request
static uv_fs_t open_req;

// Declare a variable for error handling
static int r;

void read_cb(uv_fs_t* read_req) {
  // Create a variable for closing our file
  uv_fs_t close_req;

  // Close our file, if result is less than 0, means error
  r = uv_fs_close(read_req->loop, &close_req, open_req.result, NULL);
  if (r < 0) {
    // In case of error, just print it
    // See docs: http://docs.libuv.org/en/v1.x/errors.html#c.uv_strerror
    fprintf(stderr, "uv_fs_close %s", uv_strerror(r));
  }

  // Cleanup memory
  uv_fs_req_cleanup(read_req);
  uv_fs_req_cleanup(&open_req);
  uv_fs_req_cleanup(&close_req);
}


int main() {
  // Initialize our event loop
  uv_loop_t *loop = uv_default_loop();

  // Open "file.txt" with permissions O_RDONLY and S_IRUSR mode
  // If r is less than 0, that means error
  // See permission docs: https://pubs.opengroup.org/onlinepubs/007908799/xsh/open.html
  // See mode docs: https://www.gnu.org/software/libc/manual/html_node/Permission-Bits.html
  r = uv_fs_open(loop, &open_req, "./file.txt", O_RDONLY, S_IRUSR, NULL);
  if (r < 0) {
    // In case of error, just print it
    // See docs: http://docs.libuv.org/en/v1.x/errors.html#c.uv_strerror
    fprintf(stderr, "uv_fs_open: %s", uv_strerror(r));
  }

  // Initialize our buffer with a size of 23 characters
  char buf[23];
  iov = uv_buf_init(buf, 23);

  // Read our file, using open_req.result, save that response in our buffer
  // And read_cb when file is completely read
  uv_fs_t read_req;
  r = uv_fs_read(loop, &read_req, open_req.result, &iov, 1, 0, read_cb);
  if (r < 0) {
    // In case of error, just print it
    // See docs: http://docs.libuv.org/en/v1.x/errors.html#c.uv_strerror
    fprintf(stderr, "uv_fs_read: %s", uv_strerror(r));
  }

  // Run our event loop
  uv_run(loop, UV_RUN_DEFAULT);
  return 0;
}
