#include <stdio.h>
#include <stdlib.h>
#include <uv.h>

int main(int argc, char** argv) {
  // Initialize our event loop
  // See docs: http://docs.libuv.org/en/v1.x/loop.html?highlight=uv_backend#c.uv_default_loop
  uv_loop_t* loop = uv_default_loop();

  // Get the loop's metrics
  // Docs: https://docs.libuv.org/en/v1.x/metrics.html#c.uv_metrics_info
  uv_metrics_t* metrics_info = malloc(sizeof(uv_metrics_t));
  int r = uv_metrics_info(loop, metrics_info);
  if (r < 0) {
    // In case of error, just print it
    // See docs: http://docs.libuv.org/en/v1.x/errors.html#c.uv_strerror
    fprintf(stderr, "uv_metrics_info: %s\n", uv_strerror(r));
    return r;
  }

  // Print the metrics
  fprintf(stdout, "loop_count: %llu\n", metrics_info->loop_count);
  fprintf(stdout, "events: %llu\n", metrics_info->events);
  fprintf(stdout, "events_waiting: %llu\n", metrics_info->events_waiting);

  // Run the event loop
  // Docs: http://docs.libuv.org/en/v1.x/loop.html?highlight=uv_backend#c.uv_run
  uv_run(loop, UV_RUN_DEFAULT);
  return 0;
}
