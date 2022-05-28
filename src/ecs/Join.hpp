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

#include "ecs/storage/Storage.hpp"
#include "util/BitSet.hpp"

#include <concepts>
#include <cstdint>
#include <functional>
#include <iterator>
#include <tuple>
#include <type_traits>

/// Entity-Component-System namespace.
namespace ecs
{
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Joinable Types
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma region ECS Joinable Types

    /// @internal
    /// Used to access properties of @ref Joinable types.
    template <typename Storage> struct JoinTraits {
        using Data = typename Storage::Component &;

        static util::BitSet const &getMask(Storage const &storage) { return storage.getMask(); }

        static Data getData(Storage &storage, std::size_t index) { return storage[index]; }
    };

    /// Implemented by types that can be joined.
    template <typename J>
    concept Joinable = requires(J &joinable, J const &cjoinable, std::size_t index)
    {
        typename JoinTraits<J>::Data;

        // clang-format off
        { JoinTraits<J>::getMask(cjoinable) } -> std::same_as<util::BitSet const &>;
        { JoinTraits<J>::getData(joinable, index) } -> std::same_as<typename JoinTraits<J>::Data>;
        // clang-format on
    };

    /// A @ref Joinable structure that yields all indices, returning @b nullptr for all missing elements and pointers
    /// to the elements otherwise.
    ///
    /// For usage, see @ref maybe().
    ///
    /// @note Do not have a join of only MaybeJoins. Otherwise the join will iterate over every single index of the
    /// bitset. If you want a join with all MaybeJoins, add an @ref Entities resource to the join as well to bound the
    /// join to all entities that are alive.
    template <typename J> class MaybeJoin {
      public:
        MaybeJoin(J &inner) : _inner(inner), _nonMask(JoinTraits<J>::getMask(inner).size()) { this->_nonMask.setAll(); }

        constexpr J &getInner() noexcept { return this->_inner; }

        constexpr util::BitSet const &getMask() const noexcept { return this->_nonMask; }

      private:
        J &_inner;
        /// all ones!
        util::BitSet _nonMask;
    };

    /// @internal
    /// Used to access properties of optional @ref Joinable types.
    template <Joinable J> struct JoinTraits<MaybeJoin<J>> {
        using Data = std::add_pointer_t<typename JoinTraits<J>::Data>;

        constexpr static util::BitSet const &getMask(MaybeJoin<J> const &joinable) { return joinable.getMask(); }

        constexpr static Data getData(MaybeJoin<J> &joinable, std::size_t index)
        {
            if (JoinTraits<J>::getMask(joinable.getInner())[index])
                return &JoinTraits<J>::getData(joinable.getInner(), index);
            return nullptr;
        }
    };

#pragma endregion ECS Joinable Types
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Iterator Support
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma region ECS Join Iterator Support

    /// The iterator type used by @ref Join.
    ///
    /// This type satisfies @ref std::forward_iterator.
    template <Joinable First, Joinable... Rest> class JoinIter {
      public:
        using value_type = std::tuple<typename JoinTraits<First>::Data, typename JoinTraits<Rest>::Data...>;
        using difference_type = std::ptrdiff_t;
        using reference = value_type &;
        using iterator_category = std::input_iterator_tag;

        /// Default (uninitialized) contructor
        explicit JoinIter() {}

        explicit JoinIter(util::BitSet const &mask, std::tuple<First &, Rest &...> const &storages, std::size_t pos)
            : _mask(std::cref(mask)), _storages(std::cref(storages)), _pos(pos)
        {
        }

        JoinIter(JoinIter<First, Rest...> const &) = default;
        JoinIter<First, Rest...> &operator=(JoinIter<First, Rest...> const &) = default;

        JoinIter(JoinIter<First, Rest...> &&) = default;
        JoinIter<First, Rest...> &operator=(JoinIter<First, Rest...> &&other) = default;

        /// @note It is Undefined Behavior to compare two iterators that do not belong to the same container.
        ///
        /// @returns Whether the two iterators are equal.
        constexpr bool operator==(JoinIter<First, Rest...> const &other) const { return this->_pos == other._pos; }

        /// @note It is Undefined Behavior to compare two iterators that do not belong to the same container.
        ///
        /// @returns Whether the two iterators are not equal.
        constexpr bool operator!=(JoinIter<First, Rest...> const &other) const { return this->_pos != other._pos; }

        /// @returns The components and/or resources corresponding the entity at the current position.
        value_type operator*() const { return this->get_components(std::make_index_sequence<(sizeof...(Rest)) + 1>()); }

        /// @returns The components and/or resources corresponding the entity at the current position.
        value_type operator->() const { return *this; }

        /// Increments the iterator.
        ///
        /// @note It is Undefined Behavior to increment the iterator past the end sentinel.
        ///
        /// @returns A reference to this iterator.
        JoinIter<First, Rest...> &operator++()
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
        JoinIter<First, Rest...> operator++(int)
        {
            JoinIter<First, Rest...> result = *this;

            ++result->_pos;
            return result;
        }

      private:
        std::reference_wrapper<const util::BitSet> _mask;
        std::reference_wrapper<const std::tuple<First &, Rest &...>> _storages;
        std::size_t _pos;

        /// Black magic™ that allows one to get the components in the storages.
        template <size_t... Indices> value_type get_components(std::index_sequence<Indices...>) const
        {
            // If someone understands this, kudos. Because I sure don't.
            return {JoinTraits<std::remove_reference_t<decltype(std::get<Indices>(this->_storages.get()))>>::getData(
                std::get<Indices>(this->_storages.get()), this->_pos)...};
        }
    };

    /// Container of joined values.
    ///
    /// Created via the @ref join() utility function.
    template <Joinable First, Joinable... Rest> class Join {
      public:
        /// Joins values.
        ///
        /// @note Consider using @ref join() instead, it doesn't require callers to specify the template parameters.
        explicit Join(First &first, Rest &...rest)
            : _mask((util::BitSet(JoinTraits<First>::getMask(first)) &= ... &= JoinTraits<Rest>::getMask(rest))),
              _storages(first, rest...)
        {
            // push a sentinel bit at the end.
            this->_mask.push(true);
            this->_begin = this->_mask.firstSet();
        }

        /// @returns A @ref std::forward_iterator to the first available entity, or a value that is equal to @ref end()
        /// if not found.
        JoinIter<First, Rest...> begin() const noexcept { return JoinIter(this->_mask, this->_storages, this->_begin); }

        /// @returns An iterator sentinel value, do not deference it.
        JoinIter<First, Rest...> end() const noexcept
        {
            return JoinIter(this->_mask, this->_storages, this->_mask.size() - 1);
        }

      private:
        util::BitSet _mask;
        std::tuple<First &, Rest &...> _storages;
        /// The position of the first set bit
        std::size_t _begin;
    };

#pragma endregion ECS Join Iterator Support
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Main join utility functions
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /// Combines multiple Joinable values into a single iterable container.
    ///
    /// @param first The fist joinable value.
    /// @param rest The other joinable values, optional.
    ///
    /// @return The joined values.
    template <Joinable First, Joinable... Rest> Join<First, Rest...> join(First &first, Rest &...rest)
    {
        return Join<First, Rest...>(first, rest...);
    }

    /// Creates A @ref Joinable structure that yields all indices, returning @b nullptr for all missing elements and
    /// pointers to the elements otherwise.
    ///
    /// @note Do not have a join of only MaybeJoins. Otherwise the join will iterate over every single index of the
    /// bitset. If you want a join with all MaybeJoins, add an @ref Entities resource to the join as well to bound the
    /// join to all entities that are alive.
    ///
    /// @tparam J A @ref Joinable type, such as @ref MapStorage, @ref Entities, and more.
    ///
    /// @param joinable A joinable value.
    ///
    /// @returns An optional version of @b joinable.
    template <Joinable J> MaybeJoin<J> maybe(J &joinable) { return MaybeJoin<J>(joinable); }
} // namespace ecs

#endif // !defined(ECS_JOIN_HPP_)
