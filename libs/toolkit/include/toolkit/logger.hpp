#pragma once

#include <string_view>
#include <fmt/format.h>
#include <spdlog/spdlog.h>

namespace tk
{
	enum class LogLevel
	{
		Trace = spdlog::level::trace,
		Info = spdlog::level::info,
		Warn = spdlog::level::warn,
		Error = spdlog::level::err
	};

	class Logger
	{
	public:
		Logger(std::string_view name);

		template<typename... T>
		void log(LogLevel level, fmt::format_string<T...> fmt, T&&... args)
		{
			mLogger->log(static_cast<spdlog::level::level_enum>(level), fmt, std::forward<T>(args)...);
		}

#define HELPER(name) template<typename... T> void name##(fmt::format_string<T...> fmt, T&&... args) { mLogger->##name##(fmt, std::forward<T>(args)...); }
		HELPER(trace);
		HELPER(info);
		HELPER(warn);
		HELPER(error);
#undef HELPER
	private:
		std::shared_ptr<spdlog::logger> mLogger;
	};
}