#include <iostream>
#include <vector>

class FenwickTree {
private:
	std::vector<int> bit;

public:
	FenwickTree(int size) {
		bit.resize(size + 1, 0);
	}

	void update(int idx, int val) {
		while (idx < bit.size()) {
			bit[idx] += val;
			idx += (idx & -idx);
		}
	}

	int query(int idx) {
		int sum = 0;
		while (idx > 0) {
			sum += bit[idx];
			idx -= (idx & -idx);
		}
	}

	int rangeQuery(int left, int right) {
		return query(right) - query(left - 1);
	}
};