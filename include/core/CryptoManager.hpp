
#pragma once

#include <QFile>

namespace CORE {
    class CryptoManager final {
    public:
        CryptoManager();

        bool init();  // sodium_init + load/generate key

        // Encrypt/Decrypt
        [[nodiscard]] QByteArray encrypt(const QByteArray& plain) const;
        [[nodiscard]] QByteArray decrypt(const QByteArray& cipher) const;

        // Template
        template<typename T>
        bool saveEncrypted(const QString& filePath, const T& obj) const {
            if (!this->m_ready) return false;

            // Serialization
            QByteArray raw;
            {
                QDataStream out(&raw, QIODevice::WriteOnly);
                out << obj;
            }

            // Encrypt
            const auto enc = this->encrypt(raw);
            if (enc.isEmpty()) return false;

            QFile f(filePath);
            if (!f.open(QIODevice::WriteOnly | QIODevice::Truncate)) return false;

            f.write(enc);

            return true;
        }

        template<typename T>
        bool loadEncrypted(const QString& filePath, T& obj) const {
            if (!this->m_ready) return false;

            QFile f(filePath);
            if (!f.open(QIODevice::ReadOnly)) return false;

            const auto enc = f.readAll();
            if (enc.isEmpty()) return false;

            auto raw = this->decrypt(enc);
            if (raw.isEmpty()) return false;

            QDataStream in(&raw, QIODevice::ReadOnly);
            in >> obj;

            return true;
        }

    private:
        [[nodiscard]] bool loadKeyFromFile(const QString& path);
        [[nodiscard]] bool saveKeyToFile(const QString& path) const;
        void generateKey();

        QByteArray m_key;    // 32 bytes
        QByteArray m_nonce;  // 12 bytes
        bool m_ready = false;
    };
}
