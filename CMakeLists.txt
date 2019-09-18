cmake_minimum_required(VERSION 2.8)

include_directories("${PROJECT_SOURCE_DIR}/include")

set(PROJECT_BIN_DIR ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_VS_INCLUDE_INSTALL_TO_DEFAULT_BUILD 1)
set(CMAKE_INSTALL_RPATH ${PROJECT_BIN_DIR})

# Add DLL flag for windows shared lib
add_definitions(-DBUILDING_DLL)

add_subdirectory("${PROJECT_SOURCE_DIR}/src")

# Remove DLL flag 
remove_definitions(-DBUILDING_DLL)

add_executable(MAIN test.cpp)

target_link_libraries(MAIN SOCKET)

install (TARGETS MAIN DESTINATION ${PROJECT_BIN_DIR})
