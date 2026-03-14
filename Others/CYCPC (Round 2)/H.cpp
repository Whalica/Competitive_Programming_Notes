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
 
i64 inv(i64 a) {
    assert(a != 0);
    return power(a, P - 2);
}

constexpr int N = 1E5;

std::vector<int> primes, is_prime(N + 1, 1);
	
void sieve() {
	is_prime[0] = is_prime[1] = 0;
	
	for (int i = 2; i <= N; i++) {
		if (is_prime[i]) {
			primes.push_back(i);
		}
		for (auto x : primes) {
			if (1LL * i * x > N) {
				break;
			}
			is_prime[i * x] = false;
			if (i % x == 0) {
				break;
			}
		}
	}
}

void solve() {
	i64 n, m;
	std::cin >> n >> m;

	int d = 0;
	for (int i = 1; i * i <= n; i++) {
		if (n % i == 0) {
			d++;
			if (i * i != n) {
				d++;
			}
		}
	}

	std::vector<int> exp;
	for (auto p : primes) {
		int cnt = 0;
		while (n % p == 0) {
			cnt++;
			n /= p;
		}
		if (cnt != 0) {
			exp.push_back(cnt);
		}
	}
	if (n != 1) { // 如果 n 是 > 1E5 的质数
		exp.push_back(1);
	}

	i64 ans = power(d, 2 * m), res = 1;
	for (auto e : exp) {
		std::vector<std::vector<i64>> dp(2 * m + 1, std::vector<i64>(m * e + 1));
		dp[0][0] = 1;
		for (int i = 1; i <= 2 * m; i++) {
			for (int j = 0; j <= m * e; j++) {
				for (int k = 0; k <= std::min(e, j); k++) { // j - k >= 0, k <= j
					dp[i][j] = (dp[i][j] + dp[i - 1][j - k]) % P;
				}
			}
		}
		res = res * dp[2 * m][m * e] % P;
	}

	std::cout << (ans + res) % P * inv(2) % P << "\n";
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	sieve();

	int t = 1;
	// std::cin >> t;

	while (t--) {
		solve();
	}

	return 0;
}
