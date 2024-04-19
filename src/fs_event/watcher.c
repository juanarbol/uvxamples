#include <stdio.h>
#include <uv.h>

// This program will handle changes (renamed and changed) into a file provided
// before execution
// ./build/fs_event <file_to_watch>
// Example if "./build/fs_event file.txt" If file.txt changes, it logs it
void change_cb(uv_fs_event_t* handle,
               const char* filename,
               int events,
               int status) {
  fprintf(stdout, "Change detected in %s: ", handle->path);

  if (events == UV_RENAME) {
    printf("renamed\n");
  }

  if (events == UV_CHANGE) {
    printf("changed\n");
  }
}

int main(int argc, char** argv) {
  // Check if required params was no privided.
  if (argc <= 1) {
    fprintf(stderr, "Usage: %s <file>\n", argv[0]);
    return 1;
  }

  // Initialize event loop
  uv_loop_t* loop = uv_default_loop();

  // Log that we are adding a watch
  fprintf(stdout, "Adding watch on %s\n", argv[1]);

  // Initialize fs event
  // See docs: http://docs.libuv.org/en/v1.x/fs_event.html#c.uv_fs_event_init
  uv_fs_event_t fs_event_req;
  int r = uv_fs_event_init(loop, &fs_event_req);
  if (r < 0) {
    // In case of error, just print it
    // See docs: http://docs.libuv.org/en/v1.x/errors.html#c.uv_strerror
    fprintf(stderr, "uv_fs_event_init: %s", uv_strerror(r));
  }

  // The recursive flag watches subdirectories too.
  // See docs: http://docs.libuv.org/en/v1.x/fs_event.html#c.uv_fs_event_start
  r = uv_fs_event_start(
      &fs_event_req, change_cb, argv[1], UV_FS_EVENT_RECURSIVE);
  if (r < 0) {
    // In case of error, just print it
    // See docs: http://docs.libuv.org/en/v1.x/errors.html#c.uv_strerror
    fprintf(stderr, " uv_fs_event_start: %s", uv_strerror(r));
  }

  // Run event loop.
  // See docs: http://docs.libuv.org/en/v1.x/loop.html#c.uv_run
  uv_run(loop, UV_RUN_DEFAULT);
  return 0;
}
