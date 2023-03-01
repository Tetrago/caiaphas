project(mvtk)

find_package(Vulkan REQUIRED)

add_library(mvtk STATIC
	"include/mvtk/extension.hpp"
	"include/mvtk/instance.hpp"

	"src/extension.cpp"
	"src/instance.cpp")

target_compile_features(mvtk PUBLIC cxx_std_20)

target_link_libraries(mvtk PUBLIC Vulkan::Vulkan)
target_include_directories(mvtk PUBLIC "include")
