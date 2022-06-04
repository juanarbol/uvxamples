#include "uv.h"
#include "stdio.h"

int main (int argc, char* argv[]) {
  // Get the OS temp dir
  // Refs: http://docs.libuv.org/en/v1.x/misc.html#c.uv_os_tmpdir
  char buff[512];
  size_t buff_size = sizeof(buff);
  int r = uv_os_tmpdir(buff, &buff_size);
  if (r < 0) {
    // Error handling
    fprintf(stderr, "Error getting OS temp dir: %s\n", uv_strerror(r));
    return 1;
  }

  // Print temp dir!
  fprintf(stdout, "The OS temp dir is: %s\n", buff);
  return 0;
}
