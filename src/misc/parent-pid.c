#include "uv.h"
#include "stdio.h"

int main (int argc, char* argv[]) {
  // Get the Parent PID of the current process
  // Refs: http://docs.libuv.org/en/v1.x/misc.html#c.uv_os_getppid
  uv_pid_t ppid = uv_os_getppid();

  // Print the process PID!
  fprintf(stdout, "The Parent PID is : %d\n", ppid);
  return 0;
}
