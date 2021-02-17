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
            for (K k : vals) this->counter_.emplace(k, 0);
        }

        std::map<K, int> get_counter() { return this->counter_; }

        int Count() {
            int sum = 0;

            for (auto it = this->counter_.begin(); it!=this->counter_.end(); ++it) {
                sum += it->second;
            }

            return sum;
        }

        int Count(K key) {
            return this->counter_.at(key);
        }

        int Count(K min, K max) {
            int sum = 0;
            auto it = this->counter_.find(min), it_end = this->counter_.find(max);

            for (; it!=it_end; ++it) sum += it->second;

            return sum;
        }

        void Remove(K key) {
            this->counter_.erase(key);
        }

        void Increment(K key) {
            this->counter_.at(key)++;
        }

        void Increment(K key, int n) {
            this->counter_.at(key) += n;
        }

        void Decrement(K key) {
            this->counter_.at(key)--;
        }
};

#endif
