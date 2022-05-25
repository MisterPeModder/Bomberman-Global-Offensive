/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Rule
*/

#ifndef BOMBERMAN_MAP_CELLULAR_RULE_HPP_
#define BOMBERMAN_MAP_CELLULAR_RULE_HPP_

#include <array>
#include <string_view>

namespace bomberman
{
    namespace map
    {
        namespace cellular
        {
            class Rule {
              public:
                Rule(std::string_view rule = "");
                ~Rule() = default;

                bool nextState(unsigned char neighbours, bool state) const;

                std::string_view getRule() const;
                void setRule(std::string_view rule);

              private:
                void parseRule(std::string_view rule);
                size_t parseBirth(std::string_view birthRule);
                size_t parseSurvive(std::string_view surviveRule);

                std::array<bool, 9> _birth;
                std::array<bool, 9> _survive;
                std::string _rule;
            };
        } // namespace cellular
    }     // namespace map
} // namespace bomberman

#endif /* !BOMBERMAN_MAP_CELLULAR_RULE_HPP_ */
