
#pragma once

#include "constants/Db_Constants.hpp"

namespace DB {
    enum class Operation {
        VerifyState,
        AddInformation,
        GetInformation,
        GetAllInformation,
        UpdateInformation,
        DeleteInformation,
        DeleteAllInformation,
        Unknown
    };

    inline Operation parseOperation(const QString& op) {
        if (op.compare(DB_CONSTANTS::OPERATIONS::VERIFY_STATE, Qt::CaseInsensitive) == 0) return Operation::VerifyState;
        if (op.compare(DB_CONSTANTS::OPERATIONS::ADD_INFORMATION, Qt::CaseInsensitive) == 0) return Operation::AddInformation;
        if (op.compare(DB_CONSTANTS::OPERATIONS::GET_INFORMATION, Qt::CaseInsensitive) == 0) return Operation::GetInformation;
        if (op.compare(DB_CONSTANTS::OPERATIONS::GET_ALL_INFORMATION, Qt::CaseInsensitive) == 0) return Operation::GetAllInformation;
        if (op.compare(DB_CONSTANTS::OPERATIONS::UPDATE_INFORMATION, Qt::CaseInsensitive) == 0) return Operation::UpdateInformation;
        if (op.compare(DB_CONSTANTS::OPERATIONS::DELETE_INFORMATION, Qt::CaseInsensitive) == 0) return Operation::DeleteInformation;
        if (op.compare(DB_CONSTANTS::OPERATIONS::DELETE_ALL_INFORMATION, Qt::CaseInsensitive) == 0) return Operation::DeleteAllInformation;

        return Operation::Unknown;
    }

    inline QString opToString(const Operation& op) {
        switch (op) {
            case Operation::VerifyState: return DB_CONSTANTS::OPERATIONS::VERIFY_STATE;
            case Operation::AddInformation: return DB_CONSTANTS::OPERATIONS::ADD_INFORMATION;
            case Operation::GetInformation: return DB_CONSTANTS::OPERATIONS::GET_INFORMATION;
            case Operation::GetAllInformation: return DB_CONSTANTS::OPERATIONS::GET_ALL_INFORMATION;
            case Operation::UpdateInformation: return DB_CONSTANTS::OPERATIONS::UPDATE_INFORMATION;
            case Operation::DeleteInformation: return DB_CONSTANTS::OPERATIONS::DELETE_INFORMATION;
            case Operation::DeleteAllInformation: return DB_CONSTANTS::OPERATIONS::DELETE_ALL_INFORMATION;
            default: return DB_CONSTANTS::OPERATIONS::UNKNOWN;
        }
    }
}
