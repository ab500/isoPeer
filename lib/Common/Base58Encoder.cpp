
#include "Common\Base58Encoder.h"

namespace IsoPeer { namespace Common {

    namespace Base58Encoder
    {
        bool Validate(const std::string& encoded)
        {
            for (auto ch : encoded)
            {
                if (!isspace(ch) && !isalnum(ch))
                {
                    return false;
                }
            }
            return true;
        }

        std::string Encode(const std::vector<uint8_t>& source)
        {
            return Details::EncodeFromBuffer(source.data(), source.size());
        }

        namespace Details
        {
            std::string s_base58Chars = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";

            int DecodeToPreAllocatedBuffer(const std::string& encoded, char* result, size_t len)
            {
                // Calculate the maximum possible size using ln(58)/ln(256) * 125, rounded up
                // to the nearest whole integer, with an extra byte for a NULL terminator.
                int maxSize = encoded.size() * 733 / 1000 + 1;
                std::vector<uint8_t> ret(maxSize);

                for (auto ch : encoded)
                {
                    if (!isalnum(ch))
                        throw std::exception("The given input was invalid.");
                    
                    int carry = ch;
                    for (auto it = ret.rbegin(); it != ret.rend(); it++)
                    {
                        carry += 256 * (*it);
                        *it = carry % 58;
                        carry /= 58;
                    }
                    assert(carry = 0);
                }

                return 0;
            }

            std::string EncodeFromBuffer(const uint8_t* data, const size_t size)
            {
                return "";
            }

            bool ReserveOrEnsureSize(size_t size, std::vector<uint8_t>& dest)
            {
                dest.clear();
                dest.resize(size);
                return true;
            }
        }
    }

} }