
#include "core/SharedStorage.hpp"

namespace CORE {
    // Public

    SharedStorage& SharedStorage::instance() {
        static SharedStorage inst;
        return inst;
    }

    SharedStorage::SharedStorage() {
        this->toolsPath = QSharedPointer<CONTAINER::ToolsPath>::create();
        this->downloadList = QSharedPointer<QList<QSharedPointer<CONTAINER::Download>>>::create();
    }


    // CONTAINER::ToolsPath
    void SharedStorage::setToolsPath(const CONTAINER::ToolsPath& tp) const {
        QMutexLocker locker(&this->mutex);
        this->toolsPath->setAll(tp);
    }

    QSharedPointer<CONTAINER::ToolsPath> SharedStorage::getToolsPath() const {
        QMutexLocker locker(&this->mutex);
        return this->toolsPath;
    }


    // CONTAINER::Download
    bool SharedStorage::addDownload(const CONTAINER::Download& newDownload) {return this->addDownload(QSharedPointer<CONTAINER::Download>::create(newDownload));}

    bool SharedStorage::addDownloads(const QList<CONTAINER::Download>& newDownloads) {
        for (const auto& d : newDownloads) {if (this->ifContainsId(d.getId())) return false;}
        for (const auto& d : newDownloads) {this->addDownload(d);} return true;
    }

    bool SharedStorage::removeDownload(const int id) {return this->downloadIndex.contains(id) ? this->removeDownload(this->downloadIndex.value(id)) : false;}

    bool SharedStorage::removeDownload(const CONTAINER::Download& newDownload) {return this->removeDownload(QSharedPointer<CONTAINER::Download>::create(newDownload));}

    bool SharedStorage::removeDownload(const QSharedPointer<CONTAINER::Download>& newDownload) {
        QMutexLocker locker(&this->mutex);

        if (newDownload && this->downloadIndex.contains(newDownload->getId())) {
            auto& list = *this->downloadList;
            const auto idd = newDownload->getId();

            for (auto it = list.begin(); it != list.end();) {if ((*it)->getId() == idd) it = list.erase(it); else ++it;}

            return this->downloadIndex.remove(newDownload->getId());
        }

        return false;
    }

    void SharedStorage::clear() {
        QMutexLocker locker(&this->mutex);
        this->downloadList->clear();
        this->downloadIndex.clear();
    }

    QSharedPointer<CONTAINER::Download> SharedStorage::getDownload(const int id) const {
        QMutexLocker locker(&this->mutex);
        return this->downloadIndex.value(id, nullptr);
    }

    QSharedPointer<QList<QSharedPointer<CONTAINER::Download>>> SharedStorage::getDownloads() const {
        QMutexLocker locker(&this->mutex);
        return this->downloadList->isEmpty() ? nullptr : this->downloadList;
    }

    qsizetype SharedStorage::getDownloadsSize() const {
        QMutexLocker locker(&this->mutex);
        return this->downloadList->size();
    }


    // Private

    bool SharedStorage::ifContainsId(const int id) const {return this->downloadIndex.contains(id);}

    void SharedStorage::sort() const {std::sort(this->downloadList->begin(), this->downloadList->end(), [](const QSharedPointer<CONTAINER::Download>& a, const QSharedPointer<CONTAINER::Download>& b) {return a->getId() < b->getId();});}

    bool SharedStorage::addDownload(const QSharedPointer<CONTAINER::Download>& newDownload) {
        QMutexLocker locker(&this->mutex);

        if (newDownload && !this->ifContainsId(newDownload->getId())) {
            this->downloadList->append(newDownload);
            this->downloadIndex.insert(newDownload->getId(), newDownload);
            this->sort();

            return true;
        }

        return false;
    }
}
