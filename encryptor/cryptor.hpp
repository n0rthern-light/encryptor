#ifndef CRYPTOR_HPP
#define CRYPTOR_HPP

#include <vector>
#include <array>
#include <stdint.h>

namespace cryptor {
    using data_t = std::vector<uint8_t>;
    using key_t = std::array<uint8_t, 32>;

    bool Encrypt(const data_t& data, const key_t& key, data_t* out);
    bool Decrypt(const data_t& data, const key_t& key, data_t* out);
};

#endif
