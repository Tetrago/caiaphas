#include "log.hpp"

namespace mvtk
{
	tk::Logger& logger() noexcept
	{
		static tk::Logger logger = tk::Logger::builder("mvtk").toStdOut().build();
		return logger;
	}
}