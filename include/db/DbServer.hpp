
#pragma once

#include "db/DbManager.hpp"
#include "db/Request.hpp"
#include <QTcpServer>

namespace DB {
    class DbServer final : public QObject {
        Q_OBJECT
    public:
        explicit DbServer(QObject* parent = nullptr);
        [[nodiscard]] bool start();
        [[nodiscard]] int getPort() const;

    private slots:
        void onNewConnection();
        void onReadyRead();

    private:
        static void sendResponse(const Request& req, const QJsonObject& data);
        static void sendError(QTcpSocket* socket, int id, const QString& msg);

        DbManager manager;
        QTcpServer server;
        quint16 port;
        QHash<Operation, std::function<void(const Request&)>> handlers;
    };
}
