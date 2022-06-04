#include "uv.h"
#include "stdio.h"

int main (int argc, char* argv[]) {
  size_t rss;
  // Get the RSS in the current process
  // Refs: http://docs.libuv.org/en/v1.x/misc.html#c.uv_resident_set_memory
  int r = uv_resident_set_memory(&rss);
  if (r < 0) {
    // This is our little error handler
    fprintf(stderr, "Error getting RSS: %s\n", uv_strerror(r));
    return 1;
  }

  // Print the RSS!
  fprintf(stdout, "RSS: %zu\n", rss);
  return 0;
}
