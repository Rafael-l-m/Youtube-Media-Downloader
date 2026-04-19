
#include "core/IdIndexMap.hpp"

namespace CORE {
    // Public

    void IdIndexMap::insert(const int id) {
        this->map.left.insert(Bimap::left_value_type{id, static_cast<int>(this->map.size())});
        this->rebuildIndex();
    }

    void IdIndexMap::erase(const int id) {
        this->map.left.erase(id);
        this->rebuildIndex();
    }

    void IdIndexMap::clear() {this->map.clear();}

    int IdIndexMap::indexOf(const int id) const {
        const auto it = this->map.left.find(id);
        if (it == this->map.left.end()) return -1;
        return it->second;
    }

    int IdIndexMap::idAt(const int index) const {
        const auto it = this->map.right.find(index);
        if (it == this->map.right.end()) return -1;
        return it->second;
    }

    size_t IdIndexMap::size() const {return this->map.size();}


    // Private

    void IdIndexMap::rebuildIndex() {
        Bimap newMap;
        int idx = 0;
        for (const auto& p : this->map.left) {newMap.insert({p.first, idx++});}
        this->map.swap(newMap);
    }
}
