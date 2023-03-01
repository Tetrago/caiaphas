#include "log.hpp"

namespace mvtk
{
	tk::Logger& logger() noexcept
	{
		static tk::Logger logger("mvtk");
		return logger;
	}
}