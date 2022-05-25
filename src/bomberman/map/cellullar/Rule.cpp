/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Rule
*/

#include "Rule.hpp"
#include <ctype.h>
#include <stdexcept>

namespace bomberman
{
    namespace map
    {
        namespace cellular
        {
            Rule::Rule(std::string_view rule) : _rule(rule) { parseRule(rule); }

            bool Rule::nextState(unsigned char neighbours, bool state)
            {
                if (neighbours > 8)
                    throw std::logic_error("A cell cannot have more than 8 neighbours."); //// Replace later
                if (!state)
                    return _birth[neighbours];
                if (state)
                    return _survive[neighbours];
            }

            void Rule::parseRule(std::string_view rule)
            {
                size_t i = 0;

                if (rule.empty() || rule[0] != 'B')
                    throw std::logic_error("Invalid rule.");
                _birth.fill(false);
                _survive.fill(false);
                ++i;
                while (i < rule.size() && isdigit(rule[i]))
                    _birth[rule[i++] - '0'] = true;
                if (i >= rule.size() || rule[i] != '/' || rule[++i] != 'S')
                    throw std::logic_error("Invalid rule.");
                ++i;
                while (i < rule.size() && isdigit(rule[i]))
                    _survive[rule[i++] - '0'] = true;
                if (i >= rule.size())
                    throw std::logic_error("Invalid rule.");
            }
        } // namespace cellular
    }     // namespace map
} // namespace bomberman
