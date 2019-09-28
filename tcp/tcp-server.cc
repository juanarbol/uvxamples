#include <stdio.h>
#include <stdlib.h>
#include <uv.h>

static int r;
uv_loop_t* loop;

struct sockaddr_in addr;

void CHECK(int code) {
  if (code < 0) {
    fprintf(stderr, "Error: %s", uv_strerror(code));
  }
}

void alloc_buffer(uv_handle_t* handle, size_t suggested_size, uv_buf_t* buf) {
  buf->base = (char*)malloc(suggested_size);
  buf->len = suggested_size;
}

void echo_write(uv_write_t* req, int status) {
  if (status) {
    fprintf(stderr, "Write error %s\n", uv_strerror(status));
  }
  free(req);
}

void echo_read(uv_stream_t* client, ssize_t nread, const uv_buf_t* buf) {
  if (nread < 0) {
    if (nread != UV_EOF) {
      fprintf(stderr, "Read error %s\n", uv_err_name(nread));
      uv_close((uv_handle_t*)client, NULL);
    }
  } else if (nread > 0) {
    uv_write_t* req = (uv_write_t*)malloc(sizeof(uv_write_t));
    uv_buf_t wrbuf = uv_buf_init(buf->base, nread);
    uv_write(req, client, &wrbuf, 1, echo_write);
  }

  if (buf->base) {
    free(buf->base);
  }
}

void on_connection(uv_stream_t* server, int status) {
  printf("New connection received");
  if (status < 0) {
    fprintf(stderr, "New connection error %s\n", uv_strerror(status));
    return;
  }

  uv_tcp_t* client = (uv_tcp_t*)malloc(sizeof(uv_tcp_t));

  uv_tcp_init(loop, client);
  if (uv_accept(server, (uv_stream_t*)client) == 0) {
    uv_read_start((uv_stream_t*)client, alloc_buffer, echo_read);
  } else {
    uv_close((uv_handle_t*)client, NULL);
  }
}

int main() {
  loop = uv_default_loop();

  uv_tcp_t server;
  r = uv_tcp_init(loop, &server);
  CHECK(r);

  r = uv_ip4_addr("0.0.0.0", 7000, &addr);
  CHECK(r);

  r = uv_tcp_bind(&server, (const struct sockaddr*)&addr, 0);
  CHECK(r);

  r = uv_listen((uv_stream_t*)&server, 128, on_connection);
  CHECK(r);

  return uv_run(loop, UV_RUN_DEFAULT);
}
