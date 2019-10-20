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
add_executable(check src/check/check.cc)

# File system examples.
add_executable(chmod src/fs/chmod/chmod.cc)
add_executable(chmodAsync src/fs/chmod/chmodAsync.cc )
add_executable(mkdir src/fs/mkdir/mkdirSync.cc )
add_executable(mkdirAsync src/fs/mkdir/mkdirAsync.cc )
add_executable(readFile src/fs/readFile/readFileSync.cc )
add_executable(readFileAsync src/fs/readFile/readFileAsync.cc )
add_executable(writeFile src/fs/writeFile/writeFileSync.cc )
add_executable(writeFileAsync src/fs/writeFile/writeFileAsync.cc )

# Fs event example.
add_executable(watcher src/fs_event/watcher.cc )

# Idle example.
add_executable(idle src/idle/idle.cc )

# Poll example.
add_executable(poll src/poll/poll.cc )

# Prepare example.
add_executable(prepare src/prepare/prepare.cc )

# Signals example.
add_executable(signals src/signals/signal.cc )

# Tcp example.
add_executable(tcp-server src/tcp/tcp-server.cc )
add_executable(tcp-client src/tcp/tcp-client.cc )

# Timer example.
add_executable(timer src/timer/timer.cc )
