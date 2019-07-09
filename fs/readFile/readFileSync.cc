#include <stdio.h>
#include <uv.h>

#define BUF_SIZE 24

// This program will read content in "./file.txt" using libuv.

// The proccess of reading a file, will be the next one:
// 1. Open the file
// 2. Read the file
// 3. Save the file content into a buffer (result of step 2)
// 4. Print the actual content (the buffer content in step 3)
// 5. Close the file
// 4. Clean up memory

// This variable if for error handling!
static int r;

int main() {
  // Initialize the event loop
  uv_loop_t *loop = uv_default_loop();

  // STEP 1

  // Create a variable, for the open request to the operating system
  uv_fs_t open_req;

  // Open the file, using uv_fs_open()
  // Read API docs before continuing reading this code
  // See docs: http://docs.libuv.org/en/v1.x/fs.html#c.uv_fs_open

  // Explanation:
  // In our declared event loop (see line 14)
  // Save the result at open_req memory address
  // Open the file located at "./file.txt" route
  // With the flag "O_RDONLY" which means 'Open for reading only'
  // With the mode "S_IRUSR" which means 'Read permission for the owner' or '0400'
  // And pass NULL for the callback, this means that this operation will be syncronus
  // Save uv_fs_open() return value in r, when r < 0, means and error ocurred
  // In case of error, r will be the error code

  // Arguments explanation:
  // loop: this is our main event loop
  // &open_req: this is the memory address where libuv save the result of opening operation
  // "./file.txt": this is our file route
  // O_RDONLY: this is the flag for opening th file
  // S_IRUSR: mode or permission code
  // NULL: this is our callback param, send NULL for making this sync
  r = uv_fs_open(loop, &open_req, "./file.txt", O_RDONLY, S_IRUSR, NULL);
  if (r < 0) {
    // This is our little error handler
    // If an error ocurred during opening file, printed using stderr
    // So, we use uv_strerror(), for translate error code to string message
    // See docs: http://docs.libuv.org/en/v1.x/errors.html?highlight=uv_strerror#c.uv_strerror
    fprintf(stderr, "Error opening: %s\n", uv_strerror(r));
  }

  // This is how we declare a buffer
  // In this variable, is where we are going to save file content,
  // this var will be uor buffer
  // BUF_SIZE just means -in this case- the number of bytes or caracters
  // Using uv_buf_init(), we'll initialize a buffer
  // In this case, the base of that buffer will be our buf variable, and the
  // size of that buffer will be BUF_SIZE, so, libuv will initialize our buffer in
  // our variable with the right size
  // See docs: http://docs.libuv.org/en/v1.x/misc.html?highlight=uv_buf_init#c.uv_buf_init
  char buf[BUF_SIZE];

  // Arguments explanation:
  // buf: variable for saving the content
  // BUF_SIZE: unsigned bytes of content
  uv_buf_t iov = uv_buf_init(buf, BUF_SIZE);

  // STEP 2 AND 3

  // Create our read request variable
  uv_fs_t read_req;

  // Read the file using uv_fs_read()
  // Read API docs before continuing reading this code
  // See docs: http://docs.libuv.org/en/v1.x/fs.html?highlight=uv_fs_read#c.uv_fs_read

  // Explanation:
  // In our declared loop (see line 14, again)
  // Save the result at read_req memory address
  // Read the uv_file (open_req.result), see docs at the end
  // Save read content in our buffer memory address
  // The number of unsigned buffers (in this case) is 1
  // The offset, which specifies the file offset at which the input operation is to be performed (in this case) is 0,
  // Send NULL to callback param, this is a sync operation
  // uv_file docs: http://docs.libuv.org/en/v1.x/misc.html#c.uv_file

  // Arguments explanation:
  // loop: our main event loop
  // &read_req: memory address where libuv will save the value of reading operation
  // open_req.result: this is actually the file that we got from uv_fs_open
  // &iov: memory address of our declared buffer
  // 1: the number of unsigned buffers
  // 0: means the offset (see line 88)
  // NULL: this is the callback param, send NULL, to make this operation sync
  r = uv_fs_read(loop, &read_req, open_req.result, &iov, 1, 0, NULL);
  if (r < 0) {
    // Error handler, see line 51
    fprintf(stderr, "Error reading: %s\n", uv_strerror(r));
  }

  // STEP 4

  // At this time, buf variable will be the actual content of our file, just print it
  printf("%s", buf);


  // STEP 5

  // Create our close request variable
  uv_fs_t close_req;

  // Close the file using uv_fs_close()
  // Read API docs before continuing reading this code
  // See docs: http://docs.libuv.org/en/v1.x/fs.html#c.uv_fs_close

  // Explanation:
  // In our declared loop (see line 14, again)
  // Save the result at close_req memory address
  // Close the uv_file (our file)
  // Send NULL to callback param, this is a sync operation

  // Arguments explanation:
  // loop: our main event loop
  // &close_req: memory address where libuv will save the value of closing file operation
  // open_req.result: this is actually the file that we got from uv_fs_open
  // NULL: this is the callback param, send NULL, to make this operation sync
  r = uv_fs_close(loop, &close_req, open_req.result, NULL);
  if (r < 0) {
    // Error handler, see line 51
    fprintf(stderr, "Error closing: %s\n", uv_strerror(r));
  }

  // STEP 6

  // Deallocate memory using uv_fs_req_cleanup()
  // Read API docs before continuing reading this code
  // See docs: http://docs.libuv.org/en/v1.x/fs.html#c.uv_fs_req_cleanup

  // Just free memory used for our open, read and close requests, that's it
  uv_fs_req_cleanup(&open_req);
  uv_fs_req_cleanup(&read_req);
  uv_fs_req_cleanup(&close_req);

  // Run our event loop :D
  // See docs: http://docs.libuv.org/en/v1.x/loop.html#c.uv_run
  uv_run(loop, UV_RUN_DEFAULT);
}
