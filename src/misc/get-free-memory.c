#include <uv.h>
#include <stdio.h>

int main () {
  // Initialize the event loop
  // Learn more at: http://docs.libuv.org/en/v1.x/loop.html?highlight=uv_loop_default#c.uv_default_loop
  uv_loop_t* loop = uv_default_loop();

  // Get free mem using libuv
  // Docs: http://docs.libuv.org/en/v1.x/misc.html#c.uv_get_free_memory
  uint64_t free_mem = uv_get_free_memory();
  fprintf(stdout, "The free mem in bytes is: %llu\n", free_mem);

  uv_run(loop, UV_RUN_ONCE);
  return 0;
}
