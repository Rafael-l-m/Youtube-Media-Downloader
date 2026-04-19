
#pragma once

#include <boost/bimap.hpp>

namespace CORE {
    class IdIndexMap final {
    public:
        using Bimap = boost::bimap<boost::bimaps::set_of<int>, boost::bimaps::set_of<int>>;
        Bimap map;

        void insert(int id);
        void erase(int id);
        void clear();
        [[nodiscard]] int indexOf(int id) const;  // id -> index
        [[nodiscard]] int idAt(int index) const;  // index -> id
        [[nodiscard]] size_t size() const;

    private:
        void rebuildIndex();
    };
}
