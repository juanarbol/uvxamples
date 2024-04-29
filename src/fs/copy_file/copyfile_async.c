#include <stdio.h>
#include <uv.h>

// This code will copy a file from one location to another
// ./build/example fileToCopy.txt destination.txt

void cp_cb (uv_fs_t* req) {
  if (req->result < 0) {
    fprintf(stderr, "Error uv_fs_copyfile: %s\n", uv_strerror(req->result));
  } else {
    printf("Copied file\n");
  }

  // Clean up our request
  uv_fs_req_cleanup(req);
}

int main (int argc, char** argv) {
  // Usage check
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <filename> <destination>\n", argv[0]);
    return 1;
  }

  // Initialize our event loop
  uv_loop_t* loop = uv_default_loop();

  // Copy the file from argv[1] to argv[2]
  // See: http://docs.libuv.org/en/v1.x/fs.html#c.uv_fs_copyfile
  uv_fs_t copy_request;
  int r = uv_fs_copyfile(loop, &copy_request, argv[1], argv[2], 0, cp_cb);
  if (r < 0) {
    fprintf(stderr, "Error uv_fs_copyfile: %s\n", uv_strerror(r));
    return r;
  }

  // Run our event loop
  return uv_run(loop, UV_RUN_DEFAULT);
}
