/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** util
*/

#include "util.hpp"
#include "raylib/text/text.hpp"

#include <fstream>
#include <sstream>
#include <string>

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

    void pushUtf8Codepoint(std::string &str, int codepoint) noexcept
    {
        str.append(raylib::text::codepointToUtf8(codepoint));
    }

    int popUtf8Codepoint(std::string &str) noexcept
    {
        int bytes;
        int codepoint;
        char const *buf = str.c_str() + str.size();

        if (str.size() > 0 && static_cast<unsigned char>(*(buf - 1)) < 128U) {
            codepoint = static_cast<int>(*(buf - 1));
            str.pop_back();
            return codepoint;
        } else if (str.size() > 1 && (codepoint = GetCodepoint(buf - 2, &bytes)) != '?') {
            str.erase(str.end() - 2, str.end());
            return codepoint;
        } else if (str.size() > 2 && (codepoint = GetCodepoint(buf - 3, &bytes)) != '?') {
            str.erase(str.end() - 3, str.end());
            return codepoint;
        } else if (str.size() > 3 && (codepoint = GetCodepoint(buf - 4, &bytes)) != '?') {
            str.erase(str.end() - 4, str.end());
            return codepoint;
        }
        return 0;
    }
} // namespace util
