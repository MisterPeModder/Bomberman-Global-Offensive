/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Rule
*/

#include "Rule.hpp"
#include <ctype.h>
#include <regex>

namespace bomberman
{
    namespace map
    {
        namespace cellular
        {
            Rule::InvalidRule::InvalidRule(std::string_view what) : std::runtime_error(what.data()) {}

            Rule::Rule(std::string_view rule) { parseRule(rule); }

            bool Rule::nextState(unsigned char neighbours, bool state) const
            {
                if (neighbours > 8)
                    throw std::logic_error("A cell cannot have more than 8 neighbours.");
                if (!state)
                    return _birth[neighbours];
                else
                    return _survive[neighbours];
            }

            std::string_view Rule::getRule() const { return _rule; }

            void Rule::setRule(std::string_view rule) { parseRule(rule); }

            void Rule::parseRule(std::string_view rule)
            {
                _rule = rule;
                _birth.fill(false);
                _survive.fill(false);
                if (rule.empty())
                    return;

                size_t i = parseBirth(rule);
                if (i == rule.size() - 1)
                    return;
                if (i < rule.size() && rule[i++] != '/')
                    throw InvalidRule("Missing separator between birth and survive rule parts.");
                i += parseSurvive(rule.data() + i);
                if (i < rule.size())
                    throw InvalidRule("Invalid rule.");
            }

            size_t Rule::parseBirth(std::string_view birthRule)
            {
                std::regex re("B[0-9]+.*");

                if (!std::regex_match(birthRule.data(), re)) {
                    if (!birthRule.empty() && birthRule[0] == 'B')
                        throw InvalidRule("Rule with empty birth.");
                    return 0;
                }
                size_t i = 1;
                while (i < birthRule.size() && isdigit(birthRule[i]))
                    _birth[birthRule[i++] - '0'] = true;
                return i;
            }

            size_t Rule::parseSurvive(std::string_view surviveRule)
            {
                std::regex re("S[0-9]+.*");

                if (!std::regex_match(surviveRule.data(), re)) {
                    if (!surviveRule.empty() && surviveRule[0] == 'S')
                        throw InvalidRule("Rule with empty survive.");
                    return 0;
                }
                size_t i = 1;
                while (i < surviveRule.size() && isdigit(surviveRule[i]))
                    _survive[surviveRule[i++] - '0'] = true;
                return i;
            }
        } // namespace cellular
    }     // namespace map
} // namespace bomberman
