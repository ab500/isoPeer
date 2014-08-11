#pragma once

#include <stdint.h>
#include <string>
#include <vector>
#include <type_traits>
#include <iterator>

namespace IsoPeer { namespace Common {
    
    namespace Base64Encoder
    {
        template <class Iter, class = typename std::enable_if<std::is_same<typename std::iterator_traits<Iter>::value_type, uint8_t>::value>::type>
        static std::string Encode(const Iter& begin, const Iter& end)
        {
            
        }

        template <class ReturnType>
        static ReturnType Decode(const std::string& encoded);

        template <>
        static std::vector<uint8_t> Decode(const std::string& encoded);

        namespace Details
        {
            static void DecodeToPreAllocatedBuffer(
                const std::string& encoded, char* result, size_t len);
        }
    };

} }
