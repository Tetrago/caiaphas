#include <mvtk/mvtk.hpp>
#include <pltk/pltk.hpp>

int main(int argc, char** argv)
{
	pltk::Window window(1024, 576, "Player");

	while(1)
	{
		pltk::Platform::update();
	}

	return 0;
}