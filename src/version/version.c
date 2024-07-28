#include <stdio.h>
#include <uv.h>

int main(void) {
  /* Retrieve the version of libuv in string and hex */
  fprintf(stdout, "libuv version in string: %s\n", uv_version_string());
  fprintf(stdout, "libuv version in hex: %d\n", uv_version());
  return 0;
}
