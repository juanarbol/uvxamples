#include <stdio.h>
#include <uv.h>

#define BUF_SIZE 24

// Declare a variable for error handling
int r;

// Clean up our read request
void read_cb (uv_fs_t* read_req) {
  uv_fs_req_cleanup(read_req);
}

// Clean up our close request
void close_cb (uv_fs_t* close_req) {
  uv_fs_req_cleanup(close_req);
}

void open_cb (uv_fs_t* open_req) {
  // Declare a variable for buffer
  uv_buf_t iov;
  char buf[BUF_SIZE];
  iov = uv_buf_init(buf, BUF_SIZE);

  // Read our file, using open_req.result, save that response in our buffer
  // And read_cb when file is completely read
  uv_fs_t read_req;
  r = uv_fs_read(open_req->loop, &read_req, open_req->result, &iov, 1, 0, read_cb);
  // Save our buffer in read_req.data
  read_req.data = iov.base;
  if (r < 0) {
    // In case of error, just print it
    // See docs: http://docs.libuv.org/en/v1.x/errors.html#c.uv_strerror
    fprintf(stderr, "uv_fs_read: %s", uv_strerror(r));
  }

  // Print our file content
  fprintf(stdout, "File content: %s\n", iov.base);

  // Create a variable for closing our file
  uv_fs_t close_req;
  // Close our file, if result is less than 0, means error
  r = uv_fs_close(open_req->loop, &close_req, open_req->result, close_cb);
  if (r < 0) {
    // In case of error, just print it
    // See docs: http://docs.libuv.org/en/v1.x/errors.html#c.uv_strerror
    fprintf(stderr, "uv_fs_close %s", uv_strerror(r));
  }

  // Free memory
  uv_fs_req_cleanup(open_req);
}

int main (int argc, char** argv) {
  if (argc <= 1) {
    fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
    fprintf(stderr, "And <file> will be read and store in a buffer with %d size\n", BUF_SIZE);
    return 1;
  }

  // Initialize our event loop
  uv_loop_t* loop = uv_default_loop();

  // Open argv[1] with permissions O_RDONLY and S_IRUSR mode
  // If r is less than 0, that means error
  // See permission docs:
  // https://pubs.opengroup.org/onlinepubs/007908799/xsh/open.html See mode
  // docs:
  // https://www.gnu.org/software/libc/manual/html_node/Permission-Bits.html
  uv_fs_t open_req;
  r = uv_fs_open(loop, &open_req, argv[1], O_RDONLY, S_IRUSR, open_cb);
  if (r < 0) {
    // In case of error, just print it
    // See docs: http://docs.libuv.org/en/v1.x/errors.html#c.uv_strerror
    fprintf(stderr, "uv_fs_open: %s", uv_strerror(r));
  }

  // Run our event loop
  uv_run(loop, UV_RUN_DEFAULT);
  return 0;
}
