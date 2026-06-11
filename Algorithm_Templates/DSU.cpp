
class DSU { // 0 - index
public:
	std::vector<int> fa, siz;

	DSU(int n) : fa(n), siz(n, 1) {
		std::iota(fa.begin(), fa.end(), 0);
	}

	int find(int x) {
		if (fa[x] != x) {
			fa[x] = find(fa[x]);
		}
		return fa[x];
	}

	void merge(int x, int y) {
		x = find(x), y = find(y);
		if (x == y) {
			return;
		}
		if (siz[x] > siz[y]) {
			std::swap(x, y);
		}
		fa[x] = y;
		siz[y] += siz[x];
	}

	bool same(int x, int y) {
		return (find(x) == find(y));
	}
};
