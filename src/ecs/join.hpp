/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** ECS - Component & Resource iteration
*/

#ifndef ECS_JOIN_HPP_
#define ECS_JOIN_HPP_

#include "ecs/join/Join.hpp"
#include "ecs/join/Joinable.hpp"
#include "ecs/join/MaybeJoin.hpp"

/// @file
///
/// Provides the @ref join() function that allows one to iterate over multiple components and resources at once.
///
/// The @ref join() function currenly accepts:
/// - @ref Entities: fetched from @ref SystemData::getResource<Entities>().
/// - @ref MapStorage: fetched from @ref SystemData::getStorage().
/// - @ref MarkerStorage: fetched from @ref SystemData::getStorage().
/// - @ref MaybeJoin: created by @ref maybe().
///
/// Powered by black magic™

/// Entity-Component-System namespace.
namespace ecs
{
    /// Combines multiple Joinable values into a single iterable container.
    ///
    /// @param first The first joinable value.
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
