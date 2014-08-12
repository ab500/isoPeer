#pragma once

#include <stdint.h>
#include <string>
#include <vector>
#include <array>
#include <type_traits>
#include <iterator>
#include <cassert>

namespace IsoPeer { namespace Common {
    
    // Contains methods that allow for Base58 encoding similar to what's used
    // for BitCoin wallet addresses.
    namespace Base58Encoder
    {
        namespace Details
        {
            template<typename>
            struct is_std_array : std::false_type {};

            template<typename T, std::size_t N>
            struct is_std_array<std::array<T, N>> : std::true_type{};

            extern std::string s_base58Chars;

            std::string EncodeFromBuffer(
                const uint8_t* data, const size_t size);

            int DecodeToPreAllocatedBuffer(
                const std::string& encoded, char* result, size_t len);

            bool ReserveOrEnsureSize(size_t size, std::vector<uint8_t>& dest);

            template <size_t N>
            bool ReserveOrEnsureSize(size_t size, std::array<uint8_t, N>& dest)
            {
                if (dest.size() >= size)
                {
                    dest.fill(0);
                    return true;
                }
                return false;
            }
        }

        std::string Encode(const std::vector<uint8_t>& source);

        template <int arraySize>
        std::string Encode(const std::array<uint8_t, arraySize>& source)
        {
            return Details::EncodeFromBuffer(source.data(), source.size());
        }

        bool Validate(const std::string& encoded);

        template <class DestContainer>
        bool Decode(const std::string& encoded, DestContainer& dest)
        {
            // Skip all the leading spaces or zeros in the encoded array.
            auto begin = encoded.begin();
            while (isspace(*begin) || *begin == Details::s_base58Chars[0])
                begin++;

            // Calculate the maximum possible size using ln(58)/ln(256) * 125, rounded up
            // to the nearest whole integer, with an extra byte for a NULL terminator.
            int maxSize = (encoded.end() - begin) * 733 / 1000 + 1;
            Details::ReserveOrEnsureSize(maxSize, dest);

            return true;
        }

    };

} }
