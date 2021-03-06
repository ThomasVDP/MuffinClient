#include "Log.hpp"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace Potato
{
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init(const std::string& t_AppName)
	{
		spdlog::set_pattern("%^[%T] %n/[%l] (%s#%!:%#): %v%$");
		s_CoreLogger = spdlog::stdout_color_mt("POTATO");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt(t_AppName);
		s_ClientLogger->set_level(spdlog::level::trace);
	}
}	// namespace Potato
