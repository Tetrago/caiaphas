#include "log.hpp"

namespace pltk
{
	tk::Logger& logger() noexcept
	{
		static tk::Logger logger = tk::Logger::builder("pltk").toStdOut().build();
		return logger;
	}
}