#include <stdio.h>
#include <uv.h>

void on_poll(uv_poll_t* handle, int status, int events) {
  if (status < 0) {
    fprintf(stderr, "Poll error: %s\n", uv_strerror(status));
    return;
  }

  fprintf(stdout, "Poll from stdin went ok! Bye!\n" );
}

int main (int argc, char** argv) {
  int r;
  uv_loop_t* loop = uv_default_loop();

  // Read from stdin
  // Docs: https://docs.libuv.org/en/v1.x/poll.html#c.uv_poll_init
  uv_poll_t stdin_poll;
  int stdin_fd = fileno(stdin);
  r = uv_poll_init(loop, &stdin_poll, stdin_fd);
  if (r < 0) {
    // In case of error, just print it
    // See docs: http://docs.libuv.org/en/v1.x/errors.html#c.uv_strerror
    fprintf(stderr, "uv_poll_init: %s", uv_strerror(r));
    return r;
  }

  // Start polling and send the callback
  // Docs: https://docs.libuv.org/en/v1.x/poll.html#c.uv_poll_start
  r = uv_poll_start(&stdin_poll, UV_READABLE, on_poll);
  if (r < 0) {
    // In case of error, just print it
    // See docs: http://docs.libuv.org/en/v1.x/errors.html#c.uv_strerror
    fprintf(stderr, "uv_poll_start: %s", uv_strerror(r));
    return r;
  }

  fprintf(stdout, "Please send something via stdin:\n");

  // Run the event loop
  // Docs: https://docs.libuv.org/en/v1.x/loop.html#c.uv_run
  uv_run(loop, UV_RUN_ONCE);
}
