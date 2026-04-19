
#pragma once

#include "container/Download.hpp"
#include "container/ToolsPath.hpp"

namespace CORE {
    class SharedStorage final {
    public:
        static SharedStorage& instance();

        // CONTAINER::ToolsPath
        void setToolsPath(const CONTAINER::ToolsPath& tp) const;
        QSharedPointer<CONTAINER::ToolsPath> getToolsPath() const;

        // CONTAINER::Download
        bool addDownload(const CONTAINER::Download& newDownload);
        bool addDownloads(const QList<CONTAINER::Download>& newDownloads);
        bool removeDownload(int id);
        bool removeDownload(const CONTAINER::Download& newDownload);
        bool removeDownload(const QSharedPointer<CONTAINER::Download>& newDownload);
        void clear();
        QSharedPointer<CONTAINER::Download> getDownload(int id) const;
        QSharedPointer<QList<QSharedPointer<CONTAINER::Download>>> getDownloads() const;
        qsizetype getDownloadsSize() const;

    private:
        SharedStorage();
        bool ifContainsId(int id) const;
        void sort() const;
        bool addDownload(const QSharedPointer<CONTAINER::Download>& newDownload);

        mutable QMutex mutex;

        // CONTAINER::ToolsPath
        QSharedPointer<CONTAINER::ToolsPath> toolsPath;

        // CONTAINER::Download
        QSharedPointer<QList<QSharedPointer<CONTAINER::Download>>> downloadList;
        QHash<int, QSharedPointer<CONTAINER::Download>> downloadIndex;
    };
}
