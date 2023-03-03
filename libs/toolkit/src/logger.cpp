#include "toolkit/logger.hpp"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace tk
{
	Logger::Builder& Logger::Builder::toStdOut() noexcept
	{
		mSinks.push_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
		return *this;
	}

	Logger::Builder& Logger::Builder::toFile(const std::filesystem::path& path) noexcept
	{
		mSinks.push_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>(path.string(), true));
		return *this;
	}

	Logger::Logger(const Builder& builder) noexcept
		: mLogger(std::string(builder.mName), builder.mSinks.begin(), builder.mSinks.end())
	{
#ifndef NDEBUG
		mLogger.set_level(spdlog::level::trace);
#endif
	}
}