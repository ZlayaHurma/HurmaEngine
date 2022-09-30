#include "Log.h"

namespace Hurma {

    std::unique_ptr<ILog> Log::mLoggerImpl;

    void Log::InitLogger(std::unique_ptr<ILog> aLoggerImpl) {
      mLoggerImpl = std::move(aLoggerImpl);
    }
    
    void Log::logInfo(const std::string& msg) { mLoggerImpl->info(msg); }
    
    void Log::logError(const std::string& msg) { mLoggerImpl->error(msg); }
    
    void Log::logWarn(const std::string& msg) { mLoggerImpl->warn(msg); }
    
    void Log::logTrace(const std::string& msg) { mLoggerImpl->trace(msg); }

}  // namespace Hurma