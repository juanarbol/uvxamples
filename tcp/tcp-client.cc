#include <uv.h>
#include <stdio.h>
#include <math.h>

static uv_loop_t *loop;
static uv_tcp_t server;
static int r;

typedef struct {
  uv_write_t req;
  uv_buf_t buf;
} write_req_t;

static void on_connection(uv_stream_t*, int);
static void alloc_cb(uv_handle_t*, size_t, uv_buf_t*);
static void read_cb(uv_stream_t*, ssize_t, const uv_buf_t*);
static void write_cb(uv_write_t*, int);

void CHECK(int code) {
  if (code < 0) {
    fprintf(stderr, "Error: %s\n", uv_strerror(code));
  }
}

int main() {
  loop = uv_default_loop();

  r = uv_tcp_init(loop, &server);
  CHECK(r);

  struct sockaddr_in addr;
  r = uv_ip4_addr("0.0.0.0", 7000, &addr);
  CHECK(r);
  
  r = uv_tcp_bind(&server, (const struct sockaddr*)&addr, 0);
  CHECK(r);

  r = uv_listen((uv_stream_t*)&server, 128, on_connection);
  CHECK(r);

  return uv_run(loop, UV_RUN_DEFAULT);
}

void on_connection(uv_stream_t *server, int status) {
  CHECK(status);

  uv_tcp_t *client;

  r = uv_tcp_init(server->loop, client);
  CHECK(r);

  r = uv_accept(server, (uv_stream_t*) client);
  CHECK(r);

  r = uv_read_start((uv_stream_t*) client, alloc_cb, read_cb);
  CHECK(r);
}

static void alloc_cb(uv_handle_t *handle, size_t size, uv_buf_t *buf) {
  // buf->len = size;
  // if (buf->base == NULL) {
  //   fprintf(stderr, "Error initialiacing buffer\n");
  // }
}

static void read_cb(uv_stream_t* client, ssize_t nread, const uv_buf_t* buf) {
  // int r = 0;
  // uv_shutdown_t *shutdown_req;

  /* Errors or EOF */
  // if (nread < 0) {
  //   fprintf(stderr, "Error in EOF or whatever");
  // }

  // if (!strncmp("QUIT", buf->base, fmin(4, 4))) {
    /* Before exiting we need to properly close the server via uv_close */
    /* We can do this synchronously */
    // uv_close((uv_handle_t*) &server, NULL);
  // }

  /* 6. Write same data back to client since we are an *echo* server and thus can reuse the buffer used to read*/
  /*    We wrap the write req and buf here in order to be able to clean them both later */
  write_req_t *write_req;
  write_req->buf = uv_buf_init(buf->base, nread);
  // r = uv_write(&write_req->req, client, &write_req->buf, 1, write_cb);
}


static void write_cb(uv_write_t *req, int status) {
  /* Since the req is the first field inside the wrapper write_req, we can just cast to it */
  /* Basically we are telling C to include a bit more data starting at the same memory location, which in this case is our buf */
  write_req_t *write_req = (write_req_t*) req;
}
