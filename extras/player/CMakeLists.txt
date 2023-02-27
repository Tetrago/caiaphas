project(player)

add_executable(player
	"src/main.cpp")

target_link_libraries(player PRIVATE mvtk)
