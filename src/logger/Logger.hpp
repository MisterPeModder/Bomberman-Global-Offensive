/*
** EPITECH PROJECT, 2022
** Indie Studio
** File description:
** Logger
*/

#ifndef RAYLIB_LOGGER_LOGGER_HPP_
#define RAYLIB_LOGGER_LOGGER_HPP_

#include <array>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <memory>
#include <string_view>

/// Basic logger class.
class Logger {
  public:
    /// Severity of a log or logLevel of a Logger.
    enum class Severity {
        Debug,       /// Debug messages
        Information, /// Random informations
        Warning,     /// Non critical error / Unexpected behavior
        Error,       /// (Critical) error
        Count,       /// Number of severities
    };

    /// Available display informations about the context.
    enum class LogInfo {
        PID,      /// Process PID
        ThreadId, /// Thread ID
        Date,     /// Current Date
        Time,     /// Current Time
        Count,    /// Number of available displays
    };

    /// Available colors in terminals (when using stdout/stderr).
    enum class Color {
        Black,   /// Black color, not used by default
        Red,     /// Red color, default to Error logs
        Green,   /// Green color, default to Information logs
        Yellow,  /// Yellow color, default to Warning logs
        Blue,    /// Blue color, default to Debug logs
        Magenta, /// Magenta color, not used by default
        Cyan,    /// Cyan color, not used by default
        White,   /// White color, default for all uncolored texts
    };

    /// Color pairs are used to associate foreground and background colors together
    using ColorPair = std::pair<Color, Color>;

    /// Default global logger.
    /// @note You need to flush it before forking processes to avoid cache data duplication.
    static Logger logger;

    /// Construct a new Logger object linked to a given output stream.
    ///
    /// @param[in] stream stream in which the logger will write.
    Logger(std::ostream &stream = std::cerr, std::string_view name = "");

    /// Construct a new Logger object linked to a logfile.
    ///
    /// @param[in] filepath path to the logfile.
    /// @param[in] clear Whether or not the logfile must be cleared.
    /// @throw std::runtime_error if the @ref std::ofstream cannot be created from the @c filepath.
    Logger(const std::filesystem::path &filepath, bool clear = false);

    /// Cannot copy loggers, because of the arbitrary output stream, which is not copiable.
    Logger(const Logger &other) = delete;

    /// Move constructor.
    Logger(Logger &&other) = default;

    /// Destroy the Logger object.
    ~Logger() = default;

    /// Cannot copy loggers, because of the arbitrary output stream, which is not copiable.
    Logger &operator=(const Logger &other) = delete;

    /// Add a message to the logs.
    /// @note The log will be taken in account only if the severity is greater or equal than the current logLevel.
    ///
    /// @param[in] severity severity of the log.
    /// @param[in] content message of the log.
    /// @param[in] line line of the
    void log(Severity severity, std::string_view content);

    /// Add a message to the logs using a writer function. It allows the use of the ostream operator overloads.
    /// @note The log will be taken in account only if the severity is greater or equal than the current logLevel.
    ///
    /// @param[in] severity severity of the log.
    /// @param[in] writer callback to write in the log.
    void log(Severity severity, std::function<void(std::ostream &)> writer);

    /// Flush the linked stream.
    void flush();

    /// Change the linked stream.
    ///
    /// @param[in] stream new output of the logger.
    void setStream(std::ostream &stream);

    /// Change the linked stream to be the input of @c filepath.
    ///
    /// @param[in] filepath filepath to the new logfile.
    /// @param[in] clear Whether or not the logfile must be cleared.
    void setOutputFile(const std::filesystem::path &filepath, bool clear = false);

    /// Set the Log Level.
    /// @note The log level define which logs must be printed in the stream.
    ///
    /// @param[in] logLevel minimum logLevel of the logs.
    void setLogLevel(Severity logLevel);

    /// Get the Log Level.
    ///
    /// @return Severity current logLevel.
    Severity getLogLevel() const;

    /// Access to a @ref LogInfo parameter.
    ///
    /// @param[in] logInfo parameter.
    /// @return true if the parameter is activated.
    /// @return false otherwise.
    bool operator[](LogInfo logInfo) const;

    /// Access to a @ref LogInfo parameter and allow to modify it.
    ///
    /// @param[in] logInfo parameter.
    /// @return reference to the current value of the parameter.
    bool &operator[](LogInfo logInfo);

    /// Remove all the @ref LogInfo set.
    void clearLogInfo();

    /// Enable/Disable a @ref LogInfo.
    ///
    /// @param enabled wheter or not the info must be enabled.
    /// @param info Info to modify.
    void enableLogInfo(bool enabled, LogInfo info);

    /// Enable/Disable multiple @ref LogInfo.
    ///
    /// @tparam Args multiple @ref LogInfo.
    /// @param enabled wheter or not the infos must be enabled.
    /// @param info First info to modify.
    /// @param args Next infos to modify.
    template <class... Args> void enableLogInfo(bool enabled, LogInfo info, Args... args)
    {
        (*this)[info] = enabled;
        enableLogInfo(enabled, args...);
    }

    /// Set the @b exclusive @ref LogInfo enabled (all infos not specified will be disabled).
    ///
    /// @tparam Args multiple @ref LogInfo.
    /// @param info First info to modify.
    /// @param args Next infos to modify.
    template <class... Args> void setLogInfo(LogInfo info, Args... args)
    {
        clearLogInfo();
        enableLogInfo(true, info, args...);
    }

    /// Reset the default colors.
    /// @note Colors are only used when the logger prints on stdout/stderr.
    void setDefaultColors();

    /// Set the color of a severity.
    /// @note Multiple severities can have the same color but it isn't recommended for readability.
    ///
    /// @param severity severity to affect.
    /// @param foreground foreground color.
    /// @param background background color.
    void setSeverityColor(Severity severity, Color foreground, Color background = Color::Black);

    /// Set the Name of the logger.
    /// @note If empty the name isn't printed.
    ///
    /// @param name name of the logger.
    void setName(std::string_view name);

    /// Get the name of the logger.
    /// @return std::string_view name of the logger, might be empty.
    std::string_view getName() const;

  private:
    void displayInformations(std::stringstream &ss);
    void displayTime(std::stringstream &ss, std::string_view format);

    std::array<bool, static_cast<size_t>(LogInfo::Count)> _infos;
    Severity _logLevel = Severity::Information;
    std::ostream *_streamPointer;
    std::ofstream _fileStream;
    std::array<ColorPair, static_cast<size_t>(Severity::Count)> _colors;
    std::string _name;
};

#endif /* !RAYLIB_LOGGER_LOGGER_HPP_ */
