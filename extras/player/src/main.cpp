#include <mvtk/mvtk.hpp>

int main(int argc, char** argv)
{
	mvtk::Instance instance = mvtk::Instance::builder()
		.name("player")
		.version(0, 1, 0)
		.build();
}