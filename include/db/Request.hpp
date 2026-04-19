
#pragma once

#include <db/Operation.hpp>
#include <db/Specification.hpp>
#include <QPointer>
#include <QTcpSocket>

namespace DB {
    struct Request {
        int id;
        Operation op;
        Specification spec;
        QJsonObject params;
        QPointer<QTcpSocket> socket;
    };
}
