/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** logger
*/

#include "logger/Logger.hpp"
#include <array>
#include <cstdarg>

extern "C"
{
#include <raylib.h>
}

namespace raylib
{
    static void raylibLogger(int msgType, const char *text, va_list args)
    {
        static Logger raylibLogger("log_raylib.txt", true);
        Logger::Severity severity;
        std::array<char, 1024> buffer;

        switch (msgType) {
            case LOG_TRACE: severity = Logger::Severity::Debug; break;
            case LOG_DEBUG: severity = Logger::Severity::Debug; break;
            case LOG_INFO: severity = Logger::Severity::Information; break;
            case LOG_WARNING: severity = Logger::Severity::Warning; break;
            case LOG_ERROR: severity = Logger::Severity::Error; break;
            case LOG_FATAL: severity = Logger::Severity::Error; break;
            default: return;
        }
        vsnprintf(buffer.data(), 1024, text, args);
        raylibLogger.log(severity, buffer.data());
    }

    void initLogger(int logLevel)
    {
        SetTraceLogCallback(raylibLogger);
        SetTraceLogLevel(logLevel);
    }
} // namespace raylib
