cmake_minimum_required(VERSION 3.16)
project(AdsUI)

set(CMAKE_CXX_STANDARD 11)  
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(Threads REQUIRED)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)

#find_library(WIRINGPI_LIB wiringPi)

file(GLOB_RECURSE hdrs "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp")
file(GLOB_RECURSE srcs "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
list(FILTER srcs EXCLUDE REGEX ".*/build/.*")
list(FILTER hdrs EXCLUDE REGEX ".*/build/.*")

add_executable(${PROJECT_NAME} ${srcs} ${hdrs})

target_include_directories(${PROJECT_NAME} PRIVATE ${GTKMM_INCLUDE_DIRS})
#target_link_libraries(${PROJECT_NAME} ${GTKMM_LIBRARIES} ${WIRINGPI_LIB})
target_link_libraries(${PROJECT_NAME} PRIVATE ${GTKMM_LIBRARIES})
target_compile_options(${PROJECT_NAME} PRIVATE ${GTKMM_CFLAGS_OTHER})
target_link_libraries(AdsUI PRIVATE Threads::Threads)
