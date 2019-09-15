CC = gcc
libuvHeader = "deps/uv/include"
libuvFolder = "deps/uv/build/Release"
ECHO = echo

.PHONY: all
all: check chmod mkdir readFile writeFile idle poll prepare signal timer

.PHONY: check
check:
	$(CC) -I${libuvHeader} -o build/chmod check/check.cc -L${libuvFolder} -luv
	$(ECHO) "This is a regular file" > build/file.txt

.PHONY: chmod
chmod:
	$(CC) -I${libuvHeader} -o build/chmodSync fs/chmod/chmod.cc -L${libuvFolder} -luv
	$(CC) -I$(libuvHeader) -o build/chmodAsync fs/chmod/chmodAsync.cc -L${libuvFolder} -luv

.PHONY: mkdir
mkdir:
	$(CC) -I${libuvHeader} -o build/mkdirSync fs/mkdir/mkdirSync.cc -L${libuvFolder} -luv
	$(CC) -I$(libuvHeader) -o build/mkdirAsync fs/mkdir/mkdirAsync.cc -L${libuvFolder} -luv

.PHONY: readFile
readFile:
	$(CC) -I$(libuvHeader) -o build/readFileSync fs/readFile/readFileSync.cc -L${libuvFolder} -luv
	$(CC) -I$(libuvHeader) -o build/readFileAsync fs/readFile/readFileAsync.cc -L${libuvFolder} -luv
	$(ECHO) "This is a regular file" > build/file.txt

.PHONY: writeFile
writeFile:
	$(CC) -I$(libuvHeader) -o build/writeFileSync fs/writeFile/writeFileSync.cc -L${libuvFolder} -luv
	$(CC) -I$(libuvHeader) -o build/writeFileAsync fs/writeFile/writeFileAsync.cc -L${libuvFolder} -luv

.PHONY: idle
idle:
	$(CC) -I$(libuvHeader) -o build/idle idle/idle.cc -L${libuvFolder} -luv

.PHONY: poll
poll:
	$(CC) -I$(libuvHeader) -o build/poll idle/idle.cc -L${libuvFolder} -luv

.PHONY: prepare
prepare:
	$(CC) -I$(libuvHeader) -o build/prepare prepare/prepare.cc -L${libuvFolder} -luv

.PHONY: signal
signal:
	$(CC) -I$(libuvHeader) -o build/signal signals/signal.cc -L${libuvFolder} -luv

.PHONY: timer
timer:
	$(CC) -I$(libuvHeader) -o build/timer timer/timer.cc -L${libuvFolder} -luv

.PHONY: fsevent
fsevent:
	$(CC) -I$(libuvHeader) -o build/watcher fs_event/watcher.cc -L${libuvFolder} -luv
	$(ECHO) "This is a regular file" > build/file.txt

.PHONY: clean
clean:
	rm -rf deps build
