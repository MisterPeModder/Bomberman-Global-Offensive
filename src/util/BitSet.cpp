/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** A more efficient dynamic bitset
*/

#include "util/BitSet.hpp"

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <vector>
#include <string_view>

namespace util
{
    BitSet::BitSet(std::size_t initialSize) : _size(initialSize), _store(getStoreWordCount(initialSize)) {}

    BitSet::BitSet(std::string_view bitString) : BitSet(bitString.size())
    {
        for (std::size_t i = 0, s = bitString.size(); i < s; ++i)
            this->set(i, bitString[s - i - 1] == '1');
    }

    BitSet &BitSet::setAll(bool value) noexcept
    {
        for (auto &word : this->_store)
            word = value ? ~std::uint64_t(0) : std::uint64_t(0);
        this->normalize();
        return *this;
    }

    bool BitSet::operator==(BitSet const &other) const noexcept { return this->_store == other._store; }

    bool BitSet::operator!=(BitSet const &other) const noexcept { return this->_store != other._store; }

    BitSet &BitSet::flip() noexcept
    {
        for (auto &word : this->_store)
            word = ~word;
        this->normalize();
        return *this;
    }

    BitSet BitSet::operator~() const
    {
        BitSet copy(*this);

        copy.flip();
        return copy;
    }

    BitSet BitSet::operator&(BitSet const &other) const
    {
        BitSet result(std::min(this->_size, other._size));

        for (std::size_t i = 0, s = result._store.size(); i < s; ++i)
            result._store[i] = this->_store[i] & other._store[i];
        result.normalize();
        return result;
    }

    BitSet BitSet::operator|(BitSet const &other) const
    {
        BitSet result(std::min(this->_size, other._size));

        for (std::size_t i = 0, s = result._store.size(); i < s; ++i)
            result._store[i] = this->_store[i] | other._store[i];
        result.normalize();
        return result;
    }

    BitSet BitSet::operator^(BitSet const &other) const
    {
        BitSet result(std::min(this->_size, other._size));

        for (std::size_t i = 0, s = result._store.size(); i < s; ++i)
            result._store[i] = this->_store[i] ^ other._store[i];
        result.normalize();
        return result;
    }

    BitSet &BitSet::operator&=(BitSet const &other) noexcept
    {
        this->_resize(std::min(this->_size, other._size));
        for (std::size_t i = 0, s = this->_store.size(); i < s; ++i)
            this->_store[i] &= other._store[i];
        this->normalize();
        return *this;
    }

    BitSet &BitSet::operator|=(BitSet const &other) noexcept
    {
        this->_resize(std::min(this->_size, other._size));
        for (std::size_t i = 0, s = this->_store.size(); i < s; ++i)
            this->_store[i] |= other._store[i];
        this->normalize();
        return *this;
    }

    BitSet &BitSet::operator^=(BitSet const &other) noexcept
    {
        this->_resize(std::min(this->_size, other._size));
        for (std::size_t i = 0, s = this->_store.size(); i < s; ++i)
            this->_store[i] ^= other._store[i];
        this->normalize();
        return *this;
    }

    void BitSet::normalize() noexcept
    {
        if ((this->_size & 0b111111) != 0) {
            std::uint64_t &last = *this->_store.rbegin();
            uint64_t mask = ~((~std::uint64_t(0)) << (this->_size & 0b111111));
            last &= mask;
        }
    }

    void BitSet::_resize(std::size_t size)
    {
        this->_store.resize(getStoreWordCount(size));
        this->_size = size;
    }

    BitSet &BitSet::push(bool value)
    {
        this->resize(this->_size + 1);
        this->set(this->_size - 1, value);
        return *this;
    }

    bool BitSet::pop()
    {
        bool value = this->test(this->_size - 1);
        this->resize(this->_size - 1);
        return value;
    }

    std::ostream &operator<<(std::ostream &output, BitSet const &set)
    {
        for (std::size_t s = set.size(), i = s; i > 0; --i)
            output << (set.test(i - 1) ? '1' : '0');
        return output;
    }
} // namespace util
