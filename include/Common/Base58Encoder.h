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
        static std::string Encode(const std::vector<uint8_t>& source)
        {
            return Details::EncodeFromBuffer(source.data(), source.size());
        }

        template <int arraySize>
        static std::string Encode(const std::array<uint8_t, arraySize>& source)
        {
            return Details::EncodeFromBuffer(source.data(), source.size());
        }

        bool Validate(const std::string& encoded);

        template <class DestContainer>
        static bool Decode(const std::string& encoded, DestContainer& dest)
        {
            // Skip all the leading spaces or zeros in the encoded array.
            auto begin = encoded.begin();
            while (isspace(*begin) || *begin == Details::s_base58Chars[0])
                begin++;

            size_t resultSize = encoded.end() - begin;
            Details::ReserveOrEnsureSize(resultSize, dest);
        }

        namespace Details
        {
            template<typename>
            struct is_std_array : std::false_type {};

            template<typename T, std::size_t N>
            struct is_std_array<std::array<T, N>> : std::true_type{};

            static std::string s_base58Chars;

            static std::string EncodeFromBuffer(
                const uint8_t* data, const size_t size);

            static int DecodeToPreAllocatedBuffer(
                const std::string& encoded, char* result, size_t len);

            template <class DestContainer, class = std::enable_if<is_std_array<DestContainer>>::type>
            static bool ReserveOrEnsureSize(size_t size, DestContainer& dest)
            {
                return dest.size() >= size;
            }

            template <class DestContainer, class = std::enable_if<!is_std_array<DestContainer>>::type>
            static bool ReserveOrEnsureSize(size_t size, DestContainer& dest)
            {
                dest.reserve(size);
                return true;
            }
        }
    };

} }
