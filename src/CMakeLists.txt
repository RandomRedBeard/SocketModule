add_library(SOCKET SHARED io.cpp ServerSocket.cpp Socket.cpp)

install (TARGETS SOCKET DESTINATION ${PROJECT_BIN_DIR})