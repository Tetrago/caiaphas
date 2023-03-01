project(toolkit)

find_package(spdlog CONFIG REQUIRED)

add_library(toolkit STATIC
	"include/toolkit/logger.hpp"

	"src/logger.cpp")

target_compile_features(toolkit PUBLIC cxx_std_20)

target_link_libraries(toolkit PUBLIC spdlog::spdlog)
target_include_directories(toolkit PUBLIC "include" PRIVATE "src")
