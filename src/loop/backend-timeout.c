#include <stdio.h>
#include <uv.h>

int main() {
  // Initialize our event loop
  uv_loop_t* loop = uv_default_loop();

  // Get the polling timeout
  // Docs: http://docs.libuv.org/en/v1.x/loop.html?highlight=uv_backend#c.uv_backend_timeout
  int timeout = uv_backend_timeout(loop);
  fprintf(stdout, "uv_backend_timeout: %d\n", timeout);

  // Run the event loop
  // Docs: http://docs.libuv.org/en/v1.x/loop.html?highlight=uv_backend#c.uv_run
  uv_run(loop, UV_RUN_ONCE);
  return 0;
}
