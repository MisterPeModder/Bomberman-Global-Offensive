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

    std::size_t utf8BoundaryStart(std::string_view str, std::size_t index) noexcept
    {
        if (str.empty())
            return 0;
        if (index >= str.size())
            return str.size();
        while (index > 0 && (static_cast<unsigned char>(str[index]) & 0b11000000) == 0b10000000)
            --index;
        return index;
    }

    std::size_t utf8BoundaryEnd(std::string_view str, std::size_t index) noexcept
    {
        if (str.empty())
            return 0;
        while (index < str.size() && (static_cast<unsigned char>(str[index]) & 0b11000000) == 0b10000000)
            ++index;
        return index;
    }

    std::size_t insertUtf8Codepoint(std::string &str, int codepoint, std::size_t index) noexcept
    {
        size_t pos = index == std::string::npos ? str.size() : index;
        std::string_view encoded = raylib::text::codepointToUtf8(codepoint);

        str.insert(pos, encoded);
        return encoded.size();
    }

    std::pair<int, std::size_t> removeUtf8Codepoint(std::string &str, std::size_t index) noexcept
    {
        if (str.empty())
            return {0, 0};

        index = utf8BoundaryStart(str, index);
        auto start = str.cbegin() + index;

        // ASCII char
        if (static_cast<unsigned char>(*start) < 128U) {
            int codepoint = static_cast<int>(*start);
            str.erase(start, start + 1);
            return {codepoint, 1};
        }

        // Multi-byte UTF-8 sequence
        auto [codepoint, size] = raylib::text::utf8ToCodepoint({start, str.cend()});

        str.erase(start, start + size);
        return {codepoint, size};
    }
} // namespace util
