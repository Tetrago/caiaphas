#pragma once

namespace pltk
{
	class Platform
	{
	public:
		static void push();
		static void pop() noexcept;

		static void update() noexcept;
	private:
		Platform() noexcept = default;

		inline static int sCount = 0;
	};
}