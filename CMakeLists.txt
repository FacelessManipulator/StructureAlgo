
CMAKE_MINIMUM_REQUIRED(VERSION 3.1)
PROJECT(playground CXX C)
set(CMAKE_CXX_STANDARD 17)

# include directories
INCLUDE_DIRECTORIES(
  ${PROJECT_SOURCE_DIR}/
  /usr/local/include
  /usr/include
)

# lib directories
LINK_DIRECTORIES(
  ${PROJECT_BINARY_DIR}/lib

  /usr/local/lib
  /use/lib

)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

ADD_EXECUTABLE(trie_m Trie/main.cc)
ADD_EXECUTABLE(draw_m draw/main.cc)
