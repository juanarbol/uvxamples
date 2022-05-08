#include <uv.h>
#include <stdio.h>

static char buff[256];

void random_cb(uv_random_t* req, int status, void* buffRef, size_t bufflen) {
  fprintf(stdout, "uv_random: %s", buff);
}

int main () {
  // Initialize the event loop
  // Learn more at: http://docs.libuv.org/en/v1.x/loop.html?highlight=uv_loop_default#c.uv_default_loop
  uv_loop_t* loop = uv_default_loop();

  // Get random bytes from the system
  // Docs: http://docs.libuv.org/en/v1.x/misc.html#c.uv_random
  uv_random_t req;
  int r = uv_random(loop, &req, &buff, sizeof(buff), 0, random_cb);
  if (r < 0) {
    // In case of error, just print it
    // See docs: http://docs.libuv.org/en/v1.x/errors.html#c.uv_strerror
    fprintf(stderr, "uv_idle_init: %s", uv_strerror(r));
    return r;
  }

  uv_run(loop, UV_RUN_ONCE);
  return 0;
}
