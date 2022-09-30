#pragma once
#include <string>

namespace Hurma{

    class ILog {
     public:
         virtual void warn(const std::string& msg) = 0;
         virtual void error(const std::string& msg) = 0;
         virtual void info(const std::string& msg) = 0;
         virtual void trace(const std::string& msg) = 0;
    };

}