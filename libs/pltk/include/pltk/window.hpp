#pragma once

#include <stack>
#include <string>

struct GLFWwindow;

namespace pltk
{
	class Window;

	struct WindowEvent
	{
		enum Type
		{
			Close
		};

		Type type;
	};

	class Window
	{
	public:
		Window(int width, int height, const std::string& title);
		~Window() noexcept;

		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;
		Window(Window&& other) noexcept;
		Window& operator=(Window&&) = delete;

		bool poll(WindowEvent& event) noexcept;

		int width() const noexcept { return mWidth; }
		int height() const noexcept { return mHeight; }
	private:
		static void pushEvent(GLFWwindow* handle, WindowEvent&& event) noexcept;

		int mWidth;
		int mHeight;
		GLFWwindow* mHandle;
		std::stack<WindowEvent> mEvents;
	};
}