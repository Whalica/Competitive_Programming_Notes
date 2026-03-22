// Code by Whalica
#include <bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;

using i128 = __int128;

constexpr i64 INF = 4'000'000'000'000'000'000;
constexpr int N = 100;

void solve() {
	std::string x, y;
	std::cin >> x >> y;
	int n = x.size(), m = y.size();
	x = " " + x;
	y = " " + y;

	std::vector<i64> len(N + 1);
	len[1] = n;
	len[2] = m;
	for (int i = 3; i <= N; i++) {
		len[i] = std::min(INF, len[i - 1] + len[i - 2]);
	}

	std::vector<std::vector<int>> prex(n + 1, std::vector<int>(26)),
								  prey(m + 1, std::vector<int>(26));

	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < 26; j++) {
			prex[i][j] = prex[i - 1][j] + (x[i] - 'a' == j);
		}
	}
	for (int i = 1; i <= m; i++) {
		for (int j = 0; j < 26; j++) {
			prey[i][j] = prey[i - 1][j] + (y[i] - 'a' == j);
		}
	}

	std::vector<std::vector<i64>> pre(N + 1, std::vector<i64>(26));
	for (int i = 0; i < 26; i++) {
		pre[1][i] = prex[n][i];
		pre[2][i] = prey[m][i];
	}
	for (int i = 3; i <= N; i++) {
		for (int j = 0; j < 26; j++) {
			pre[i][j] = pre[i - 1][j] + pre[i - 2][j];
		}
	}

	int q;
	std::cin >> q;

	auto f = [&](auto&& self, int k, i64 p, char c) -> i64 {
		if (k == 1) {
			return prex[p][c - 'a'];
		}
		if (k == 2) {
			return prey[p][c - 'a'];
		}
		if (p <= len[k - 1]) {
			return self(self, k - 1, p, c);
		} else {
			return pre[k - 1][c - 'a'] + self(self, k - 2, p - len[k - 1], c);
		}
	};

	for (int i = 0; i < q; i++) {
		i64 l, r;
		char c;
		std::cin >> l >> r >> c;

		std::cout << f(f, N, r, c) - f(f, N, l - 1, c) << "\n";
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	
	int t = 1;
	// std::cin >> t;

	while (t--) {
		solve();
	}

	return 0;
}
