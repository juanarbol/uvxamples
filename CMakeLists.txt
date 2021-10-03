cmake_minimum_required(VERSION 3.0)

project (uvxamples)

message(STATUS "Building in ${CMAKE_BUILD_TYPE} mode")
message(STATUS "Building with ${CMAKE_C_COMPILER_ID} ${CMAKE_C_COMPILER_VERSION} on ${CMAKE_SYSTEM}")

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} -DDEBUG -O0 -g3")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS} -DNDEBUG -O2 -g")

option(libuv_buildtests "" OFF)
add_subdirectory(deps/libuv EXCLUDE_FROM_ALL)

link_libraries(uv_a)

# Check example.
add_executable(check src/check/check.c)

# File system examples.
add_executable(chmod src/fs/chmod/chmod.c)
add_executable(chmodAsync src/fs/chmod/chmodAsync.c)
add_executable(mkdir src/fs/mkdir/mkdirSync.c)
add_executable(mkdirAsync src/fs/mkdir/mkdirAsync.c)
add_executable(readFile src/fs/readFile/readFileSync.c)
add_executable(readFileAsync src/fs/readFile/readFileAsync.c)
add_executable(writeFile src/fs/writeFile/writeFileSync.c)
add_executable(writeFileAsync src/fs/writeFile/writeFileAsync.c)

# Fs event example.
add_executable(watcher src/fs_event/watcher.c)

# Idle example.
add_executable(idle src/idle/idle.c)

# Poll example.
add_executable(poll src/poll/poll.c)

# Prepare example.
add_executable(prepare src/prepare/prepare.c)

# Signals example.
add_executable(signals src/signals/signal.c)

# Tcp example.
add_executable(tcp-server src/tcp/tcp-server.c)
add_executable(tcp-client src/tcp/tcp-client.c)

# Timer example.
add_executable(timer src/timer/timer.c)

# Special thanks to Saúl Ibarra for the recomendation of using Cmake
# to build Libuv and this project, also, a huge part of this code was
# taken from his project txiki.js https://github.com/saghul/txiki.js
