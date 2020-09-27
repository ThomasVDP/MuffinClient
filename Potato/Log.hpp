#ifndef POTATO_ENGINE_LOG_HPP
#define POTATO_ENGINE_LOG_HPP

#ifndef SPDLOG_FMT_EXTERNAL
#define SPDLOG_FMT_EXTERNAL
#endif
#include "spdlog/spdlog.h"

#include <memory>

namespace Potato
{
	class Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}	// namespace Potato

#define POTATO_SOURCE_MACRO spdlog::source_loc(__FILE__, __LINE__, static_cast<const char*>(__FUNCTION__))
// Core log macros
#define POTATO_CORE_TRACE(...) ::Potato::Log::GetCoreLogger()->log(POTATO_SOURCE_MACRO, spdlog::level::trace, __VA_ARGS__)
#define POTATO_CORE_INFO(...)  ::Potato::Log::GetCoreLogger()->log(POTATO_SOURCE_MACRO, spdlog::level::info, __VA_ARGS__)
#define POTATO_CORE_WARN(...)  ::Potato::Log::GetCoreLogger()->log(POTATO_SOURCE_MACRO, spdlog::level::warn, __VA_ARGS__)
#define POTATO_CORE_ERROR(...) ::Potato::Log::GetCoreLogger()->log(POTATO_SOURCE_MACRO, spdlog::level::err, __VA_ARGS__)
#define POTATO_CORE_FATAL(...) ::Potato::Log::GetCoreLogger()->log(POTATO_SOURCE_MACRO, spdlog::level::critical, __VA_ARGS__)
// Core debug log macro
#define POTATO_CORE_DEBUG(...) ::Potato::Log::GetCoreLogger()->log(POTATO_SOURCE_MACRO, spdlog::level::debug, __VA_ARGS__)

//SPDLOG_TRACE()

// Client log macros
#define POTATO_TRACE(...) ::Potato::Log::GetClientLogger()->log(POTATO_SOURCE_MACRO, spdlog::level::trace, __VA_ARGS__)
#define POTATO_INFO(...)  ::Potato::Log::GetClientLogger()->log(POTATO_SOURCE_MACRO, spdlog::level::info, __VA_ARGS__)
#define POTATO_WARN(...)  ::Potato::Log::GetClientLogger()->log(POTATO_SOURCE_MACRO, spdlog::level::warn, __VA_ARGS__)
#define POTATO_ERROR(...) ::Potato::Log::GetClientLogger()->log(POTATO_SOURCE_MACRO, spdlog::level::err, __VA_ARGS__)
#define POTATO_FATAL(...) ::Potato::Log::GetClientLogger()->log(POTATO_SOURCE_MACRO, spdlog::level::critical, __VA_ARGS__)
// Client debug log macro
#define POTATO_DEBUG(...) ::Potato::Log::GetClientLogger()->log(POTATO_SOURCE_MACRO, spdlog::level::debug, __VA_ARGS__)

#endif