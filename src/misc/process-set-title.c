#include <uv.h>

int main (int argc, char* argv[]) {
  // NOTE: this is kind of hard to test, maybe considering adding a sleep here or something
  // in order to give time to the eyes to see the new title. Whatever, it's just a test.

  // In UNIX systems `uv_setup_args` should be called before `uv_set_process_title`
  // Refs: http://docs.libuv.org/en/v1.x/misc.html#c.uv_setup_args
  uv_setup_args(argc, argv);

  // Change this process title to "uvxamples!" using the `uv_set_process_title` function
  // Refs: http://docs.libuv.org/en/v1.x/misc.html#c.uv_set_process_title
  uv_set_process_title("uvxamples!");

  return 0;
}
