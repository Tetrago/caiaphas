#include "pltk/window.hpp"

#include <stdexcept>

#include "pltk/platform.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace pltk
{
	Window::Window(const WindowCreateInfo& createInfo)
		: mWidth(createInfo.width)
		, mHeight(createInfo.height)
	{
		glfwDefaultWindowHints();
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

		mHandle = glfwCreateWindow(mWidth, mHeight, createInfo.title.c_str(), nullptr, nullptr);
		if(!mHandle)
		{
			throw std::runtime_error("Failed to create window");
		}

		glfwSetWindowUserPointer(mHandle, this);

		glfwSetWindowCloseCallback(mHandle, [](GLFWwindow* handle) { pushEvent(handle, { WindowEvent::Close }); });
	}

	Window::~Window() noexcept
	{
		glfwDestroyWindow(mHandle);
	}

	Window::Window(Window&& other) noexcept
		: mWidth(other.mWidth)
		, mHeight(other.mHeight)
		, mHandle(other.mHandle)
		, mEvents(std::move(other.mEvents))
	{
		glfwSetWindowUserPointer(mHandle, this);
	}

	bool Window::poll(WindowEvent& event) noexcept
	{
		if(mEvents.empty()) return false;

		event = mEvents.top();
		mEvents.pop();
		return true;
	}

	void Window::pushEvent(GLFWwindow* handle, WindowEvent&& event) noexcept
	{
		static_cast<Window*>(glfwGetWindowUserPointer(handle))->mEvents.push(std::move(event));
	}
}