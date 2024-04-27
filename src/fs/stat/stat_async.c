#include <stdio.h>
#include <uv.h>

// Signature for the callback function
void stat_cb(uv_fs_t* req) {
  // Print out the stat results
  // See the stat structure: https://docs.libuv.org/en/v1.x/fs.html#c.uv_stat_t
  fprintf(stdout, "uid : %llu\n", req->statbuf.st_uid);
  fprintf(stdout, "gid : %llu\n", req->statbuf.st_gid);
  fprintf(stdout, "size: %llu\n", req->statbuf.st_size);
  // and so on...

  // Clean up our request
  uv_fs_req_cleanup(req);
}

// This code will file stat 
// ./build/example fileToStat
int main (int argc, char** argv) {
  // Usage check
  if (argc < 1) {
    fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
    return 1;
  }

  // Initialize our event loop
  uv_loop_t* loop = uv_default_loop();

  // Stat the file from argv[1]
  // See: http://docs.libuv.org/en/v1.x/fs.html#c.uv_fs_stat
  uv_fs_t stat_req;
  int r = uv_fs_stat(loop, &stat_req, argv[1], stat_cb);
  if (r < 0) {
    fprintf(stderr, "Error uv_fs_stat: %s\n", uv_strerror(r));
    return r;
  }

  // Run our event loop
  // See: http://docs.libuv.org/en/v1.x/loop.html#c.uv_run
  return uv_run(loop, UV_RUN_DEFAULT);
}
