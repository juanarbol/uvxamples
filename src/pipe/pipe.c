#include <stdio.h>
#include <stdlib.h>
#include <uv.h>

// This file with read a file and write its content to stdout using a pipe

int main(int argc, char** argv) {
  // Check if the user passed the file path
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <file>\n", argv[0]);
    return 1;
  }

  // Initialize the event loop
  // See: https://docs.libuv.org/en/v1.x/loop.html#c.uv_default_loop
  uv_loop_t* loop = uv_default_loop();

  // Open the file synchronously
  // See: https://docs.libuv.org/en/v1.x/fs.html#c.uv_fs_open
  uv_fs_t open_req;
  int r = uv_fs_open(loop, &open_req, argv[1], O_RDONLY, 0, NULL);
  if (r < 0) {
    fprintf(stderr, "Error uv_fs_open: %s\n", uv_strerror(r));
    return r;
  }

  // Run stat on the file
  // See: https://docs.libuv.org/en/v1.x/fs.html#c.uv_fs_fstat
  uv_fs_t fstat_req;
  r = uv_fs_fstat(loop, &fstat_req, open_req.result, NULL);
  if (r < 0) {
    fprintf(stderr, "Error uv_fs_fstat: %s\n", uv_strerror(r));
    return r;
  }

  // Init a buffer to read the file with the size of the file
  // See: https://docs.libuv.org/en/v1.x/misc.html#c.uv_buf_init
  char buffer[fstat_req.statbuf.st_size + 1];
  uv_buf_t buf = uv_buf_init(buffer, fstat_req.statbuf.st_size + 1);

  // Init and open a pipe to write the file content to stdout
  // See: https://docs.libuv.org/en/v1.x/pipe.html#c.uv_pipe_init
  uv_pipe_t pipe;
  r = uv_pipe_init(loop, &pipe, 0);
  if (r < 0) {
    fprintf(stderr, "Error uv_pipe_init: %s\n", uv_strerror(r));
    return r;
  }

  // See: https://docs.libuv.org/en/v1.x/pipe.html#c.uv_pipe_open
  r = uv_pipe_open(&pipe, 1);  // 1 refers to stdout
  if (r < 0) {
    fprintf(stderr, "Error uv_pipe_open: %s\n", uv_strerror(r));
    return r;
  }

  // Read the file synchronously and store the content in the buffer
  // See: https://docs.libuv.org/en/v1.x/fs.html#c.uv_fs_read
  uv_fs_t read_req;
  r = uv_fs_read(loop, &read_req, open_req.result, &buf, 1, 0, NULL);
  if (r < 0) {
    fprintf(stderr, "Error uv_fs_read: %s\n", uv_strerror(r));
    return r;
  }

  // Close the file synchronously
  // See: https://docs.libuv.org/en/v1.x/fs.html#c.uv_fs_close
  r = uv_fs_close(loop, &open_req, open_req.file, NULL);
  if (r < 0) {
    fprintf(stderr, "Error uv_fs_close: %s\n", uv_strerror(r));
    return r;
  }

  // Write into the pipe (stdout) the content of the buffer synchronously
  // See: https://docs.libuv.org/en/v1.x/stream.html#c.uv_write
  uv_write_t write_req;
  r = uv_write(&write_req, (uv_stream_t*)&pipe, &buf, 1, NULL);
  if (r < 0) {
    fprintf(stderr, "Error uv_write: %s\n", uv_strerror(r));
    return r;
  }

  // cleanup the fs requests
  uv_fs_req_cleanup(&open_req);
  uv_fs_req_cleanup(&fstat_req);
  uv_fs_req_cleanup(&read_req);

  // Run the event loop
  // See: https://docs.libuv.org/en/v1.x/loop.html#c.uv_run
  return uv_run(loop, UV_RUN_DEFAULT);
}
