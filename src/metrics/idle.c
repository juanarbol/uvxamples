#include <stdio.h>
#include <uv.h>

int main() {
  // Initialize our event loop
  uv_loop_t* loop = uv_default_loop();

  // Get the loop's idle metric
  // Docs: http://docs.libuv.org/en/v1.x/metrics.html#c.uv_metrics_idle_time
  uint64_t idle_time = uv_metrics_idle_time(loop);
  fprintf(stdout, "uv_metrics_idle_time: %llu\n", idle_time);

  // Run the event loop
  // Docs: http://docs.libuv.org/en/v1.x/loop.html?highlight=uv_backend#c.uv_run
  uv_run(loop, UV_RUN_ONCE);
  return 0;
}
