#include <uv.h>
#include <stdio.h>

int main (int argc, char** argv) {
  // Init a variable to store the information
  // See docs: https://docs.libuv.org/en/v1.x/misc.html#c.uv_rusage_t
  uv_rusage_t rusage;
  //Gets the resource usage measures for the current process.
  // See docs: https://docs.libuv.org/en/v1.x/misc.html#c.uv_getrusage
  int r = uv_getrusage(&rusage);
  if (r < 0) {
    // In case of error, print the error
    // See docs: http://docs.libuv.org/en/v1.x/errors.html#c.uv_strerror
    fprintf(stderr, "uv_getrusage: %s\n", uv_err_name(r));
    return r;
  }

  // Print all the information the function gives us
  printf("ru_nivcsw %llu\n", rusage.ru_nivcsw);
  printf("ru_nvcsw %llu\n", rusage.ru_nvcsw);
  printf("ru_nsignals %llu\n", rusage.ru_nsignals);
  printf("ru_msgrcv %llu\n", rusage.ru_msgrcv);
  printf("ru_msgsnd %llu\n", rusage.ru_msgsnd);
  printf("ru_oublock %llu\n", rusage.ru_oublock);
  printf("ru_inblock %llu\n", rusage.ru_inblock);
  printf("ru_nswap %llu\n", rusage.ru_nswap);
  printf("ru_majflt %llu\n", rusage.ru_majflt);
 // ...So far so on
 // See all the fields in the docs: https://docs.libuv.org/en/v1.x/misc.html#c.uv_rusage_t

  return r;
}
