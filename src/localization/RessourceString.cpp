/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** RessourceString
*/

#include "RessourceString.hpp"
#include "Localization.hpp"

namespace localization
{
    RessourceString::operator std::string_view() const { return Localization::translate(_msgid); }

    RessourceString::operator std::string() const { return std::string(*this); }
} // namespace localization

std::ostream &operator<<(std::ostream &stream, const localization::RessourceString &rs)
{
    return stream << localization::Localization::translate(rs.getMsgId());
}
