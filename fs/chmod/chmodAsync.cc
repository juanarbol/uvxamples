#include <uv.h>
#include <stdio.h>

void on_chmod(uv_fs_t *req) {
  // Just print when chmod operation is completed!
  printf("File chwoned!\n");
}

int main() {
  // Initialize our event loop
  uv_loop_t *loop = uv_default_loop();

  // Declare variable for error handling
  int r;

  // Initialize our chmod request,
  // if his response is less than 0, means error
  // In this particular example, we'll chmod "file.txt" with S_IRGRP permissions
  // And run on_chmod callback when the chmod operation is complete
  // See docs: https://www.gnu.org/software/libc/manual/html_node/Permission-Bits.html
  uv_fs_t chmod_req;
  r = uv_fs_chmod(loop, &chmod_req, "file.txt", S_IRGRP, on_chmod);
  if (r < 0) {
    // In case of error, just print it
    // See docs: http://docs.libuv.org/en/v1.x/errors.html#c.uv_strerror
    fprintf(stderr, "uv_fs_chmod: %s", uv_strerror(r));
  }

  // Run our event loop
  uv_run(loop, UV_RUN_DEFAULT);
  return 0;
}
