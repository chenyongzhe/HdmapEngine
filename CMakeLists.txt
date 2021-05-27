project(HdmapEngine)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_STANDARD 11)
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
find_package( Eigen3 REQUIRED )

include_directories(${EIGEN3_INCLUDE_DIRS})
file(GLOB LIBS "${PROJECT_SOURCE_DIR}/libs/*")
file(GLOB SRCS "${PROJECT_SOURCE_DIR}/src/*")
file(GLOB ELESRCS "${PROJECT_SOURCE_DIR}/src/element/*")
file(GLOB TINEYXMLSRCS "${PROJECT_SOURCE_DIR}/src/tinyxml/*")
file(GLOB TOOLSSRCS "${PROJECT_SOURCE_DIR}/src/tools/*")
file(GLOB MAPSRCS "${PROJECT_SOURCE_DIR}/src/HdMapEngine/*")



include_directories(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/libs)

add_executable(HdmapEngine src/main.cpp ${MAPSRCS} ${ELESRCS} ${TINEYXMLSRCS} ${TOOLSSRCS})
add_executable(OutputPoint src/OutputPoint.cpp ${MAPSRCS}  ${ELESRCS} ${TINEYXMLSRCS} ${TOOLSSRCS})
target_link_libraries(HdmapEngine ${LIBS} ${Eigen_LIBRARIES})
target_link_libraries(OutputPoint ${LIBS} ${Eigen_LIBRARIES})

 