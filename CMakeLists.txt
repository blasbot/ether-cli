cmake_minimum_required(VERSION 3.22)

project(eth-cli)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory("lib/eth-rpc")

# The location of our rpc library
set(RPC_LIB "${CMAKE_SOURCE_DIR}/lib/eth-rpc/build/x64-Release/eth-rpc.lib")

# Include directories
include_directories(
	${CURL_INCLUDE_DIR}
	${JSONCPP_INCLUDE_DIR}
	${BOOST_INCLUDEDIR}
	"${PROJECT_SOURCE_DIR}/lib/eth-rpc/include"
)

add_executable(${PROJECT_NAME} "src/shell.cpp" "src/app.cpp" "src/commands.cpp")

find_package(CURL REQUIRED) # libcurl
find_package(JSONCPP REQUIRED) # jsoncpp
find_package(Boost REQUIRED) # boost

target_link_libraries(${PROJECT_NAME}
	eth-rpc
	CURL::libcurl
	Boost::boost
	${JSONCPP_LIBRARY}
)
