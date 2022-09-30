#pragma once
#include <memory>
#include "Hurma/Core.h"
#include "ILog.h"

namespace Hurma {

    class HURMA_API Log 
    {
     public:

         static void InitLogger(std::unique_ptr<ILog> aLoggerImpl);

         static void logInfo(const std::string& msg);
    
         static void logError(const std::string& msg);
    
         static void logWarn(const std::string& msg);
    
         static void logTrace(const std::string& msg);

     private:
         #pragma warning(push)
         #pragma warning(disable:4251)
         static std::unique_ptr<ILog> mLoggerImpl;
         #pragma warning(pop)
    };
}
