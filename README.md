# uvxamples

Special thanks to Saúl Ibarra for the recomendation of using Cmake
to build Libuv and this project, also, a huge part of this code was
taken from his project txiki.js https://github.com/saghul/txiki.js

This project is just for showcasing some examples of [libuv](http://libuv.org/) API.
_Read [basics of libuv](http://docs.libuv.org/en/v1.x/guide/basics.html#basics-of-libuv) first_.

## Building:

This use CMake and Make as building tools, so we can run multiplatform!

Run `FILE=fileRoute ./build.sh`, yes, that's it!

Debug objects could be generated by providing the `BUILD_TYPE` environment variable
("Release" is the default build mode):

```sh
$ BUILD_TYPE=Debug FILE=./src/timer/timer.c ./build.sh
```

## Running examples:

```sh
$ FILE=./src/timer/timer.c ./build.sh
$ ./build/example
```

## Example index:

* check: [check phase example](/src/check)
* fs: [file system operations examples](/src/fs)
* fs events: [file system events examples](/src/fs_events)
* idle: [idle examples](/src/idle)
* loop: [event loop API examples](/src/loop)
* metrics: [libuv metrics operations](/src/metrics)
* misc: [misc examples](/src/misc)
* poll: [polling phase example](/src/poll)
* prepare: [prepare phase example](/src/prepare)
* signals: [signal examples](/src/signals)
* tcp: [tcp examples](/src/tcp)
* timer: [timer examples](/src/timer)

## Dependencies:

1. Cmake (at least 3.0).

## PS: the content presented here is just for educational purposes.
