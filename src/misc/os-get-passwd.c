#include <uv.h>
#include <stdio.h>

int main (int argc, char** argv) {
  // Init a variable to store the information
  uv_passwd_t passwd;
  // Get the password file entry for the current uid
  // See docs: https://docs.libuv.org/en/v1.x/misc.html#c.uv_os_get_passwd
  int r = uv_os_get_passwd(&passwd);
  if (r < 0) {
    // In case of error, print the error
    // See docs: http://docs.libuv.org/en/v1.x/errors.html#c.uv_strerror
    fprintf(stderr, "uv_os_get_passwd: %s\n", uv_err_name(r));
    return r;
  }

  // Print all the information the function gives us
  fprintf(stdout, "gid: %lu\n", passwd.gid);
  fprintf(stdout, "uid: %lu\n", passwd.uid);
  fprintf(stdout, "shell: %s\n", passwd.shell);
  fprintf(stdout, "homedir: %s\n", passwd.homedir);
  fprintf(stdout, "username: %s\n", passwd.username);

  // The allocated memory needs to be freed with uv_os_free_passwd
  // See docs: https://docs.libuv.org/en/v1.x/misc.html#c.uv_os_free_passwd
  uv_os_free_passwd(&passwd);

  return r;
}
