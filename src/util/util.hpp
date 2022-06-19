/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Utils
*/

#ifndef BOMBERMAN_UTILS_HPP_
#define BOMBERMAN_UTILS_HPP_

#include <filesystem>
#include <functional>
#include <string>
#include <utility>
#include <string_view>

namespace util
{
    /// Concatenate multiple directories in a single path.
    /// @note This function is the end point of the templated @ref makePath() function.
    ///
    /// @param[in] path end path.
    /// @return std::filesystem::path The path send in input.
    inline std::filesystem::path makePath(std::filesystem::path path) { return path; }

    /// Concatenate multiple directories in a single path.
    ///
    /// @tparam Args directories to concatenate
    /// @param[in] path starting path
    /// @param[in] nextDir next directory
    /// @param[in] args next directories (optional)
    /// @return std::filesystem::path concatenated path of all the directories
    template <class... Args>
    std::filesystem::path makePath(std::filesystem::path path, std::string_view nextDir, Args... args)
    {
        return makePath(path.append(nextDir), args...);
    }

    /// Load a configuration file with a form of [key]=[value] for each line.
    /// @note Empty lines and lines starting with a '#' are skipped.
    ///
    /// @param path filepath.
    /// @param handleValue function called with each key value pair. If it returns false, the function doesn't read the
    /// next lines and close the file.
    /// @return true If the file was entirely loaded.
    /// @return false If the file couldn't be opened or if the @c handleValue function returned false for an element.
    bool loadConfigFile(
        const std::filesystem::path &path, const std::function<bool(std::string_view, std::string_view)> &handleValue);

    /// @returns The index of the closest UTF-8 char boundary, starting from right to left.
    std::size_t utf8BoundaryStart(std::string_view str, std::size_t index) noexcept;

    /// @returns The index of the closest UTF-8 char boundary, starting from left to right.
    std::size_t utf8BoundaryEnd(std::string_view str, std::size_t index) noexcept;

    /// Inserts an UTF-8 codepoint in @b str.
    ///
    /// @note This function is not safe to call over multiple threads.
    ///
    /// @param str The string to modify.
    /// @param codepoint An Unicode codepoint.
    /// @param index Where to insert the codepoint, defaults to the end of the string.
    ///
    /// @returns The number of bytes added to str.
    std::size_t insertUtf8Codepoint(std::string &str, int codepoint, std::size_t index = std::string::npos) noexcept;

    /// Removes an UTF-8 codepoint from @b str.
    ///
    /// @note This function is not safe to call over multiple threads.
    ///
    /// @param str The string to modify.
    /// @param index The byte offset of the character, defaults to the end of the string.
    ///
    /// @return The removed codepoint, or 0 if @b str was empty or not valid UTF-8.
    std::pair<int, std::size_t> removeUtf8Codepoint(std::string &str, std::size_t index = std::string::npos) noexcept;
} // namespace util

#endif /* !BOMBERMAN_UTILS_HPP_ */
