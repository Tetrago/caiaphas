project(pltk)

find_package(glfw3 CONFIG REQUIRED)

add_library(pltk STATIC
	"src/platform.cpp"
	"src/window.cpp")

target_compile_features(pltk PUBLIC cxx_std_17)

target_link_libraries(pltk PUBLIC glfw)
target_include_directories(pltk PUBLIC "include")
