project(HdmapEngine)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_STANDARD 11)
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


file(GLOB LIBS "${PROJECT_SOURCE_DIR}/libs/*")
file(GLOB SRCS "${PROJECT_SOURCE_DIR}/src/*")
file(GLOB ELESRCS "${PROJECT_SOURCE_DIR}/src/element/*")
file(GLOB TINEYXMLSRCS "${PROJECT_SOURCE_DIR}/src/tinyxml/*")


include_directories(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/libs)

add_executable(HdmapEngine ${SRCS} ${ELESRCS} ${TINEYXMLSRCS})
target_link_libraries(HdmapEngine ${LIBS})
