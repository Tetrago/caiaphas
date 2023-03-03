#pragma once

#include <filesystem>
#include <vector>
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
		class Builder
		{
			friend class Logger;
		public:
			~Builder() noexcept = default;

			Builder(const Builder&) = delete;
			Builder& operator=(const Builder&) = delete;

			Builder& toStdOut() noexcept;
			Builder& toFile(const std::filesystem::path& path) noexcept;

			Logger build() noexcept
			{
				return Logger(*this);
			}
		private:
			Builder(std::string_view name) noexcept
				: mName(name)
			{}

			std::string_view mName;
			std::vector<spdlog::sink_ptr> mSinks;
		};

		~Logger() noexcept = default;

		Logger(const Logger&) = delete;
		Logger& operator=(const Logger&) = delete;
		Logger(Logger&& other) noexcept;
		Logger& operator=(Logger&) = delete;

		template<typename... T>
		void log(LogLevel level, fmt::format_string<T...> fmt, T&&... args)
		{
			mLogger.log(static_cast<spdlog::level::level_enum>(level), fmt, std::forward<T>(args)...);
		}

#define HELPER(name) template<typename... T> void name##(fmt::format_string<T...> fmt, T&&... args) { mLogger.##name##(fmt, std::forward<T>(args)...); }
		HELPER(trace);
		HELPER(info);
		HELPER(warn);
		HELPER(error);
#undef HELPER

		static Builder builder(std::string_view name) noexcept
		{
			return Builder(name);
		}
	private:
		Logger(const Builder& builder) noexcept;

		spdlog::logger mLogger;
	};
}