/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** ResourceString
*/

#include "ResourceString.hpp"
#include "Localization.hpp"

namespace localization
{
    ResourceString::operator std::string_view() const { return Localization::translate(_msgid); }

    ResourceString::operator std::string() const { return std::string(*this); }
} // namespace localization

std::ostream &operator<<(std::ostream &stream, const localization::ResourceString &rs)
{
    return stream << localization::Localization::translate(rs.getMsgId());
}
