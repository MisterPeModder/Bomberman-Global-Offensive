/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** ECS - Component & Resource iteration
*/

#ifndef ECS_JOIN_HPP_
#define ECS_JOIN_HPP_

/// @file
///
/// Provides the @ref join() function that allows one to iterate over multiple components and resources at once.
///
/// Powered by black magic™

#include "util/BitSet.hpp"

#include <cstdint>
#include <functional>
#include <iterator>
#include <tuple>

/// Entity-Component-System namespace.
namespace ecs
{
    /// The iterator type used by @ref Join.
    ///
    /// This type satisfies @ref std::forward_iterator.
    template <typename Storage, typename... Storages> class JoinIter {
      public:
        using value_type = std::tuple<typename Storage::Component &, typename Storages::Component &...>;
        using difference_type = std::ptrdiff_t;
        using reference = value_type &;
        using iterator_category = std::input_iterator_tag;

        explicit JoinIter() {}

        explicit JoinIter(
            util::BitSet const &mask, std::tuple<Storage &, Storages &...> const &storages, std::size_t pos)
            : _mask(std::cref(mask)), _storages(std::cref(storages)), _pos(pos)
        {
        }

        JoinIter(JoinIter<Storage, Storages...> const &) = default;
        JoinIter<Storage, Storages...> &operator=(JoinIter<Storage, Storages...> const &) = default;

        JoinIter(JoinIter<Storage, Storages...> &&) = default;
        JoinIter<Storage, Storages...> &operator=(JoinIter<Storage, Storages...> &&other) = default;

        /// @note It is Undefined Behavior to compare two iterators that do not belong to the same container.
        ///
        /// @returns Whether the two iterators are equal.
        constexpr bool operator==(JoinIter<Storage, Storages...> const &other) const
        {
            return this->_pos == other._pos;
        }

        /// @note It is Undefined Behavior to compare two iterators that do not belong to the same container.
        ///
        /// @returns Whether the two iterators are not equal.
        constexpr bool operator!=(JoinIter<Storage, Storages...> const &other) const
        {
            return this->_pos != other._pos;
        }

        /// @returns The components and/or resources corresponding the entity at the current position.
        value_type operator*() const
        {
            return this->get_components(std::make_index_sequence<(sizeof...(Storages)) + 1>());
        }

        /// @returns The components and/or resources corresponding the entity at the current position.
        value_type operator->() const { return *this; }

        /// Increments the iterator.
        ///
        /// @note It is Undefined Behavior to increment the iterator past the end sentinel.
        ///
        /// @returns A reference to this iterator.
        JoinIter<Storage, Storages...> &operator++()
        {
            this->_pos = this->_mask.get().firstSet(this->_pos + 1);
            return *this;
        }

        /// Copies the iterator and increments the copy, please use pre-incrementation instead.
        ///
        /// @note It is Undefined Behavior to increment the iterator past the end sentinel.
        /// @note This creates a copy of the iterator!
        ///
        /// @returns The incremented copy.
        JoinIter<Storage, Storages...> operator++(int)
        {
            JoinIter<Storage, Storages...> result = *this;

            ++result->_pos;
            return result;
        }

      private:
        std::reference_wrapper<const util::BitSet> _mask;
        std::reference_wrapper<const std::tuple<Storage &, Storages &...>> _storages;
        std::size_t _pos;

        /// Black magic™ that allows one to get the components in the storages.
        template <size_t... Indices> value_type get_components(std::index_sequence<Indices...>) const
        {
            return {std::get<Indices>(this->_storages.get())[this->_pos]...};
        }
    };

    /// Container of joined values.
    ///
    /// Created via the @ref join() utility function.
    template <typename Storage, typename... Storages> class Join {
      public:
        /// Joins values.
        ///
        /// @note Consider using @ref join() instead, it doesn't require callers to specify the template parameters.
        explicit Join(Storage &first, Storages &...rest)
            : _mask((util::BitSet(first.getMask()) &= ... &= rest.getMask())), _storages(first, rest...)
        {
            // push a sentinel bit at the end.
            this->_mask.push(true);
            this->_begin = this->_mask.firstSet();
        }

        /// @returns A @ref std::forward_iterator to the first available entity, or a value that is equal to @ref end()
        /// if not found.
        JoinIter<Storage, Storages...> begin() const noexcept
        {
            return JoinIter(this->_mask, this->_storages, this->_begin);
        }

        /// @returns An iterator sentinel value, do not deference it.
        JoinIter<Storage, Storages...> end() const noexcept
        {
            return JoinIter(this->_mask, this->_storages, this->_mask.size() - 1);
        }

      private:
        util::BitSet _mask;
        std::tuple<Storage &, Storages &...> _storages;
        /// The position of the first set bit
        std::size_t _begin;
    };

    /// Combines multiple Joinable values into a single iterable container.
    ///
    /// @param first The fist joinable value.
    /// @param rest The other joinable values, optional.
    ///
    /// @return The joined values.
    template <typename First, typename... Rest> Join<First, Rest...> join(First &first, Rest &...rest)
    {
        return Join<First, Rest...>(first, rest...);
    }
} // namespace ecs

#endif // !defined(ECS_JOIN_HPP_)
