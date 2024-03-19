#include <iostream>
#include <vector>
#include <iomanip>

#define UPDATE 1
#define QUERY 2

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
			tree[curr] = tree[curr * 2] + tree[curr * 2 + 1];
		}
	}

	T query(int from, int to, int curr, int left, int right) {
		if (right < from or to < left) return 0;
		if (from <= left and right <= to) return tree[curr];

		int mid = (left + right) >> 1;
		return query(from, to, curr * 2, left, mid)
			+ query(from, to, curr * 2 + 1, mid + 1, right);
	}

	void update(int idx, T diff, int curr, int left, int right) {
		if (idx < left or right < idx) return;
		if (left == right) {
			tree[curr] += diff;
		}
		else {
			int mid = (left + right) >> 1;
			update(idx, diff, curr * 2, left, mid);
			update(idx, diff, curr * 2 + 1, mid + 1, right);
			tree[curr] = tree[curr * 2] + tree[curr * 2 + 1];
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

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);

	int N, M, K;
	std::cin >> N >> M >> K;

	std::vector<long long> arr(N);
	for (auto& x : arr) std::cin >> x;

	SegTree<long long> segtree(arr);
	
	for (int i = 0; i < M + K; i++) {
		int q;
		std::cin >> q;

		if (q == UPDATE) {
			int idx;
			long long b;
			std::cin >> idx >> b;
			idx--;
			segtree.update(idx, b - arr[idx]);
			arr[idx] = b;
		}
		if (q == QUERY) {
			int from, to;
			std::cin >> from >> to;
			from--; to--;
			std::cout << segtree.query(from, to) << '\n';
		}
	}
	return 0;
}