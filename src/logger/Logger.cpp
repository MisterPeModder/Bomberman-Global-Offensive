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
    setDefaultColors();
    setStream(stream);
    setLogInfo(LogInfo::Time);
}

Logger::Logger(const std::filesystem::path &filepath, bool clear)
{
    setDefaultColors();
    setOutputFile(filepath, clear);
    setLogInfo(LogInfo::Time);
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
    auto add_info = [&](std::string_view name, std::function<void(void)> writeInfo) {
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

    if (_streamPointer == &std::cout || _streamPointer == &std::cerr)
        ss << "\033[" << 30 + static_cast<size_t>(_colors[static_cast<size_t>(severity)].first) << ";"
           << 40 + static_cast<size_t>(_colors[static_cast<size_t>(severity)].second) << "m";

    displayInformations(ss);
    ss << "[" << severityNames[severity] << "] : ";
    writer(ss);
    if (_streamPointer == &std::cout || _streamPointer == &std::cerr)
        ss << "\033[0m";
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

void Logger::setOutputFile(const std::filesystem::path &filepath, bool clear)
{
    if (_fileStream.is_open())
        _fileStream.close();
    if (!clear)
        _fileStream.open(filepath, std::ios_base::app | std::ios_base::out);
    else
        _fileStream.open(filepath, std::ios_base::out);
    if (!_fileStream.is_open()) {
        _streamPointer = &std::cerr;
        throw std::runtime_error("Invalid logger output file.");
    }
    _streamPointer = &_fileStream;
}

void Logger::setLogLevel(Severity logLevel) { _logLevel = logLevel; }

Logger::Severity Logger::getLogLevel() const { return _logLevel; }

void Logger::clearLogInfo() { enableLogInfo(false, LogInfo::PID, LogInfo::ThreadId, LogInfo::Date, LogInfo::Time); }

void Logger::enableLogInfo(bool enabled, LogInfo info) { (*this)[info] = enabled; }

bool Logger::operator[](LogInfo logInfo) const { return _infos[static_cast<size_t>(logInfo)]; }

bool &Logger::operator[](LogInfo logInfo) { return _infos[static_cast<size_t>(logInfo)]; }

void Logger::setDefaultColors()
{
    setSeverityColor(Severity::Debug, Color::Blue);
    setSeverityColor(Severity::Information, Color::Green);
    setSeverityColor(Severity::Warning, Color::Yellow);
    setSeverityColor(Severity::Error, Color::Red);
}

void Logger::setSeverityColor(Severity severity, Color foreground, Color background)
{
    _colors[static_cast<size_t>(severity)] = {foreground, background};
}
