#include <uv.h>
#include <stdio.h>

int main (int argc, char* argv[]) {
  // Get the OS host name
  // Refs: https://docs.libuv.org/en/v1.x/misc.html#c.uv_os_gethostname
  char buff[24];
  size_t buff_size = sizeof(buff);
  int r = uv_os_gethostname(buff, &buff_size);
  if (r < 0) {
    // Error handling
    fprintf(stderr, "uv_os_gethostname: %s\n", uv_strerror(r));
    return r;
  }

  // Print host name!
  fprintf(stdout, "the host name is: %s\n", buff);
  return r;
}
