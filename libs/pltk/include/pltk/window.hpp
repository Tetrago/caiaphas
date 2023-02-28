#pragma once

#include <string>

struct GLFWwindow;

namespace pltk
{
	class Window
	{
	public:
		Window(int width, int height, const std::string& title);
		~Window() noexcept;

		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;
		Window(Window&& other) noexcept;
		Window& operator=(Window&&) = delete;
	private:
		GLFWwindow* mHandle;
	};
}