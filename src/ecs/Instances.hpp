/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** ECS - Instances
*/

#ifndef ECS_TYPE_MAP_HPP_
#define ECS_TYPE_MAP_HPP_

#include <iterator>
#include <memory>
#include <typeindex>
#include <unordered_map>

namespace ecs
{
    /// A set with values identified by their type, all values must inherit from @b Base.
    ///
    /// @tparam Base The common parent class of all contained instances.
    template <typename Base> class Instances {
      public:
        /// Constructs an instance of @b Value in-place.
        ///
        /// @tparam Value The type of instance to create, must inherit from @b Base.
        /// @tparam Args The arguments to pass to the constructor of @b Value.
        ///
        /// @param error The content of the error to throw if @b Value is already in the set.
        /// @param args The arguments to pass to the constructor of @b Value.
        ///
        /// @returns A reference to the newly created value.
        ///
        /// @throws std::logic_error If an instance of @b Value was already added to this set.
        template <std::derived_from<Base> Value, typename... Args> Value &emplace(char const *error, Args &&...args)
        {
            std::type_index key(typeid(Value));

            if (this->_inner.contains(key))
                throw std::logic_error(error);

            std::unique_ptr<Value> instance(std::make_unique<Value, Args...>(std::forward<Args>(args)...));
            Value *instancePtr(instance.get());

            this->_inner.emplace(std::make_pair(key, std::move(instance)));
            return *instancePtr;
        }

        /// Fetches the contained instance of @b Value.
        ///
        /// @tparam Value The type of instance to fetch, must inherit from @b Base.
        ///
        /// @param error The content of the error to throw if @b Value is not in the set.
        ///
        /// @returns A reference to the instance of @b Value contained within.
        ///
        /// @throws std::logic_error If no instance of @b Value is in the set.
        template <std::derived_from<Base> Value> Value &get(char const *error) { return *this->getPtr<Value>(error); }

        /// Fetches the contained instance of @b Value.
        ///
        /// @tparam Value The type of instance to fetch, must inherit from @b Base.
        ///
        /// @param error The content of the error to throw if @b Value is not in the set.
        ///
        /// @returns A const reference to the instance of @b Value contained within.
        ///
        /// @throws std::logic_error If no instance of @b Value is in the set.
        template <std::derived_from<Base> Value> Value const &get(char const *error) const
        {
            return *this->getPtr<Value>(error);
        }

        /// Fetches the contained instance of @b Value.
        ///
        /// @tparam Value The type of instance to fetch, must inherit from @b Base.
        ///
        /// @param error The content of the error to throw if @b Value is not in the set.
        ///
        /// @returns A pointer to the instance of @b Value contained within.
        ///
        /// @throws std::logic_error If no instance of @b Value is in the set.
        template <std::derived_from<Base> Value> Value *getPtr(char const *error) const
        {
            auto found = this->_inner.find(std::type_index(typeid(Value)));

            if (found == this->_inner.end())
                throw std::logic_error(error);
            return dynamic_cast<Value *>(found->second.get());
        }

        /// @returns The backing storage.
        constexpr std::unordered_map<std::type_index, std::unique_ptr<Base>> const &getInner() const
        {
            return this->_inner;
        }

        /// @tparam Value The type of instance to test, must inherit from @b Base.
        ///
        /// @returns Whether the given instance type is contained in the set.
        template <std::derived_from<Base> Value> bool contains()
        {
            return this->_inner.contains(std::type_index(typeid(Value)));
        }

      private:
        std::unordered_map<std::type_index, std::unique_ptr<Base>> _inner;
    };
} // namespace ecs

#endif // !defined(ECS_TYPE_MAP_HPP_)
