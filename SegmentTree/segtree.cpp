#include <iostream>
#include <vector>

template <typename T>
class SegTree {
private:
	std::vector<T> tree;
	int N;

	void build(const std::vector<T>& arr, int curr, int left, int right) {
		if (left == right) tree[curr] = arr[left];
		else {
			int mid = (left + right) >> 1;
			build(arr, curr * 2, left, mid);
			build(arr, curr * 2 + 1, mid + 1, right);
			// TODO : implement recurrence relation 
			/*
			tree[curr] = tree[curr * 2] + tree[curr * 2 + 1];
			*/
		}
	}

	T query(int from, int to, int curr, int left, int right) {
		if (right < from or to < left) return 0;
		if (from <= left and right <= to) return tree[curr];
		
		int mid = (left + right) >> 1;
		// TODO : implement recurrence relation
		/*
		return query(from, to, curr * 2, left, mid)
			+ query(from, to, curr * 2 + 1, mid + 1, right);
		*/
	}

	void update(int idx, T diff, int curr, int left, int right) {
		if (left == right) {
			// TODO : implement diff update
			/*
			tree[curr] += diff;
			*/
		}
		else if (idx < left or right < idx) return;
		else {
			int mid = (left + right) >> 1;
			update(idx, diff, curr * 2, left, mid);
			update(idx, diff, curr * 2 + 1, mid + 1, right);
			// TODO : implement recurrence relation
			/*
			tree[curr] = tree[curr * 2] + tree[curr * 2 + 1];
			*/
		}
	}

public:
	SegTree(const std::vector<T>& arr) {
		N = arr.size();
		tree.resize(4 * N, 0);
		build(arr, 1, 0, N - 1);
	}

	T query(int from, int to) {
		return query(from, to, 1, 0, N - 1);
	}

	void update(int idx, T diff) {
		update(idx, diff, 1, 0, N - 1);
	}
};