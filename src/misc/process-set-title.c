#include "uv.h"
#include "stdio.h"
// #include "unistd.h" // remove comment if the sleep function is required
#ifdef _WIN32
// #include <Windows.h> // remove comment if the sleep function is required for Windows
#else

int main (int argc, char* argv[]) {
  // In UNIX systems `uv_setup_args` should be called before `uv_set_process_title`
  // Refs: http://docs.libuv.org/en/v1.x/misc.html#c.uv_setup_args
  uv_setup_args(argc, argv);

  // Change this process title to "uvxamples!" using the `uv_set_process_title` function
  // Refs: http://docs.libuv.org/en/v1.x/misc.html#c.uv_set_process_title
  uv_set_process_title("uvxamples!");

  // This is for test porpuses only, this will finish executions really fast, an intentional
  // sleep could make it easier to confirm that the API works.
  // sleep(20);

  return 0;
}
