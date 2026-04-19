
#include "constants/Core_Constants.hpp"
#include "core/CryptoManager.hpp"
#include <sodium.h>
#include <QDir>
#include <QStandardPaths>

namespace CORE {
    CryptoManager::CryptoManager() = default;

    bool CryptoManager::init() {
        if (sodium_init() < 0) return false;

        const auto configDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
        if (const QDir dir; !dir.exists(configDir)) (void)dir.mkpath(configDir);

        if (const auto keyPath = configDir + QDir::separator() + CORE_CONSTANTS::CRYPTO_MANAGER::DEFAULT_KEY_NAME; !this->loadKeyFromFile(keyPath)) {
            this->generateKey();

            if (!this->saveKeyToFile(keyPath)) return false;
        }

        this->m_ready = true;

        return true;
    }

    QByteArray CryptoManager::encrypt(const QByteArray& plain) const {
        if (!this->m_ready) return {};

        QByteArray cipher;
        cipher.resize(plain.size() + crypto_aead_aes256gcm_ABYTES);

        unsigned long long cipher_len = 0;

        if (crypto_aead_aes256gcm_encrypt(
            reinterpret_cast<unsigned char*>(cipher.data()),
            &cipher_len,
            reinterpret_cast<const unsigned char*>(plain.data()),
            plain.size(),
            nullptr,
            0,
            nullptr,
            reinterpret_cast<const unsigned char*>(this->m_nonce.data()),
            reinterpret_cast<const unsigned char*>(this->m_key.data())) != 0) return {};

        cipher.resize(static_cast<qsizetype>(cipher_len));

        return cipher;
    }

    QByteArray CryptoManager::decrypt(const QByteArray& cipher) const {
        if (!this->m_ready) return {};

        QByteArray plain;
        plain.resize(cipher.size());

        unsigned long long plain_len = 0;

        if (crypto_aead_aes256gcm_decrypt(
            reinterpret_cast<unsigned char *>(plain.data()),
            &plain_len,
            nullptr,
            reinterpret_cast<const unsigned char *>(cipher.data()),
            cipher.size(),
            nullptr,
            0,
            reinterpret_cast<const unsigned char *>(this->m_nonce.data()),
            reinterpret_cast<const unsigned char *>(this->m_key.data())) != 0) return {};

        plain.resize(static_cast<qsizetype>(plain_len));

        return plain;
    }


    // Private

    bool CryptoManager::loadKeyFromFile(const QString& path) {
        QFile f(path);
        if (!f.open(QIODevice::ReadOnly)) return false;

        QDataStream in(&f);
        in >> this->m_key >> this->m_nonce;

        return this->m_key.size() == crypto_aead_aes256gcm_KEYBYTES && this->m_nonce.size() == crypto_aead_aes256gcm_NPUBBYTES;
    }

    bool CryptoManager::saveKeyToFile(const QString& path) const {
        QFile f(path);
        if (!f.open(QIODevice::WriteOnly | QIODevice::Truncate)) return false;

        QDataStream out(&f);
        out << this->m_key << this->m_nonce;

        return true;
    }

    void CryptoManager::generateKey() {
        this->m_key.resize(crypto_aead_aes256gcm_KEYBYTES);
        this->m_nonce.resize(crypto_aead_aes256gcm_NPUBBYTES);

        randombytes_buf(this->m_key.data(), this->m_key.size());
        randombytes_buf(this->m_nonce.data(), this->m_nonce.size());
    }
}
