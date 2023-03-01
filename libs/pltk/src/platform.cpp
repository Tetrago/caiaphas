#include "pltk/platform.hpp"

#include <stdexcept>

#include "log.hpp"

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
		else
		{
			logger().info("Initialized platform handler");
		}
	}

	Platform::~Platform() noexcept
	{
		if(--sCount > 0) return;

		glfwTerminate();
		logger().info("Platform handler destructed");
	}

	Window Platform::createWindow(const WindowCreateInfo& createInfo)
	{
		return Window(createInfo);
	}

	void Platform::update() noexcept
	{
		glfwPollEvents();
	}

	std::vector<const char*> Platform::getRequiredExtensions() noexcept
	{
		uint32_t count;
		const char** extensions = glfwGetRequiredInstanceExtensions(&count);

		return std::vector<const char*>(extensions, extensions + count);
	}
}