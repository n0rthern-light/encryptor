#include "cryptor.hpp"
#include "chacha20.hpp"
#include "sha256.hpp"
#include <random>
#include <cstring>
#include <cstdint>

namespace cryptor {
    using nonce_t = std::array<uint8_t, 8>;  // 64-bit nonce for ChaCha20
    using tag_t = std::array<uint8_t, 32>;    // 32-bit CRC32 tag for integrity check

    void random_nonce(nonce_t& nonce) {
        std::random_device rd;
        std::mt19937 rng(rd());
        std::uniform_int_distribution<uint8_t> dist(0, 255);

        for (auto& byte : nonce) {
            byte = dist(rng);
        }
    }

    tag_t calculate_sha256(const data_t& data) {
        hash_sha256 hash;
        hash.sha256_init();
        hash.sha256_update(data.data(), data.size());
        auto hash_result = hash.sha256_final();
        return hash_result;
    }

    bool Encrypt(const data_t& plaintext, const key_t& key, data_t* out) {
        if (!out || plaintext.empty()) return false;

        nonce_t nonce;
        random_nonce(nonce);

        data_t ciphertext(plaintext.size());

        std::memcpy(ciphertext.data(), plaintext.data(), plaintext.size());

        Chacha20 chacha(key.data(), nonce.data());
        chacha.crypt(ciphertext.data(), plaintext.size());

        auto hash_tag = calculate_sha256(plaintext);

        out->resize(nonce.size() + ciphertext.size() + hash_tag.size());
        std::memcpy(out->data(), nonce.data(), nonce.size());
        std::memcpy(out->data() + nonce.size(), ciphertext.data(), ciphertext.size());
        std::memcpy(out->data() + nonce.size() + ciphertext.size(), hash_tag.data(), hash_tag.size());

        return true;
    }

    bool Decrypt(const data_t& encrypted, const key_t& key, data_t* out) {
        if (!out || encrypted.size() < nonce_t{}.size() + sizeof(tag_t)) return false;

        nonce_t nonce;
        tag_t tag;
        size_t ciphertext_len = encrypted.size() - nonce.size() - tag.size();
        data_t ciphertext(ciphertext_len);

        std::memcpy(nonce.data(), encrypted.data(), nonce.size());
        std::memcpy(ciphertext.data(), encrypted.data() + nonce.size(), ciphertext_len);
        std::memcpy(tag.data(), encrypted.data() + nonce.size() + ciphertext_len, tag.size());

        out->resize(ciphertext_len);

        std::memcpy(out->data(), ciphertext.data(), ciphertext_len);

        Chacha20 chacha(key.data(), nonce.data());
        chacha.crypt(out->data(), ciphertext_len);

        auto hash_tag = calculate_sha256(*out);
        tag_t received_hash_tag;
        std::memcpy(&received_hash_tag, tag.data(), sizeof(received_hash_tag));

        if (hash_tag != received_hash_tag) {
            return false;
        }

        return true;
    }
};

