#pragma once
#include "Hurma/Log/ILog.h"
#include "spdlog/logger.h"

class SpdLogger : public Hurma::ILog 
{
 public:
    SpdLogger();

    void warn(const std::string& msg) override;

    void error(const std::string& msg) override;

    void info(const std::string& msg) override;

    void trace(const std::string& msg) override;

 private:
     std::shared_ptr<spdlog::logger> mSpdLogger;  
};
