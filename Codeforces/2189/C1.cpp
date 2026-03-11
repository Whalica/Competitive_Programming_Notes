// Code by Whalica
#include <bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;

using i128 = __int128;

void solve() {
	int n;
	std::cin >> n;

	std::vector<int> p(n + 1);
	std::iota(p.begin() + 1, p.end(), 1);   
	if (n & 1) {
		std::swap(p[1], p[n - 1]);
		for (int i = 2; i <= n - 3; i += 2) {
			std::swap(p[i], p[i + 1]);
		}
	} else {
		std::swap(p[1], p[n]);
		for (int i = 2; i <= n - 2; i += 2) {
			std::swap(p[i], p[i + 1]);
		}
	}

	for (int i = 1; i <= n; i++) {
		std::cout << p[i] << " \n"[i == n];
	}
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
