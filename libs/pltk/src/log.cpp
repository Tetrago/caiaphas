#include "log.hpp"

namespace pltk
{
	tk::Logger& logger() noexcept
	{
		static tk::Logger logger("pltk");
		return logger;
	}
}