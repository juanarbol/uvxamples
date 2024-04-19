#include <uv.h>
#include <stdio.h>

int main () {
  double host_uptime;
  // Get host's uptime
  // Docs: http://docs.libuv.org/en/v1.x/misc.html#c.uv_uptime
  int r = uv_uptime(&host_uptime);
  if (r < 0) {
    // In case of error, just print it
    // See docs: http://docs.libuv.org/en/v1.x/errors.html#c.uv_strerror
    fprintf(stderr, "uv_uptime: %s\n", uv_strerror(r));
    return r;
  }

  // Print host's uptime
  fprintf(stdout, "uv_uptime: %f\n", host_uptime);

  return 0;
}
