#include "uv.h"
#include "stdio.h"

int main (int argc, char* argv[]) {
  // In UNIX systems `uv_setup_args` should be called before `uv_set_process_title`
  // and `uv_get_process_title` functions
  // Refs: http://docs.libuv.org/en/v1.x/misc.html#c.uv_setup_args
  uv_setup_args(argc, argv);

  // Change this process title to "uvxamples!" using the `uv_set_process_title` function
  // Refs: http://docs.libuv.org/en/v1.x/misc.html#c.uv_set_process_title
  uv_set_process_title("uvxamples!");

  char buff[512];
  // Use the `uv_get_process_title` for getting the process title
  // Refs: http://docs.libuv.org/en/v1.x/misc.html#c.uv_get_process_title
  int r = uv_get_process_title(buff, sizeof(buff));
  if (r < 0) {
    // Error handling
    fprintf(stderr, "Error getting process title: %s\n", uv_strerror(r));
    return 1;
  }

  // Finally print the process title
  fprintf(stdout, "The process title is: %s\n", buff);
  return 0;
}
