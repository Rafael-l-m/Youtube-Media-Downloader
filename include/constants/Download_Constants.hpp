
#pragma once

#include <QRegularExpression>

namespace DOWNLOAD_CONSTANTS::DOWNLOAD_WORKER {
    inline constexpr int MIN_WAIT_TIME = 3000;
    inline constexpr int MAX_WAIT_TIME = 7000;
    inline constexpr int MIN_RATE = 225;
    inline constexpr int MAX_RATE = 650;
    inline constexpr int MAX_CONCURRENT_PROCESS = 3;
    inline constexpr int RETRIES = 5;
    inline constexpr int FRAGMENT_RETRIES = 15;
    inline constexpr int CONCURRENT_RETRIES = 2;

    inline static const QRegularExpression PATTERN_EXTRACT_PROGRESS(R"(\[download\]\s+(\d+(\.\d+)?)%)", QRegularExpression::CaseInsensitiveOption);

    inline const QString PATH = "PATH";

    inline const QStringList userAgents = {
            "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/123.0.0.0 Safari/537.36",
            "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Edg/123.0.0.0 Safari/537.36",
            "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:122.0) Gecko/20100101 Firefox/122.0",
            "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/123.0.0.0 Safari/537.36",
            "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/123.0.0.0 Safari/537.36",
            "Mozilla/5.0 (Linux; Android 12; Pixel 6) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/123.0.0.0 Mobile Safari/537.36"
        };

    namespace ERRORS_CAUSED_TOO_MANY_REQUESTS {
        inline const QByteArray CODE_403 = "403";
        inline const QByteArray CODE_429 = "429";
        inline const QByteArray FORBIDDEN = "Forbidden";
        inline const QByteArray LIMIT_EXCEEDED = "Limit exceeded";
        inline const QByteArray RATE_LIMIT = "Rate limit";
        inline const QByteArray TOO_MANY_REQUEST = "Too Many Requests";
    }
}

