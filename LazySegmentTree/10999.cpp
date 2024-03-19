#include <iostream>
#include <vector>
#include <iomanip>

#define UPDATE 1
#define QUERY 2

template <typename T>
class LazySegTree {
private:
	int N;
	std::vector<T> tree;
	std::vector<T> lazy;

	void build(const std::vector<T>& arr, int curr, int left, int right) {
		if (left == right) tree[curr] = arr[left];
		else {
			int mid = (left + right) >> 1;
			build(arr, curr * 2, left, mid);
			build(arr, curr * 2 + 1, mid + 1, right);
			tree[curr] = tree[curr * 2] + tree[curr * 2 + 1];
		}
	}

	void propagate(int curr, int left, int right) {
		if (lazy[curr] != 0) {
			tree[curr] += lazy[curr] * (right - left + 1);
			if (left != right) {
				lazy[curr * 2] += lazy[curr];
				lazy[curr * 2 + 1] += lazy[curr];
			}
			lazy[curr] = 0;
		}
	}

	T query(int from, int to, int curr, int left, int right) {
		propagate(curr, left, right);
		if (right < from or to < left) return 0;
		if (from <= left and right <= to) return tree[curr];

		int mid = (left + right) >> 1;
		return query(from, to, curr * 2, left, mid)
			+ query(from, to, curr * 2 + 1, mid + 1, right);
	}

	void update(int from, int to, T diff, int curr, int left, int right) {
		propagate(curr, left, right);
		if (right < from or to < left) return;
		if (from <= left and right <= to) {
			tree[curr] += diff * (right - left + 1);
			if (left != right) {
				lazy[curr * 2] += diff;
				lazy[curr * 2 + 1] += diff;
			}
		}
		else {
			int mid = (left + right) >> 1;
			update(from, to, diff, curr * 2, left, mid);
			update(from, to, diff, curr * 2 + 1, mid + 1, right);
			tree[curr] = tree[curr * 2] + tree[curr * 2 + 1];
		}
	}

public:
	LazySegTree(const std::vector<T>& arr) {
		N = arr.size();
		tree.resize(4 * N);
		lazy.resize(4 * N);
		build(arr, 1, 0, N - 1);
	}

	T query(int from, int to) {
		return query(from, to, 1, 0, N - 1);
	}

	void update(int from, int to, T diff) {
		update(from, to, diff, 1, 0, N - 1);
	}
};

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);

	int N, M, K;
	std::cin >> N >> M >> K;

	std::vector<long long> arr(N);
	for (auto& x : arr) std::cin >> x;

	LazySegTree<long long> lazysegtree(arr);

	for (int i = 0; i < M + K; i++) {
		int q;
		std::cin >> q;

		if (q == UPDATE) {
			int from, to;
			long long diff;
			std::cin >> from >> to >> diff;
			from--; to--;
			lazysegtree.update(from, to, diff);
		}
		if (q == QUERY) {
			int from, to;
			std::cin >> from >> to;
			from--; to--;
			std::cout << lazysegtree.query(from, to) << '\n';
		}
	}

	return 0;
}