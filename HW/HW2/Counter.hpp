#ifndef COUNTER_HPP
#define COUNTER_HPP

#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <utility>
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

        K MostCommon() {
            /*
            * @params: none
            * 
            * @return: key with max mapped value in counter
            */

            if (this->counter_.empty()) {
                throw std::domain_error("err bro");
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

        std::vector<K> MostCommon(int n) {
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

            std::deque<K> max_keys;
            int max_val = -1;

            if (this->counter_.empty()) {
                throw std::domain_error("err bro");
            } else {
                auto it = this->counter_.begin();

                for (; it!=this->counter_.end(); ++it) {
                    if (it->second>max_val) {
                        if (max_keys.size()==n) max_keys.pop_back();
                        max_keys.push_back(it->first);
                        max_val = it->second;
                    } else if (it->second==max_val) {
                        if (max_keys.size()==n) max_keys.pop_front();
                        max_keys.push_back(it->first);
                    }
                }
            }

            return std::vector<K>(max_keys.begin(), max_keys.end());
        }

        K LeastCommon() {
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

        std::vector<K> LeastCommon(int n) {
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
                throw std::domain_error("err bro");
            } else {
                auto it = this->counter_.rbegin();

                for (; it!=this->counter_.rend(); ++it) {
                    if (it->second<min_val) {
                        if (min_keys.size()==n) min_keys.pop_back();
                        min_keys.push_front(it->first);
                        min_val = it->second;
                    } else if (it->second==min_val) {
                        if (min_keys.size()==n) min_keys.pop_back();
                        min_keys.push_front(it->first);
                    }
                }
            }

            return std::vector<K>(min_keys.begin(), min_keys.end());
        }

        std::map<K, double> Normalized() {
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

        std::set<K> Keys() {
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

        std::vector<int> Values() {
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

        friend std::ostream& operator<<(std::ostream& os, const Counter<K> &b) {
            /* OVERLOADS THE `<<` OPERATOR TO OUTPUT COUNTER MAP */

            auto it = b.counter_.begin();

            os << "{";
            for (; it!=--b.counter_.end(); ++it) {
                os << it->first << ": " << std::to_string(it->second) << ", ";
            }
            os << it->first << ": " << std::to_string(it->second) << "}";

            return os;
        }
};

#endif
