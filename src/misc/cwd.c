#include <stdio.h>
#include <uv.h>

int main() {
  // Get the current working dir using libuv
  // Docs: http://docs.libuv.org/en/v1.x/misc.html#c.uv_cwd
  char buff[256];
  size_t* size = sizeof buff;
  int r = uv_cwd(buff, &size);
  if (r < 0) {
    // In case of error, just print it
    // See docs: http://docs.libuv.org/en/v1.x/errors.html#c.uv_strerror
    fprintf(stderr, "uv_cwd: %s", uv_strerror(r));
    return r;
  }

  fprintf(stdout, "uv_cwd: %s\n", buff);
  return 0;
}
