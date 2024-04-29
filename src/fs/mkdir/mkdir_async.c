#include <stdio.h>
#include <uv.h>

void on_create(uv_fs_t* req) {
  // Just announce that our folder was created
  printf("Directory %s created!\n", (char*) req->data);
  // Cleanup memory
  // See docs: http://docs.libuv.org/en/v1.x/fs.html?highlight=uv_fs_req_cleanup#c.uv_fs_req_cleanup
  uv_fs_req_cleanup(req);
}

int main (int argc, char** argv) {
  if (argc <= 1) {
    fprintf(stderr, "Usage: %s <path>\n", argv[0]);
    fprintf(stderr, "And path/my_uv_folder will be created\n");
    return 1;
  }

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
  char* folder = strcat(argv[1], "/my_uv_folder");
  uv_fs_t mkdir_req;
  mkdir_req.data = folder;
  r = uv_fs_mkdir(loop, &mkdir_req, folder, O_RDWR, on_create);
  if (r < 0) {
    // In case of error, just print it
    // See docs: http://docs.libuv.org/en/v1.x/errors.html#c.uv_strerror
    fprintf(stderr, "uv_fs_mkdir: %s\n", uv_strerror(r));
  }

  // Run our event loop
  uv_run(loop, UV_RUN_DEFAULT);
  return r;
}
