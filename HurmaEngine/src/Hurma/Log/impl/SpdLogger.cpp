#include "SpdLogger.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

SpdLogger::SpdLogger() 
{
    mSpdLogger = spdlog::stdout_color_mt("HurmaEngine");
}

void SpdLogger::warn(const std::string& msg) 
{
    mSpdLogger->warn(msg);
}

void SpdLogger::error(const std::string& msg) 
{
    mSpdLogger->error(msg);
}

void SpdLogger::info(const std::string& msg) 
{
    mSpdLogger->info(msg);
}

void SpdLogger::trace(const std::string& msg) 
{
    mSpdLogger->trace(msg);
}
