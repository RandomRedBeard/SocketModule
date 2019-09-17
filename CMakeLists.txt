cmake_minimum_required(VERSION 2.8)

include_directories("${PROJECT_SOURCE_DIR}/include")

# Add DLL flag for windows shared lib
add_definitions(-DBUILDING_DLL)

add_subdirectory("${PROJECT_SOURCE_DIR}/src")

# Remove DLL flag 
remove_definitions(-DBUILDING_DLL)

add_executable(MAIN test.cpp)

target_link_libraries(MAIN SOCKET)

set(CMAKE_VS_INCLUDE_INSTALL_TO_DEFAULT_BUILD 1)

install (TARGETS MAIN SOCKET DESTINATION ${PROJECT_SOURCE_DIR}/bin)