#pragma once

#include <span>

#include "window.hpp"

namespace pltk
{
	class Platform
	{
	public:
		Platform();
		~Platform() noexcept;

		Platform(const Platform&) = delete;
		Platform& operator=(const Platform&) = delete;

		Window createWindow(const WindowCreateInfo& createInfo);

		void update() noexcept;
		std::span<const char*> getRequiredExtensions() noexcept;
	private:
		inline static int sCount = 0;
	};
}