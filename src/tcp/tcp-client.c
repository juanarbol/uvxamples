#include <stdio.h>
#include <stdlib.h>
#include <uv.h>

struct sockaddr_in addr;

void alloc_cb (uv_handle_t* handle, size_t suggested_size, uv_buf_t* buf) {
  // Allocate memory for the buffer
  buf->base = (char*)malloc(suggested_size);
  buf->len = suggested_size;
}

void read_cb (uv_stream_t* stream, ssize_t nread, const uv_buf_t* buf) {
  // Read memory from the buffer
  if (nread < 0) { // If nothin to read
    if (nread == UV_EOF) { // Check if it's the end of the file
      uv_close((uv_handle_t*) stream, NULL); // Close the stream
    }
  } else if (nread > 0) { // Print the read content
    printf("Received: %s\n", buf->base);
  }

  // Free what we wrote to the buffer
  free(buf->base);
}

void on_connection (uv_connect_t* server, int status) {
  if (status < 0) {
    fprintf(stderr, "Error on_connect: %s\n", uv_strerror(status));
    return;
  }

  printf("Connected to server\n");
  // Read from the server
  // Read more: https://docs.libuv.org/en/v1.x/stream.html#c.uv_read_start
  uv_stream_t* stream = server->handle;
  uv_read_start(stream, alloc_cb, read_cb);
}

int main (int argc, char* argv[]) {
  // Allow the user to pass the port as an argument
  int port;
  if (argc < 2) {
    port = 1234;
  } else {
    port = atoi(argv[1]);
  }

  // Create the event loop
  // See docs: https://docs.libuv.org/en/v1.x/loop.html#c.uv_default_loop
  uv_loop_t* loop = uv_default_loop();

  // Init our TCP handle
  // See docs: https://docs.libuv.org/en/v1.x/tcp.html#c.uv_tcp_init
  uv_tcp_t client;
  int r = uv_tcp_init(loop, &client);
  if (r < 0) {
    fprintf(stderr, "Error: %s\n", uv_strerror(r));
    return r;
  }

  // Convert the "0.0.0.0" string to a sockaddr_in struct
  // See docs: https://docs.libuv.org/en/v1.x/misc.html#c.uv_ip4_addr
  r = uv_ip4_addr("0.0.0.0", port, &addr);
  if (r < 0) {
    fprintf(stderr, "Error: %s\n", uv_strerror(r));
    return r;
  }

  // Connect to the server
  // See docs: https://docs.libuv.org/en/v1.x/tcp.html#c.uv_tcp_connect
  uv_connect_t connect_req;
  r = uv_tcp_connect(&connect_req, &client, (const struct sockaddr*)&addr, on_connection);
  if (r < 0) {
    fprintf(stderr, "Error: %s\n", uv_strerror(r));
    return r;
  }

  return uv_run(loop, UV_RUN_DEFAULT);
}
