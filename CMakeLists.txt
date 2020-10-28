cmake_minimum_required(VERSION "3.8.1")
#set (CMAKE_CXX_STANDARD 11)
project("ShopsDeliverySystem")
 
#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "src/*.cpp" "include/*.h")
 
add_executable(ShopsDeliverySystem ${SOURCES})