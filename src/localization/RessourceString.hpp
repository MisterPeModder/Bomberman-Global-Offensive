/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** RessourceString
*/

#ifndef LOCALIZATION_RESSOURCESTRING_HPP_
#define LOCALIZATION_RESSOURCESTRING_HPP_

#include <string>

namespace localization
{
    class RessourceString {
      public:
        RessourceString();
        ~RessourceString();

      private:
        std::string _id;
        std::string _translated;
    };
} // namespace localization

#endif /* !LOCALIZATION_RESSOURCESTRING_HPP_ */
