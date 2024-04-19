#include <stdio.h>
#include <stdlib.h>
#include <uv.h>

int r;
struct sockaddr_in addr;

// This function is called when a new connection is received
void on_connection (uv_stream_t* server, int status) {
  if (status < 0) {
    fprintf(stderr, "New connection error %s\n", uv_strerror(status));
    return;
  }

  printf("New connection received\n");

  // Create a new client hadle
  uv_tcp_t* client = (uv_tcp_t*)malloc(sizeof(uv_tcp_t));
  uv_tcp_init(server->loop, client);
  // Accept the new connection
  // See docs: https://docs.libuv.org/en/v1.x/stream.html#c.uv_accept
  if (uv_accept(server, (uv_stream_t*)client) == 0) {
    // If connection is accepted start writing to the client
    uv_write_t* write_req = (uv_write_t*)malloc(sizeof(uv_write_t));
    // Simple message
    uv_buf_t buf = uv_buf_init("Hello, world!\n", 13);
    // Write the message to the client stream
    // See docs: https://docs.libuv.org/en/v1.x/stream.html#c.uv_write
    uv_write(write_req, (uv_stream_t*)client, &buf, 1, NULL);
  }

  // Close the connection handle no matter what
  // See docs: https://docs.libuv.org/en/v1.x/handle.html#c.uv_close
  uv_close((uv_handle_t*)client, NULL);
}

int main (int arc, char** argv) {
  // Allow the user to pass the port as an argument
  int port;
  if (arc < 2) {
    port = 1234;
  } else {
    port = atoi(argv[1]);
  }

  // Create the event loop
  // See docs: https://docs.libuv.org/en/v1.x/loop.html#c.uv_default_loop
  uv_loop_t* loop = uv_default_loop();

  // Init our TCP handle
  // See docs: https://docs.libuv.org/en/v1.x/tcp.html#c.uv_tcp_init
  uv_tcp_t server;
  r = uv_tcp_init(loop, &server);
  if (r < 0) {
    fprintf(stderr, "Error: %s", uv_strerror(r));
    return r;
  }

  // Convert the "0.0.0.0" string to a sockaddr_in struct
  // See docs: https://docs.libuv.org/en/v1.x/misc.html#c.uv_ip4_addr
  r = uv_ip4_addr("0.0.0.0", port, &addr);
  if (r < 0) {
    fprintf(stderr, "Error: %s", uv_strerror(r));
    return r;
  }

  // Bind the handle to the address
  // See docs: https://docs.libuv.org/en/v1.x/tcp.html#c.uv_tcp_bind
  r = uv_tcp_bind(&server, (const struct sockaddr*)&addr, 0);
  if (r < 0) {
    fprintf(stderr, "Error: %s", uv_strerror(r));
    return r;
  }

  // Start listening for incoming connections
  // See docs: https://docs.libuv.org/en/v1.x/stream.html#c.uv_listen
  r = uv_listen((uv_stream_t*)&server, 128, on_connection);
  if (r < 0) {
    fprintf(stderr, "Error: %s", uv_strerror(r));
    return r;
  }

  return uv_run(loop, UV_RUN_DEFAULT);
}
