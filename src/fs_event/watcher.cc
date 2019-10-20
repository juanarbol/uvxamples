#include <stdio.h>
#include <stdlib.h>
#include "uv.h"

// This code was taken from this source:
// https://github.com/Akagi201/learning-libuv/blob/master/onchange/main.c

static int r;
uv_loop_t* loop;
const char* command;

// This program will handle changes (renamed and changed) into a file provided
// before execution
// ./build/fs_event <command> <file_to_watch> [file2 ...]
// Example if "./build/fs_event ls file.txt" If file.txt changes, "ls" command
// will run.
void run_command(uv_fs_event_t* handle,
                 const char* filename,
                 int events,
                 int status) {
  fprintf(stderr, "Change detected in %s: ", handle->path);
  if (events == UV_RENAME) {
    fprintf(stderr, "renamed");
  }
  if (events == UV_CHANGE) {
    fprintf(stderr, "changed");
  }

  fprintf(stderr, " %s\n", filename ? filename : "");
  // Syscall to <command>
  system(command);
}

int main(int argc, char** argv) {
  // Check if required params was no privided.
  if (argc <= 2) {
    fprintf(stderr, "Usage: %s <command> <file1> [file2 ...]\n", argv[0]);
    return 1;
  }

  // Initialize event loop
  loop = uv_default_loop();

  // Save command provided in argv
  command = argv[1];

  // Keep that logic on a loop.
  while (argc-- > 2) {
    fprintf(stderr, "Adding watch on %s\n", argv[argc]);

    uv_fs_event_t fs_event_req;

    // Initialize fs event
    // See docs: http://docs.libuv.org/en/v1.x/fs_event.html#c.uv_fs_event_init
    r = uv_fs_event_init(loop, &fs_event_req);
    if (r < 0) {
      // In case of error, just print it
      // See docs: http://docs.libuv.org/en/v1.x/errors.html#c.uv_strerror
      fprintf(stderr, "uv_fs_event_init: %s", uv_strerror(r));
    }

    // The recursive flag watches subdirectories too.
    // See docs: http://docs.libuv.org/en/v1.x/fs_event.html#c.uv_fs_event_start
    r = uv_fs_event_start(
        &fs_event_req, run_command, argv[argc], UV_FS_EVENT_RECURSIVE);
    if (r < 0) {
      // In case of error, just print it
      // See docs: http://docs.libuv.org/en/v1.x/errors.html#c.uv_strerror
      fprintf(stderr, "uv_fs_event_init: %s", uv_strerror(r));
    }
  }

  // Run event loop.
  // See docs: http://docs.libuv.org/en/v1.x/loop.html#c.uv_run
  uv_run(loop, UV_RUN_DEFAULT);
  return 0;
}
