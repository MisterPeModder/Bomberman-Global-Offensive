#include <iostream>
#include "logger/Logger.hpp"

int main()
{
    /// Setup the logger parameters
    Logger::logger.setOutputFile("log.txt");
    Logger::logger.setLogLevel(Logger::Severity::Information);
    Logger::logger.setLogInfo(Logger::LogInfo::Time);

    Logger::logger.log(Logger::Severity::Information, "Start of program");
    std::cout << "Hello, World!" << std::endl;
    Logger::logger.log(Logger::Severity::Information, "End of program");
}
