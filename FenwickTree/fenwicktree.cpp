#include <iostream>
#include <vector>

template <typename T>
class FenwickTree {
private:
	std::vector<T> bit;

public:
	FenwickTree(int size) {
		bit.resize(size + 1, 0);
	}

	void update(int idx, T diff) {
		while (idx < bit.size()) {
			bit[idx] += diff;
			idx += (idx & -idx);
		}
	}

	T query(int idx) {
		T sum = 0;
		while (idx > 0) {
			sum += bit[idx];
			idx -= (idx & -idx);
		}
	}

	T rangeQuery(int left, int right) {
		return query(right) - query(left - 1);
	}
};