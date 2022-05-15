#include <iostream>
#include "localization/Localization.hpp"
#include "logger/Logger.hpp"

int main()
{
    /// Setup the logger parameters
    Logger::logger.setOutputFile("log.txt");
    Logger::logger.setLogLevel(Logger::Severity::Information);
    Logger::logger.setLogInfo(Logger::LogInfo::Time);

    /// Setup the locales parameters
    localization::Localization::loadLocales({"en", "fr"});
    localization::Localization::setLocale("fr");
    localization::Localization::registerString("New string!");

    Logger::logger.log(Logger::Severity::Information, "Start of program");
    std::cout << _("Hello, World!") << std::endl;
    localization::Localization::saveLocales();
    Logger::logger.log(Logger::Severity::Information, "End of program");
}
