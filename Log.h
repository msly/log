#pragma once

#include "spdlog/spdlog.h"
namespace spd = spdlog;

class CLog
{
public:
    CLog();
    ~CLog();

    CLog(const CLog&) = delete;
    CLog& operator =(const CLog&) = delete;
    CLog(CLog&&) = delete;
};

extern CLog nono;
//#define LOG_DEBUG (spd::get("log")->debug())
//#define LOG_INFO (spd::get("log")->info())
//#define LOG_ERROR (spd::get("log")->error())
// new version
// spd::get("log")->debug("{}", "hello");