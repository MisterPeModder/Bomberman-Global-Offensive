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
            /// Cellular automata rule, representing of form B[0-9]+/S[0-9]+
            /// Where B stands for Birth, S for survive and the numbers are the neighbours number
            /// See https://en.wikipedia.org/wiki/Life-like_cellular_automaton
            class Rule {
              public:
                /// Create a new Rule from its notation.
                /// Empty rule will result in rule with no birth neither survive (all cells die in a single iteration)
                Rule(std::string_view rule = "");

                /// Destroy the rule.
                ~Rule() = default;

                /// Get the next state of a cell based on its current state and the number of filled neighbours.
                ///
                /// @param neighbours number of filled neighbours (the 8 adjacent blocks)
                /// @param state current state, true for filled.
                /// @return Next state of the cell following the loaded rule.
                bool nextState(unsigned char neighbours, bool state) const;

                /// Get the Rule notation
                ///
                /// @return std::string_view rule notation
                std::string_view getRule() const;

                /// Set the Rule from its notation
                ///
                /// @param rule rule notation
                void setRule(std::string_view rule);

              private:
                /// Parse a rule.
                ///
                /// @param rule rule to parse.
                void parseRule(std::string_view rule);

                /// Parse a birth rule
                ///
                /// @param birthRule rule matching the regex "B[0-9]+"
                /// @return std::size_t end id of the birth rule part
                size_t parseBirth(std::string_view birthRule);

                /// Parse a survive rule
                ///
                /// @param surviveRule rule matching the regex S[0-9]+
                /// @return size_t end id of the survive rule part
                ///
                size_t parseSurvive(std::string_view surviveRule);

                std::array<bool, 9> _birth;
                std::array<bool, 9> _survive;
                std::string _rule;
            };
        } // namespace cellular
    }     // namespace map
} // namespace bomberman

#endif /* !BOMBERMAN_MAP_CELLULAR_RULE_HPP_ */
