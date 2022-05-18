/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** RessourceString
*/

#ifndef LOCALIZATION_RESSOURCESTRING_HPP_
#define LOCALIZATION_RESSOURCESTRING_HPP_

#include <ostream>
#include <string_view>

namespace localization
{
    /// Translatable string. Will register itself in the loaded locales.
    class RessourceString {
      public:
        /// Construct a new Ressource String object.
        ///
        /// @param msgid id of the message, also the message used when no translation is set.
        constexpr RessourceString(std::string_view msgid) : _msgid(msgid) {}

        /// Destroy the Ressource String object.
        ~RessourceString() = default;

        /// Get the Msg Id wrapped.
        ///
        /// @return std::string_view msgid.
        constexpr std::string_view getMsgId() const { return _msgid; }

        /// Convert the string to its translated version.
        ///
        /// @return std::string_view translated string.
        operator std::string_view() const;

        /// Convert the string to its translated version.
        ///
        /// @return std::string translated string.
        operator std::string() const;

      private:
        std::string_view _msgid;
    };
} // namespace localization

/// Overload of output stream operator to allow writing translated string to streams.
///
/// @param stream output stream.
/// @param rs ressource string.
/// @return std::ostream& output stream.
///
std::ostream &operator<<(std::ostream &stream, const localization::RessourceString &rs);

#endif /* !LOCALIZATION_RESSOURCESTRING_HPP_ */
