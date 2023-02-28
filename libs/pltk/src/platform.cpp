#include "pltk/platform.hpp"

#include <stdexcept>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace pltk
{
	void Platform::push()
	{
		if(sCount++ > 0) return;
		
		if(!glfwInit())
		{
			throw std::runtime_error("Failed to initialize GLFW");
		}
	}

	void Platform::pop() noexcept
	{
		if(--sCount > 0) return;
		glfwTerminate();
	}

	void Platform::update() noexcept
	{
		glfwPollEvents();
	}
}