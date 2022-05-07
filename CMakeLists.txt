cmake_minimum_required(VERSION 3.0)

project (uvxamples)

message(STATUS "Building in ${CMAKE_BUILD_TYPE} mode")
message(STATUS "Building with ${CMAKE_C_COMPILER_ID} ${CMAKE_C_COMPILER_VERSION} on ${CMAKE_SYSTEM}")

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} -DDEBUG -O0 -g3")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS} -DNDEBUG -O2 -g")

option(libuv_buildtests "" OFF)
add_subdirectory(deps/libuv EXCLUDE_FROM_ALL)

link_libraries(uv_a)

function(COMPILE_EXAMPLE)
  message("Compiling \"${FILE_ROUTE}\" into \"./example\"")
  add_executable(example ${FILE_ROUTE})
endfunction()

COMPILE_EXAMPLE()

# Special thanks to Saúl Ibarra for the recomendation of using Cmake
# to build Libuv and this project, also, a huge part of this code was
# taken from his project txiki.js https://github.com/saghul/txiki.js
