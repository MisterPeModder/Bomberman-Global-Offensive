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
        auto start = str.cend() - 1;

        // ASCII char
        if (str.size() > 0 && static_cast<unsigned char>(*start) < 128U) {
            int codepoint = static_cast<int>(*start);
            str.erase(start, start + 1);
            return codepoint;
        }
        // Multi-byte UTF-8 sequence
        for (std::size_t i = 1; i < 4; ++i) {
            if (str.size() <= i)
                break;
            start = str.cend() - i - 1;
            auto [codepoint, size] = raylib::text::utf8ToCodepoint({start, str.cend()});

            if (codepoint != '?') {
                str.erase(start, start + size);
                return codepoint;
            }
        }
        return 0;
    }
} // namespace util
