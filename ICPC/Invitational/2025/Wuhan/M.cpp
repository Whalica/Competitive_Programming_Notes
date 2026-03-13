// Code by Whalica
#include <bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;

using i128 = __int128;

using F = long double;
using Point = std::array<F, 3>;

constexpr F eps = 1E-8;

F norm(Point X){
	return std::sqrtl(X[0] * X[0] + X[1] * X[1] + X[2] * X[2]);
}

F dot(Point X, Point Y){
	return X[0] * Y[0] + X[1] * Y[1] + X[2] * Y[2];
}

Point cross(Point X, Point Y) {
	return {X[1] * Y[2] - X[2] * Y[1], 
			X[2] * Y[0] - X[0] * Y[2], 
			X[0] * Y[1] - X[1] * Y[0]};
}

Point operator+(Point X, Point Y) {
	return {X[0] + Y[0], X[1] + Y[1], X[2] + Y[2]};
}

Point operator*(F lambda, Point P) {
	return {P[0] * lambda, P[1] * lambda, P[2] * lambda};
}

F angle(Point X, Point Y) {
	return atan2l(norm(cross(X, Y)), dot(X, Y));
}

void solve() {
	int R;
	std::cin >> R;

	auto trans = [&](int x, int y, int z) -> std::tuple<F, F, F> {
        Point Q = {1.0l * x, 1.0l * y, 1.0l * z};
		F len = norm(Q);
		return {R * x / len, R * y / len, R * z / len};
	};

	Point P, S, T;
	int x, y, z;
	std::cin >> x >> y >> z;
	std::tie(P[0], P[1], P[2]) = trans(x, y, z);
	std::cin >> x >> y >> z;
	std::tie(S[0], S[1], S[2]) = trans(x, y, z);
	std::cin >> x >> y >> z;
	std::tie(T[0], T[1], T[2]) = trans(x, y, z);

	auto check = [&](F lambda) -> F {
		Point Q = lambda * S + (1 - lambda) * T;
		return angle(P, Q) * R;
	};

	F l = 0.0l, r = 1.0l, res = 1.0l;
	int cnt = 100;
	while (cnt--) {
		F lmid = (2.0l * l + r) / 3.0l, rmid = (l + 2.0l * r) / 3.0l;
		if (check(lmid) + eps < check(rmid)) {
			res = lmid;
			r = rmid;
		} else {
			l = lmid;
		}
	}

	Point Q = res * S + (1.0l - res) * T;
	F ans = angle(P, Q);
	ans = std::min(ans, angle(P, S));
	ans = std::min(ans, angle(P, T));
	std::cout << std::setprecision(20) << ans * R << "\n";
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
