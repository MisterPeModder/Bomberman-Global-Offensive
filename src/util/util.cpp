/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** util
*/

#include "util.hpp"
#include <fstream>
#include <sstream>

namespace util
{
    bool loadConfigFile(
        const std::filesystem::path &path, const std::function<bool(std::string_view, std::string_view)> &handleValue)
    {
        std::ifstream file(path);
        std::string line;
        std::stringstream ss;
        std::string key;
        std::string value;
        bool res = true;

        if (!file.is_open())
            return false;
        while (std::getline(file, line)) {
            if (line.empty() || line[0] == '#')
                continue;
            ss.str(line);
            std::getline(ss, key, '=');
            value = ss.str().substr(ss.tellg());
            if (!handleValue(key, value)) {
                res = false;
                break;
            }
        }
        file.close();
        return res;
    }
} // namespace util