#include <uv.h>
#include <stdio.h>

int main (int argc, char* argv[]) {
  // Get the PID current process
  // Refs: http://docs.libuv.org/en/v1.x/misc.html#c.uv_os_getpid
  uv_pid_t pid = uv_os_getpid();

  // Print the process PID!
  fprintf(stdout, "The PID is: %d\n", pid);
  return 0;
}
