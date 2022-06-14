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
#include <random>
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

    /// Generate a random number in the interval [min, max]
    ///
    /// @tparam numeral type of the numbers.
    /// @param min minimum value.
    /// @param max maximum value.
    /// @return numeral value in the interval [min, max]
    template <typename numeral> numeral randInt(numeral min, numeral max)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<std::mt19937::result_type> dist(min, max);

        return dist(gen);
    }

} // namespace util

#endif /* !BOMBERMAN_UTILS_HPP_ */
