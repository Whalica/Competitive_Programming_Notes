// Code by Whalica
#include <bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;

using i128 = __int128;

using Point = std::array<i64, 2>;
using Vector = std::array<i64, 2>;

Point operator+(Point A, Point B) {
	return { A[0] + B[0], A[1] + B[1] };
}

Point operator-(Point A, Point B) {
	B[0] = -B[0], B[1] = -B[1];
	return A + B;
}

i128 cross(Vector A, Vector B) {
	return (i128)A[0] * B[1] - (i128)A[1] * B[0];
}

i128 normSqaure(Vector A) {
	return (i128)A[0] * A[0] + (i128)A[1] * A[1];
}

void solve() {
	int n;
	std::cin >> n;

	Point O;
	i64 r;
	std::cin >> O[0] >> O[1] >> r;

	std::vector<Point> p(n);
	for (int i = 0; i < n; i++) {
		std::cin >> p[i][0] >> p[i][1];
	}

	int j = 1;
	i64 ans = 0, res = 0;
	for (int i = 0; i < n; i++) {
		if (i > 0) {
			res -= cross(p[j] - p[i - 1], p[j] - p[i]);
		}
		Vector v(O - p[i]);
		while ((j + 1) % n != i &&
			   cross(p[(j + 1) % n] - p[i], v) > 0 &&
			   cross(p[(j + 1) % n] - p[i], v) * cross(p[(j + 1) % n] - p[i], v) >= normSqaure(p[(j + 1) % n] - p[i]) * r * r) {
			res += cross(p[j] - p[i], p[(j + 1) % n] - p[i]);
			j = (j + 1) % n;
		}
		ans = std::max(ans, res);
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
