/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** RessourceFile
*/

#ifndef LOCALIZATION_RESSOURCEFILE_HPP_
#define LOCALIZATION_RESSOURCEFILE_HPP_

#include <map>
#include "RessourceString.hpp"

namespace localization
{
    class RessourceFile {
      public:
        RessourceFile() = default;
        ~RessourceFile() = default;

      private:
        std::string _locale;
        std::map<std::string, RessourceString> _ressources;
    };
} // namespace localization

#endif /* !LOCALIZATION_RESSOURCEFILE_HPP_ */
