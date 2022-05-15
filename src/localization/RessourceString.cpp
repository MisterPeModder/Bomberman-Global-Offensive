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
    RessourceString::RessourceString(std::string_view msgid) : _msgid(msgid) {}

    std::string_view RessourceString::getMsgId() const { return _msgid; }

    RessourceString::operator std::string_view() const { return Localization::translate(_msgid, true); }

    RessourceString::operator std::string() const { return std::string(*this); }
} // namespace localization

std::ostream &operator<<(std::ostream &stream, const localization::RessourceString &rs)
{
    return stream << static_cast<std::string_view>(rs);
}
