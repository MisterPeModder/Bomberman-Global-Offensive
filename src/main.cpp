#include <iostream>
#include "localization/Localization.hpp"
#include "logger/Logger.hpp"

int main()
{
    /// Setup the logger parameters
    Logger::logger.setOutputFile("log.txt");
    Logger::logger.setLogLevel(Logger::Severity::Information);
    Logger::logger.setLogInfo(Logger::LogInfo::Time);

    localization::Localization::loadLocales({"en", "fr"});
    localization::Localization::setLocale("fr");

    Logger::logger.log(Logger::Severity::Information, "Start of program");
    std::cout << _("Hello, World!") << std::endl;
    Logger::logger.log(Logger::Severity::Information, "End of program");
}
