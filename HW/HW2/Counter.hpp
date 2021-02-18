#ifndef COUNTER_HPP
#define COUNTER_HPP

#include <map>
#include <vector>

template <typename K>
class Counter {
    private:
        std::map<K, int> counter_;

    public:
        Counter(): counter_() {}
        Counter(std::vector<K> vals) {
            /*
            * @params:
            *   vals - vector of keys to init the counter map with
            */

            for (K k : vals) this->counter_.emplace(k, 0);
        }

        std::map<K, int> get_counter() const { return this->counter_; }

        int Count() {
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

        int Count(K key) {
            /*
            * @params:
            *   key - key to retrieve count of
            * 
            * @return: value at requested key
            */

            return this->counter_.at(key);
        }

        int Count(K min, K max) {
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

        void Remove(K key) {
            /*
            * @params:
            *   key - key to remove
            * 
            * @return: none
            */

            this->counter_.erase(key);
        }

        void Increment(K key) {
            /*
            * @params:
            *   key - key to increase the value of by 1
            * 
            * @return: none
            */

            this->counter_.at(key)++;
        }

        void Increment(K key, int n) {
            /*
            * @params:
            *   key - key to increase the value of
            *   n   - value to increase the key count by
            * 
            * @return: none
            */

            this->counter_.at(key) += n;
        }

        void Decrement(K key) {
            /*
            * @params:
            *   key - key to decrement the value of by 1
            * 
            * @return: none
            */

            this->counter_.at(key)--;
        }
};

#endif
