#include <uv.h>
#include <stdio.h>


int main () {
  // Initialize the event loop
  // Learn more at: http://docs.libuv.org/en/v1.x/loop.html?highlight=uv_loop_default#c.uv_default_loop
  uv_loop_t* loop = uv_default_loop();

  double host_uptime;
  // Get host's uptime
  // Docs: http://docs.libuv.org/en/v1.x/misc.html#c.uv_uptime
  int r = uv_uptime(&host_uptime);
  if (r < 0) {
    // In case of error, just print it
    // See docs: http://docs.libuv.org/en/v1.x/errors.html#c.uv_strerror
    fprintf(stderr, "uv_uptime: %s\n", uv_strerror(r));
    return r;
  } else {
    fprintf(stdout, "uv_uptime: %f\n", host_uptime);
  }

  // Run the event loop
  // See: http://docs.libuv.org/en/v1.x/loop.html?highlight=uv_loop_default#c.uv_run
  uv_run(loop, UV_RUN_ONCE);
  return 0;
}
