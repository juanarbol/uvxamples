#include <stdio.h>
#include <uv.h>


int main() {
  // Get the uname using libuv
  uv_utsname_t uname_buffer;
  // Docs: http://docs.libuv.org/en/v1.x/misc.html#c.uv_os_uname
  int r = uv_os_uname(&uname_buffer);
  if (r < 0) {
    // In case of error, just print it
    // See docs: http://docs.libuv.org/en/v1.x/errors.html#c.uv_strerror
    fprintf(stderr, "uv_os_uname: %s", uv_strerror(r));
    return r;
  }

  // See the other members of `uv_utsname_t` struct
  // Docs: http://docs.libuv.org/en/v1.x/misc.html#c.uv_utsname_t
  fprintf(stdout, "uv_os_uname: %s\n", uname_buffer.sysname);
  return 0;
}
