/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** ECS - Component & Resource iteration
*/

/// @file
/// @internal
///
/// Optional Joinable Type.

#ifndef ECS_JOIN_MAYBE_JOIN_HPP_
#define ECS_JOIN_MAYBE_JOIN_HPP_

#include "ecs/join/Joinable.hpp"
#include "util/BitSet.hpp"

#include <type_traits>

/// Entity-Component-System namespace.
namespace ecs
{
    /// A @ref Joinable structure that yields all indices, returning @b nullptr for all missing elements and pointers
    /// to the elements otherwise.
    ///
    /// For usage, see @ref maybe().
    ///
    /// @note Do not have a join of only MaybeJoins. Otherwise the join will iterate over every single index of the
    /// bitset. If you want a join with all MaybeJoins, add an @ref Entities resource to the join as well to bound the
    /// join to all entities that are alive.
    template <typename J> class MaybeJoin final {
      public:
        using Data = std::add_pointer_t<typename JoinTraits<J>::Data>;

        MaybeJoin(J &inner) : _inner(inner), _nonMask(JoinTraits<J>::getMask(inner).size()) { this->_nonMask.setAll(); }

        constexpr util::BitSet const &getMask() const noexcept { return this->_nonMask; }

        constexpr Data getData(std::size_t index) const
        {
            util::BitSet const &innerMask = JoinTraits<J>::getMask(this->_inner);

            if (index < innerMask.size() && innerMask[index])
                return &JoinTraits<J>::getData(this->_inner, index);
            return nullptr;
        }

        void adjustMask(std::size_t maxSize)
        {
            if (maxSize > this->_nonMask.size()) {
                this->_nonMask.resize(maxSize);
                this->_nonMask.setAll();
            }
        }

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

        constexpr static Data getData(MaybeJoin<J> &joinable, std::size_t index) { return joinable.getData(index); }
    };

    /// @internal
    /// Used to resize the "non"-mask to the largest size.
    template <Joinable J> struct JoinTraitsExt<MaybeJoin<J>> {
        constexpr static void adjustMask(MaybeJoin<J> &joinable, std::size_t maxSize) { joinable.adjustMask(maxSize); }
    };
} // namespace ecs

#endif // !defined(ECS_JOIN_MAYBE_JOIN_HPP_)
