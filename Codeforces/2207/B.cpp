// Code by Whalica
#include <bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;

using i128 = __int128;

void solve() {
	int n, m, l;
	std::cin >> n >> m >> l;

	std::vector<int> a(n);
	for (int i = 0; i < n; i++) {
		std::cin >> a[i];
	}

	std::vector<int> f(m);
	int p = 0;
	for (int i = 0; i < l; i++) {
		f[std::min(m, n - p + 1) - 1]++;
		std::sort(f.begin(), f.end(), std::greater<int>());
		if (p < n && a[p] - 1 == i) {
			f[0] = 0;
			std::sort(f.begin(), f.end(), std::greater<int>());
			p++;
		}
	}

	std::cout << f[0] << "\n";
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int t = 1;
	std::cin >> t;

	while (t--) {
		solve();
	}

	return 0;
}
