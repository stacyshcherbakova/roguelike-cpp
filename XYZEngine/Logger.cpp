#include "pch.h"
#include "Logger.h"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>

namespace XYZEngine
{
	void ConsoleSink::Write(LogLevel level, const std::string& line)
	{
		if (level >= LogLevel::Warning)
		{
			std::cerr << line << std::endl;
		}
		else
		{
			std::cout << line << std::endl;
		}
	}

	FileSink::FileSink(const std::string& filePath)
		: file(filePath, std::ios::app)
	{
	}

	void FileSink::Write(LogLevel level, const std::string& line)
	{
		if (file.is_open())
		{
			file << line << std::endl;
		}
	}

	Logger* Logger::Instance()
	{
		static Logger logger;
		return &logger;
	}

	Logger::Logger()
	{
#ifdef NDEBUG
		minLevel = LogLevel::Info;
#else
		minLevel = LogLevel::Debug;
#endif
	}

	void Logger::AddSink(std::unique_ptr<LogSink> sink)
	{
		std::lock_guard<std::mutex> lock(mutex);
		if (sink != nullptr)
		{
			sinks.push_back(std::move(sink));
		}
	}

	void Logger::ClearSinks()
	{
		std::lock_guard<std::mutex> lock(mutex);
		sinks.clear();
	}

	void Logger::SetMinLevel(LogLevel level)
	{
		minLevel = level;
	}

	LogLevel Logger::GetMinLevel() const
	{
		return minLevel;
	}

	void Logger::Log(LogLevel level, const std::string& message)
	{
		if (level < minLevel)
		{
			return;
		}

		std::lock_guard<std::mutex> lock(mutex);
		if (sinks.empty())
		{
			AddDefaultSinks();
		}

		const auto now = std::chrono::system_clock::now();
		const std::time_t time = std::chrono::system_clock::to_time_t(now);
		std::tm localTime;
		localtime_s(&localTime, &time);
		const auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count() % 1000;

		std::ostringstream line;
		line << std::put_time(&localTime, "%H:%M:%S") << '.' << std::setfill('0') << std::setw(3) << milliseconds
			<< " [" << LevelName(level) << "] " << message;

		const std::string formatted = line.str();
		for (auto& sink : sinks)
		{
			sink->Write(level, formatted);
		}
	}

	const char* Logger::LevelName(LogLevel level)
	{
		switch (level)
		{
		case LogLevel::Debug: return "DEBUG";
		case LogLevel::Info: return "INFO";
		case LogLevel::Warning: return "WARNING";
		case LogLevel::Error: return "ERROR";
		default: return "UNKNOWN";
		}
	}

	void Logger::AddDefaultSinks()
	{
		sinks.push_back(std::make_unique<ConsoleSink>());
		sinks.push_back(std::make_unique<FileSink>("log.txt"));
	}
}
