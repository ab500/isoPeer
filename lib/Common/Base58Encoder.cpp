
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
                return 0;
            }

            // Adopted from BitCoin implementation (it was very good!)
            std::string EncodeFromBuffer(const uint8_t* begin, const uint8_t* end)
            {
                // Skip and count leading zeros.
                int zeros = 0;
                while (begin != end && *begin == 0) {
                    begin++;
                }

                // Converting from base 256 to base 58 requires an increased
                // number of digits. We first do the numerical conversion before
                // projecting it into our chosen character set.
                // The space conversion factor is computed as log(256) / log(58)
                // using integer math, rounding up.
                std::vector<uint8_t> b58((end - begin) * 138 / 100 + 1, 0);

                while (begin != end) {
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

            bool ReserveOrEnsureSize(size_t size, std::vector<uint8_t>& dest)
            {
                dest.clear();
                dest.resize(size);
                return true;
            }
        }
    }

} }