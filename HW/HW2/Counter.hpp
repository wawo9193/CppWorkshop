#ifndef COUNTER_HPP
#define COUNTER_HPP

#include <bits/stdc++.h>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <utility>
#include <vector>

struct CustomVar {
    std::string val;
    int another_val;
    bool and_another_one;

    // comparator for using inside of a stl map
    bool operator<(const CustomVar& other) const {
        return (val < other.val);
    }
};

// Output custom var
std::ostream& operator<<(std::ostream& os, const CustomVar& cv) {
    os << "(" << cv.val << ", " << cv.another_val << ", " << cv.and_another_one << ")";
    return os;
}

template <typename K>
class Counter {
    private:
        std::map<K, int> counter_;

    public:
        Counter(): counter_() {}
        Counter(std::vector<K> vals);

        std::map<K, int> get_counter() const { return this->counter_; }

        int Count();
        int Count(K key);
        int Count(K min, K max);
        void Remove(K key);
        void Increment(K key);
        void Increment(K key, int n);
        void Decrement(K key);
        void Decrement(K key, int n);
        K MostCommon();
        std::vector<K> MostCommon(int n);
        K LeastCommon();
        std::vector<K> LeastCommon(int n);
        std::map<K, double> Normalized();
        std::set<K> Keys();
        std::vector<int> Values();

        template <typename U>
        friend std::ostream& operator<<(std::ostream& os, const Counter<U> &b);
};

template <typename K>
Counter<K>::Counter(std::vector<K> vals) {
    /*
    * @params:
    *   vals - vector of keys to init the counter map with
    */

    for (K k : vals) {
        if (this->counter_.find(k)==this->counter_.end()) {
            this->counter_.emplace(k, 1);
        } else {
            this->counter_[k]++;
        }
    }
}

template <typename K>
int Counter<K>::Count() {
    /*
    * @params: none
    * 
    * @return: total of all values from the k,v pairs in counter
    */

    int sum = 0;

    for (auto it = this->counter_.begin(); it!=this->counter_.end(); ++it) {
        sum += it->second;
    }

    return sum;
}

template <typename K>
int Counter<K>::Count(K key) {
    /*
    * @params:
    *   key - key to retrieve count of
    * 
    * @return: value at requested key
    */

    return this->counter_[key];
}

template <typename K>
int Counter<K>::Count(K min, K max) {
    /*
    * @params:
    *   min - beginning of range
    *   max - end of range
    * 
    * @return: sum of values from min to max in counter,
    *          min - inclusive, max - exclusive
    */

    int sum = 0;
    auto it = this->counter_.find(min), it_end = this->counter_.find(max);

    for (; it!=it_end; ++it) sum += it->second;

    return sum;
}

template <typename K>
void Counter<K>::Remove(K key) {
    /*
    * @params:
    *   key - key to remove
    * 
    * @return: none
    */

    this->counter_.erase(key);
}

template <typename K>
void Counter<K>::Increment(K key) {
    /*
    * @params:
    *   key - key to increase the value of by 1
    * 
    * @return: none
    */

    this->counter_[key]++;
}

template <typename K>
void Counter<K>::Increment(K key, int n) {
    /*
    * @params:
    *   key - key to increase the value of
    *   n   - value to increase the key count by
    * 
    * @return: none
    */

    this->counter_[key] += n;
}

template <typename K>
void Counter<K>::Decrement(K key) {
    /*
    * @params:
    *   key - key to decrement the value of by 1
    * 
    * @return: none
    */

    this->counter_[key] = std::max(this->counter_[key] - 1, 0);
}

template <typename K>
void Counter<K>::Decrement(K key, int n) {
    /*
    * @params:
    *   key - key to decrement the value of by 1
    *   n   - value to decrement the value at key by
    * 
    * @return: none
    */

    this->counter_[key] = std::max(this->counter_[key] - n, 0);
}

template <typename K>
K Counter<K>::MostCommon() {
    /*
    * @params: none
    * 
    * @return: key with max mapped value in counter
    */

    if (this->counter_.empty()) {
        throw std::domain_error("err");
    } else {
        K max_key;
        int max_val = -1;

        auto it = this->counter_.begin();

        for (; it!=this->counter_.end(); ++it) {
            if (it->second>max_val) {
                max_key = it->first;
                max_val = it->second;
            }
        }

        return max_key;
    }
}

template <typename K>
std::vector<K> Counter<K>::MostCommon(int n) {
    /*
    * @params:
    *   n - how many of the most common keys are called for
    * 
    * @return: vector of the n most 'counted' keys in the counter,
    *          and if values are equivalent, higher priority goes
    *          to the beginning keys in sorted order.
    * 
    * i.e. {"a":2, "b":2, "c":3} where n=2, gives {"a","c"}
    */

    std::vector<K> max_keys;

    // this data structure is a map that goes from greater to least by the value from the counter map,
    // and the value of this map is a max heap of the keys from the counter map.
    std::map<int, std::priority_queue<K, std::vector<K>, std::greater<K> >, std::greater<int> > all_max;

    if (this->counter_.empty()) {
        throw std::domain_error("err");
    } else {
        auto c_it = this->counter_.begin();

        for (; c_it!=this->counter_.end(); ++c_it) {
            all_max[c_it->second].push(c_it->first);
        }

        auto m_it = all_max.begin();

        for (; m_it!=all_max.end(); ++m_it) {
            if (!n) break;

            while(n && !m_it->second.empty()) {
                max_keys.push_back(m_it->second.top());
                m_it->second.pop();
                --n;
            }
        }
    }

    return max_keys;
}

template <typename K>
K Counter<K>::LeastCommon() {
    /*
    * @params: none
    * 
    * @return: key with min mapped value in counter
    */

    if (this->counter_.empty()) {
        throw std::domain_error("u goofed");
    } else {
        K min_key;
        int min_val = INT_MAX;

        auto it = this->counter_.begin();

        for (; it!=this->counter_.end(); ++it) {
            if (it->second<min_val) {
                min_key = it->first;
                min_val = it->second;
            }
        }

        return min_key;
    }
}

template <typename K>
std::vector<K> Counter<K>::LeastCommon(int n) {
    /*
    * @params:
    *   n - how many of the least common keys are called for
    * 
    * @return: vector of the n least 'counted' keys in the counter,
    *          and if values are equivalent, higher priority goes
    *          to the beginning keys in sorted order.
    * 
    * i.e. {"a":2, "b":3, "c":3} where n=2, gives {"a","b"}
    */

    std::deque<K> min_keys;
    int min_val = INT_MAX;

    if (this->counter_.empty()) {
        throw std::domain_error("err");
    } else {
        auto it = this->counter_.rbegin();

        for (; it!=this->counter_.rend(); ++it) {
            if (it->second<min_val) {
                if ((int)min_keys.size()==n) min_keys.pop_back();
                min_keys.push_front(it->first);
                min_val = it->second;
            } else if (it->second==min_val) {
                if ((int)min_keys.size()==n) min_keys.pop_back();
                min_keys.push_front(it->first);
            }
        }
    }

    return std::vector<K>(min_keys.begin(), min_keys.end());
}

template <typename K>
std::map<K, double> Counter<K>::Normalized() {
    /*
    * @params: none
    * 
    * @return: map that maps the keys in counter to their normalized weights
    *          based on their counts and the total.
    * 
    * i.e. {"cat": 8, "dog": 4, "hamster": 2,"eagle": 6} will give a normalized
    *      map of, {"cat": 0.4, "dog": 0.2, "hamster":0.1, "eagle": 0.3}
    */

    std::map<K, double> norm_counter;
    double total = Count();

    auto it = this->counter_.begin();

    for (; it!=this->counter_.end(); ++it) {
        norm_counter.emplace(it->first, it->second / total);
    }

    return norm_counter;
}

template <typename K>
std::set<K> Counter<K>::Keys() {
    /*
    * @params: none
    * 
    * @return: set of all keys in counter
    */

    std::set<K> key_set;

    auto it = this->counter_.begin();

    for (; it!=this->counter_.end(); ++it) {
        key_set.insert(it->first);
    }

    return key_set;
}

template <typename K>
std::vector<int> Counter<K>::Values() {
    /*
    * @params: none
    * 
    * @return: vector of all values in counter
    */

    std::vector<int> value_vector;

    auto it = this->counter_.begin();

    for (; it!=this->counter_.end(); ++it) {
        value_vector.push_back(it->second);
    }

    return value_vector;
}

template <typename U>
std::ostream& operator<<(std::ostream& os, const Counter<U>& b) {
    /* OVERLOADS THE `<<` OPERATOR TO OUTPUT COUNTER MAP */

    auto it = b.counter_.begin();

    os << "{";
    for (; it!=b.counter_.end(); ++it) {
        os << it->first << ":" << it->second << ",";
    }
    os << "}\n";
    return os;
}

#endif
