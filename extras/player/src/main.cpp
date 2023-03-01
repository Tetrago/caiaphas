#include <mvtk/mvtk.hpp>
#include <pltk/pltk.hpp>

int main(int argc, char** argv)
{
	pltk::Platform platform;

	auto instance = mvtk::Instance::builder()
		.name("caiaphas_player")
		.version(0, 1, 0)
		.extension(platform.getRequiredExtensions())
		.build();

	pltk::Window window = platform.createWindow({ 1024, 576, "Player" });

	bool running = true;
	while(running)
	{
		platform.update();

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