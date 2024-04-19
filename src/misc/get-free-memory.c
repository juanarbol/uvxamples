#include <uv.h>
#include <stdio.h>

int main () {
  // Get free mem using libuv
  // Docs: http://docs.libuv.org/en/v1.x/misc.html#c.uv_get_free_memory
  uint64_t free_mem = uv_get_free_memory();
  fprintf(stdout, "The free mem in bytes is: %llu\n", free_mem);

  return 0;
}
