
#include "Common\Base58Encoder.h"

namespace {
    std::string s_base58Chars = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";
}

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
            // Skip and count leading zeros.
            int zeros = 0;
            auto begin = source.begin();
            while (begin != source.end() && *begin == 0) {
                begin++;
            }

            // Converting from base 256 to base 58 requires an increased
            // number of digits. We first do the numerical conversion before
            // projecting it into our chosen character set.
            // The space conversion factor is computed as log(256) / log(58)
            // using integer math, rounding up.
            std::vector<uint8_t> b58((source.end() - begin) * 138 / 100 + 1, 0);

            while (begin != source.end()) {
                // This loop is performing two functions:
                // Because we're working from the most significant digit backwards
                // we take each existing value and shift it a up a magnitude. That's
                // why we multiply by 256 each round. We pushed the number in the
                // most significant position into our new array first, and by the
                // time we're done we want it to be multipled by its base the number
                // of times equal to its position.
                //
                // The second thing its doing is taking the current byte value and
                // distributing it through the current numbers, pushing the carry
                // over towards the more significant columns.
                int carry = *begin;
                for (auto iter = b58.rbegin(); iter != b58.rend(); iter++) {
                    carry += 256 * (*iter);
                    *iter = carry % 58;
                    carry /= 58;
                }
                // If carry is nonzero we somehow didn't allocate enough space in b58 to
                // hold the entire number.
                assert(carry == 0);
                begin++;
            }

            auto iter = b58.begin();
            while (iter != b58.end() && *iter == 0)
                iter++;

            std::string ret;
            ret.reserve(zeros + (b58.end() - iter));
            ret.assign(zeros, s_base58Chars[0]);
            while (iter != b58.end()) {
                ret += (s_base58Chars[*iter]);
                iter++;
            }
            return ret;
        }

        bool Decode(const std::string& encoded, std::vector<uint8_t>& dest)
        {
            auto iter = encoded.begin();
            while (iter != encoded.end() && isspace(*iter))
                iter++;

            int zeros = 0;
            while (iter < encoded.end() && *iter == '1') {
                zeros++;
                iter++;
            }

            std::vector<uint8_t> b256((encoded.end() - iter) * 733 / 1000 + 1);

            while (iter != encoded.end() && !isspace(*iter)) {

                auto chPos = std::find(s_base58Chars.begin(), s_base58Chars.end(), *iter);
                if (chPos == s_base58Chars.end())
                    return false;

                int carry = chPos - s_base58Chars.begin();
                for (auto b256iter = b256.rbegin(); b256iter != b256.rend(); b256iter++) {
                    carry += 58 * (*b256iter);
                    *b256iter = carry % 256;
                    carry /= 256;
                }
                assert(carry == 0);
                iter++;
            }

            while (iter != encoded.end() && isspace(*iter))
                iter++;
            if (iter != encoded.end())
                return false;

            auto b256iter = b256.begin();
            while (b256iter != b256.end() && *b256iter == 0)
                b256iter++;

            dest.resize(zeros + (b256.end() - b256iter));
            dest.assign(zeros, 0x00);
            std::copy(b256iter, b256.end(), dest.begin() + zeros);

            return true;
        }
    }

} }