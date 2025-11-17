#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <memory>

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace Editor
{

	class Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetLogger() { return m_logger; }

	private:
		static std::shared_ptr<spdlog::logger> m_logger;
	};

}

#ifdef ED_DEBUG

	#define ED_LOG_TRACE(...)    ::Editor::Log::GetLogger()->trace(__VA_ARGS__)
	#define ED_LOG_INFO(...)     ::Editor::Log::GetLogger()->info(__VA_ARGS__)
	#define ED_LOG_WARN(...)     ::Editor::Log::GetLogger()->warn(__VA_ARGS__)
	#define ED_LOG_ERROR(...)    ::Editor::Log::GetLogger()->error(__VA_ARGS__)

	#define ED_ASSERT(x, ...)		 { if (!x) { ::Editor::Log::GetLogger()->error("Assert error: {0}", __VA_ARGS__); __debugbreak(); } }

#else

	#define ED_LOG_TRACE(...)    
	#define ED_LOG_INFO(...)    
	#define ED_LOG_WARN(...)    
	#define ED_LOG_ERROR(...)    
	
	#define ED_ASSERT(x, ...)

#endif

#endif