#include <uv.h>
#include <stdio.h>

int main (int argc, char* argv[]) {
  // Get the OS homedir
  // Refs: http://docs.libuv.org/en/v1.x/misc.html#c.uv_os_homedir
  char buff[512];
  size_t buff_size = sizeof(buff);
  int r = uv_os_homedir(buff, &buff_size);
  if (r < 0) {
    // Error handling
    fprintf(stderr, "Error getting OS homedir: %s\n", uv_strerror(r));
    return 1;
  }

  // Print homedir!
  fprintf(stdout, "The OS homedir is: %s\n", buff);
  return 0;
}
