#include <mvtk/mvtk.hpp>
#include <pltk/pltk.hpp>

int main(int argc, char** argv)
{
	pltk::Window window(1024, 576, "Player");

	bool running = true;
	while(running)
	{
		pltk::Platform::update();

		pltk::WindowEvent event;
		while(window.poll(event))
		{
			if(event.type == pltk::WindowEvent::Close)
			{
				running = false;
			}
		}
	}

	return 0;
}