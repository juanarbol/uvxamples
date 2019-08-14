#include <uv.h>
#include <stdio.h>
#include <stdlib.h>

void on_change(uv_fs_event_t* handle, const char* filename, int events, int status) {
  printf("Hooooray!");
  // printf("%s", filename);
  // printf("%d", events);
  // printf("%d", status);
  // printf("%u", handle->type);
}

int main() {
  uv_loop_t *loop = uv_default_loop();

  printf("Adding listener!");
  int r;
  uv_fs_event_t handler;
  r = uv_fs_event_init(loop, &handler);
  if (r < 0) {
    fprintf(stderr, "uv_fs_event_init: %s", uv_strerror(r));
  }

  r = uv_fs_event_start(&handler, on_change, "./../textfile.txt", UV_FS_EVENT_RECURSIVE);
  if (r < 0) {
    fprintf(stderr, "uv_fs_event_start: %s\n", uv_strerror(r));
  }

  uv_run(loop, UV_RUN_DEFAULT);
  return 0;
}
