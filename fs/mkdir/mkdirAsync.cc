#include <stdio.h>
#include <uv.h>

void on_create(uv_fs_t* req) {
  // Just announce that our folder was created
  printf("Directory created!\n");
  // Cleanup memory
  uv_fs_req_cleanup(req);
}

int main() {
  // Initialize our event loop
  uv_loop_t* loop = uv_default_loop();

  // Declare variable for error handling
  int r;

  // Initialize our mkdir request,
  // if his response is less than 0, means error
  // In this particular example, we'll create a folder named folder
  // And run on_create callback when the mkdir operation is complete
  // note that the folder will be created will O_RDWR flag
  // See docs: https://pubs.opengroup.org/onlinepubs/007908799/xsh/open.html
  uv_fs_t mkdir_req;
  r = uv_fs_mkdir(loop, &mkdir_req, "./folder", O_RDWR, on_create);
  if (r < 0) {
    // In case of error, just print it
    // See docs: http://docs.libuv.org/en/v1.x/errors.html#c.uv_strerror
    fprintf(stderr, "uv_fs_mkdir: %s", uv_strerror(r));
  }

  // Run our event loop
  uv_run(loop, UV_RUN_DEFAULT);
  return 0;
}
