#include <stdio.h>
#include <uv.h>

int main (int argc, char** argv) {
  // Declare a variable for store the RSS
  size_t rss;
  // Calll the  uv_resident_set_memory
  // See docs: https://docs.libuv.org/en/v1.x/misc.html#c.uv_resident_set_memory
  int r = uv_resident_set_memory(&rss);
  if (r < 0) {
    // In case of error, print the error
    // See docs: http://docs.libuv.org/en/v1.x/errors.html#c.uv_strerror
    fprintf(stderr, " uv_resident_set_memory: %s\n", uv_err_name(r));
    return r;
  }

  // Print the value of RSS
  fprintf(stdout, " uv_resident_set_memory: %d\n", (int)rss);

  return r;
}
