#include "pltk/window.hpp"

#include <stdexcept>

#include "pltk/platform.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace pltk
{
	Window::Window(int width, int height, const std::string& title)
	{
		Platform::push();

		glfwDefaultWindowHints();
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

		mHandle = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
		if(!mHandle)
		{
			throw std::runtime_error("Failed to create window");
		}
	}

	Window::~Window() noexcept
	{
		glfwDestroyWindow(mHandle);
		Platform::pop();
	}

	Window::Window(Window&& other) noexcept
		: mHandle(other.mHandle)
	{}
}