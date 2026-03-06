// Code by Whalica
#include <bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;

constexpr i64 P = 998244353;

i64 power(i64 a, i64 b) {
    a %= P;
    i64 res = 1;
    for (; b; a = a * a % P, b >>= 1) {
        if (b & 1) {
            res = res * a % P;
        }
    }
    return res;
}

void solve() {
	i64 n, m;
	std::cin >> n >> m;

	std::vector<std::pair<i64, i64>> a(n);
	for (auto& [x, y] : a) {
		std::cin >> y >> x;
	}

	std::sort(a.begin(), a.end(), std::greater<std::pair<i64, i64>>());

	i64 rem = 0, lst = 0, ans = 0;
	for (auto& [y, x] : a) {
		if (rem) {
			if (std::bit_width((u64)rem) + lst - y >= 60) {
				break;
			}
			rem *= (1LL << (lst - y));
		}
		lst = y;
		if (x < rem) {
			rem -= x;
		} else {
			x -= rem;
			i64 cnt = (x + m - 1) / m % P;
			ans = (ans + cnt * power(2, y) % P) % P;
			rem = (m - x % m) % m;
		}
	}

	std::cout << ans << "\n";
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
