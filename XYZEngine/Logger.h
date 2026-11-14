#pragma once

#include <fstream>
#include <memory>
#include <mutex>
#include <sstream>
#include <string>
#include <vector>

namespace XYZEngine
{
	enum class LogLevel
	{
		Debug,
		Info,
		Warning,
		Error
	};

	// Where a formatted log line goes: console, file, anything else added later
	class LogSink
	{
	public:
		virtual ~LogSink() = default;
		virtual void Write(LogLevel level, const std::string& line) = 0;
	};

	class ConsoleSink : public LogSink
	{
	public:
		void Write(LogLevel level, const std::string& line) override;
	};

	class FileSink : public LogSink
	{
	public:
		explicit FileSink(const std::string& filePath);
		void Write(LogLevel level, const std::string& line) override;

	private:
		std::ofstream file;
	};

	// Single entry point for all log messages of the engine and the game.
	// Without explicit setup it writes to the console and to log.txt next to the executable.
	class Logger
	{
	public:
		static Logger* Instance();

		void AddSink(std::unique_ptr<LogSink> sink);
		void ClearSinks();
		void SetMinLevel(LogLevel level);
		LogLevel GetMinLevel() const;

		void Log(LogLevel level, const std::string& message);

		static const char* LevelName(LogLevel level);

	private:
		Logger();
		~Logger() = default;
		Logger(const Logger&) = delete;
		Logger& operator=(const Logger&) = delete;

		void AddDefaultSinks();

		std::vector<std::unique_ptr<LogSink>> sinks;
		LogLevel minLevel = LogLevel::Debug;
		std::mutex mutex;
	};
}

// Stream-style logging: LOG_INFO("Player created at " << x << ", " << y)
#define XYZ_LOG(level, expr) \
	do { \
		std::ostringstream xyzLogStream; \
		xyzLogStream << expr; \
		XYZEngine::Logger::Instance()->Log(level, xyzLogStream.str()); \
	} while (0)

#define LOG_DEBUG(expr) XYZ_LOG(XYZEngine::LogLevel::Debug, expr)
#define LOG_INFO(expr) XYZ_LOG(XYZEngine::LogLevel::Info, expr)
#define LOG_WARNING(expr) XYZ_LOG(XYZEngine::LogLevel::Warning, expr)
#define LOG_ERROR(expr) XYZ_LOG(XYZEngine::LogLevel::Error, expr)
