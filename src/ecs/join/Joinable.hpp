/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** ECS - Component & Resource iteration
*/

/// @file
///
/// The Joinable Trait.

#ifndef ECS_JOIN_JOINABLE_HPP_
#define ECS_JOIN_JOINABLE_HPP_

#include "util/BitSet.hpp"

#include <concepts>
#include <cstdint>

/// Entity-Component-System namespace.
namespace ecs
{
    /// Base case for non-implenting types.
    template <typename J> struct JoinTraits {
        // empty, only specializations of JoinTraits contain data here.
    };

    /// Optional Join traits.
    template <typename J> struct JoinTraitsExt {
        constexpr static void adjustMask([[maybe_unused]] J &joinable, [[maybe_unused]] std::size_t maxSize) {}
    };

    /// Implemented by types that can be joined.
    template <typename J>
    concept Joinable = requires(J &joinable, J const &cjoinable, std::size_t index, std::size_t maxSize)
    {
        typename JoinTraits<J>::Data;

        // clang-format off
        { JoinTraitsExt<J>::adjustMask(joinable, maxSize) } -> std::same_as<void> ;
        { JoinTraits<J>::getMask(cjoinable) } -> std::same_as<util::BitSet const &>;
        { JoinTraits<J>::getData(joinable, index) } -> std::same_as<typename JoinTraits<J>::Data>;
        // clang-format on
    };
} // namespace ecs

#endif // !defined(ECS_JOIN_JOINABLE_HPP_)
