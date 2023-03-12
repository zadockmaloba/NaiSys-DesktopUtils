#ifndef NAISYS_INDEXED_MAP_H
#define NAISYS_INDEXED_MAP_H

#include <vector>
#include <tuple>
#include <memory.h>

namespace NaiSys {
namespace Core {

template <typename T_ky, typename T_vl>
class IndexedMap
{
private:
    class Pair
    {
    public:
        Pair(const T_ky &key, const T_vl &value)
            : m_key{ key }, m_value{ value }
        {

        }


        T_ky key() const {
            return m_key;
        }
        void setKey(const T_ky &newKey) {
            m_key = newKey;
        }
        T_vl value() const {
            return m_value;
        }
        void setValue(const T_vl &newValue) {
            m_value = newValue;
        }

    private:
        T_ky m_key;
        T_vl m_value;
    };

public://typedefs
    using pair_array = std::vector<Pair>;

public:
    IndexedMap(const pair_array &p = {});
    ~IndexedMap();

public:
    void push_back(const Pair &pair) throw();
    void push_front(const Pair &pair) throw();
    void pop_back() throw();
    void pop_front() throw();

    pair_array pairs() const {
        return m_pairs;
    }
    void setPairs(const pair_array &newPairs) {
        m_pairs = newPairs;
    }
    size_t size() const {
        return m_pairs.size();
    }
    const T_vl at(const T_ky &_key) const {
        return this[_key].value();
    }

public://operators
    Pair &operator[](T_ky _key) const throw() {
        auto ret = std::for_each(m_pairs.begin(), m_pairs.end(),
        [_key](Pair& pr)->Pair&{
            if(_key == pr.key()) return pr;
        });
        return ret;
    }

private:
    pair_array m_pairs;
};

}
}

#endif //naisysindexedmap.h
