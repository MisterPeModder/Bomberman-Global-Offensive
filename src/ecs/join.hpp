/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** ECS
*/

#ifndef ECS_JOIN_HPP_
#define ECS_JOIN_HPP_

#include <iostream>
#include "util/BitSet.hpp"

#include <cstdint>
#include <iterator>
#include <tuple>

namespace ecs
{
    template <typename Storage, typename... Storages> class JoinIter {
      public:
        using value_type = std::tuple<typename Storage::Component &, typename Storages::Component &...>;
        using difference_type = std::ptrdiff_t;
        using reference = value_type &;
        using iterator_category = std::input_iterator_tag;

        explicit JoinIter(
            util::BitSet const &mask, std::tuple<Storage &, Storages &...> const &storages, std::size_t pos)
            : _mask(mask), _storages(storages), _pos(pos)
        {
        }

        JoinIter(JoinIter<Storage, Storages...> const &) = default;
        JoinIter<Storage, Storages...> &operator=(JoinIter<Storage, Storages...> const &) = default;

        constexpr bool operator==(JoinIter<Storage, Storages...> const &other) const
        {
            return this->_pos == other._pos;
        }

        constexpr bool operator!=(JoinIter<Storage, Storages...> const &other) const
        {
            return this->_pos != other._pos;
        }

        value_type operator*() const
        {
            return this->get_components(std::make_index_sequence<(sizeof...(Storages)) + 1>());
        }

      private:
        util::BitSet const &_mask;
        std::tuple<Storage &, Storages &...> const &_storages;
        std::size_t _pos;

        template <size_t... Indices> value_type get_components(std::index_sequence<Indices...>) const
        {
            ecs::Entity entity(this->_pos, 0);
            return {std::get<Indices>(this->_storages)[entity]...};
        }
    };

    template <typename Storage, typename... Storages> class Join {
      public:
        explicit Join(Storage &first, Storages &...rest)
            : _mask((util::BitSet(first.getMask()) &= ... &= rest.getMask())), _storages(first, rest...)
        {
            for (size_t i = 0; i < this->_mask.size(); ++i) {
                std::cout << "entity #" << i << ": " << (this->_mask[i] ? "present" : "absent") << "\n";
            }
            std::cout.flush();
        }

        JoinIter<Storage, Storages...> begin() noexcept { JoinIter(this->_mask, this->_storages, 0); }
        JoinIter<Storage, Storages...> end() noexcept { JoinIter(this->_mask, this->_storages, this->_mask.size()); }

      private:
        util::BitSet _mask;
        std::tuple<Storage &, Storages &...> _storages;
    };

    template <typename First, typename... Rest> void join(First &first, Rest &...rest)
    {
        Join<First, Rest...>(first, rest...);
    }
} // namespace ecs

#endif // !defined(ECS_JOIN_HPP_)
