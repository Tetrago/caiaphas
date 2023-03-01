#include "toolkit/logger.hpp"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace tk
{
	Logger::Logger(std::string_view name)
		: mLogger(spdlog::stdout_color_mt(std::string(name)))
	{
#ifndef NDEBUG
		mLogger->set_level(spdlog::level::trace);
#endif
	}
}