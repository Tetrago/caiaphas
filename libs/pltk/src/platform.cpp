#include "pltk/platform.hpp"

#include <stdexcept>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace pltk
{
	Platform::Platform()
	{
		if(sCount++ > 0) return;
		
		if(!glfwInit())
		{
			throw std::runtime_error("Failed to initialize GLFW");
		}
	}

	Platform::~Platform() noexcept
	{
		if(--sCount > 0) return;
		glfwTerminate();
	}

	Window Platform::createWindow(const WindowCreateInfo& createInfo)
	{
		return Window(createInfo);
	}

	void Platform::update() noexcept
	{
		glfwPollEvents();
	}

	std::span<const char*> Platform::getRequiredExtensions() noexcept
	{
		uint32_t count;
		const char** extensions = glfwGetRequiredInstanceExtensions(&count);

		return std::span<const char*>(extensions, count);
	}
}