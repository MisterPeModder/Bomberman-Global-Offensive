/*
** EPITECH PROJECT, 2022
** Indie Studio
** File description:
** Logger
*/

#include "Logger.hpp"
#include <ctime>
#include <iomanip>
#include <map>
#include <sstream>
#include <thread>

/// GetCurrentProcessId() / getpid()
#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

Logger Logger::logger;

Logger::Logger(std::ostream &stream)
{
    setStream(stream);
    setLogInfos(LogInfo::Time);
}

Logger::Logger(std::string_view filename)
{
    setOutputFile(filename);
    setLogInfos(LogInfo::Time);
}

void Logger::displayTime(std::stringstream &ss, std::string_view format)
{
    std::time_t now = std::time(nullptr);

#ifdef _WIN32
    tm loctm;
    localtime_s(&loctm, &now);
    ss << std::put_time(&loctm, format.data());
#else
    ss << std::put_time(std::localtime(&now), format.data());

#endif
}

void Logger::displayInformations(std::stringstream &ss)
{
    bool firstInfo = true;
    auto add_info = [&, this](std::string_view name, std::function<void(void)> writeInfo) {
        if (!firstInfo)
            ss << " ";
        if (name.size() > 0) {
            ss << name << "(";
            writeInfo();
            ss << ")";
        } else
            writeInfo();
        firstInfo = false;
    };

    if ((*this)[LogInfo::PID])
        add_info("PID", [&]() {
#ifdef _WIN32
            ss << GetCurrentProcessId();
#else
            ss << getpid();
#endif
        });
    if ((*this)[LogInfo::ThreadId])
        add_info("ThreadID", [&]() { ss << std::this_thread::get_id(); });
    if ((*this)[LogInfo::Date])
        add_info("", [&]() { displayTime(ss, "%x"); });
    if ((*this)[LogInfo::Time])
        add_info("", [&]() { displayTime(ss, "%X"); });
    if (!firstInfo)
        ss << " ";
}

void Logger::log(Severity severity, std::function<void(std::ostream &)> writer)
{
    if (severity < _logLevel)
        return;
    static std::map<Severity, const char *> severityNames = {{Severity::Debug, "DEBUG"},
        {Severity::Information, "INFO"}, {Severity::Warning, "WARN"}, {Severity::Error, "ERROR"}};
    std::stringstream ss;

    displayInformations(ss);
    ss << "[" << severityNames[severity] << "] : ";
    writer(ss);
    ss << std::endl;
    (*_streamPointer) << ss.str();
}

void Logger::log(Severity severity, std::string_view content)
{
    log(severity, [&](std::ostream &ss) { ss << content; });
}

void Logger::flush() { _streamPointer->flush(); }

void Logger::setStream(std::ostream &stream)
{
    if (_fileStream.is_open())
        _fileStream.close();
    _streamPointer = &stream;
}

void Logger::setOutputFile(std::string_view filename)
{
    if (_fileStream.is_open())
        _fileStream.close();
    _fileStream.open(filename.data(), std::ios_base::app | std::ios_base::out);
    if (!_fileStream.is_open()) {
        _streamPointer = &std::cerr;
        throw std::runtime_error("Invalid logger output file.");
    }
    _streamPointer = &_fileStream;
}

void Logger::setLogLevel(Severity logLevel) { _logLevel = logLevel; }

Logger::Severity Logger::getLogLevel() const { return _logLevel; }

void Logger::clearLogInfos() { enableLogInfo(false, LogInfo::PID, LogInfo::ThreadId, LogInfo::Date, LogInfo::Time); }

void Logger::enableLogInfo(bool enabled, LogInfo info) { (*this)[info] = enabled; }

bool Logger::operator[](LogInfo logInfo) const { return _infos[static_cast<size_t>(logInfo)]; }

bool &Logger::operator[](LogInfo logInfo) { return _infos[static_cast<size_t>(logInfo)]; }
