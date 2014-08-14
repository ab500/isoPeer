
#include "Common\Base58Encoder.h"

namespace {
    std::string s_base58Chars = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";
}

namespace IsoPeer { namespace Common {

    namespace Base58Encoder
    {
        std::string Encode(const std::vector<uint8_t>& source)
        {
            // 138 / 100 is approximately log(256) / log(58), which represents the
            // conversion factor for the lenght of byte arrays in the respective bases. 
            std::vector<uint8_t> b58(source.size() * 138 / 100 + 1, 0);

            for (auto byte : source) {
                int carry = byte;
                for (auto iter = b58.rbegin(); iter != b58.rend(); iter++) {
                    carry += 256 * (*iter);
                    *iter = carry % 58;
                    carry /= 58;
                }
                // If carry is nonzero we somehow didn't allocate enough space in b58 to
                // hold the entire number.
                assert(carry == 0);
            }

            // Ignore any leading spaces and don't allocate them into
            // the string we're about to return.
            auto iter = b58.begin();
            while (iter != b58.end() && *iter == 0)
                iter++;

            // Finally map the rebased base58 bytes to their ASCII characters.
            std::string ret;
            ret.reserve(b58.end() - iter);
            while (iter != b58.end()) {
                ret += (s_base58Chars[*iter]);
                iter++;
            }
            return ret;
        }

        bool Decode(const std::string& encoded, std::vector<uint8_t>& dest)
        {
            // 733 / 1000 is approximately log(58) / log(256), which represents the
            // conversion factor for the lenght of byte arrays in the respective bases.
            std::vector<uint8_t> b256(encoded.size() * 733 / 1000 + 1);

            for (auto ch : encoded) {
                // Map the character to its actual numerical value in base58.
                auto chPos = std::find(s_base58Chars.begin(), s_base58Chars.end(), ch);
                if (chPos == s_base58Chars.end())
                    return false;

                int carry = chPos - s_base58Chars.begin();
                for (auto iter = b256.rbegin(); iter != b256.rend(); iter++) {
                    carry += 58 * (*iter);
                    *iter = carry % 256;
                    carry /= 256;
                }
                assert(carry == 0);
            }

            // Ignore any leading zeros.
            auto iter = b256.begin();
            while (iter != b256.end() && *iter == 0)
                iter++;

            dest.reserve(b256.end() - iter);
            while (iter != b256.end())
                dest.push_back(*(iter++));

            return true;
        }
    }

} }