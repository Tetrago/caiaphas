project(pltk)

find_package(glfw3 CONFIG REQUIRED)

add_library(pltk STATIC
	"include/pltk/platform.hpp"
	"include/pltk/window.hpp"

	"src/log.cpp"
	"src/log.hpp"
	"src/platform.cpp"
	"src/window.cpp")

target_compile_features(pltk PUBLIC cxx_std_20)

target_link_libraries(pltk PUBLIC toolkit glfw)
target_include_directories(pltk PUBLIC "include" PRIVATE "src")
