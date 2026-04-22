## [Educational Codeforces Round 189 (Rated for Div. 2)](https://codeforces.com/contest/2225)

[TOC]

### [A. A Number Between Two Others](https://codeforces.com/contest/2225/problem/A)

#### 简要题意

> 给定整数 $x, y$ 满足 $1\le x < y\le 10^{18}$ 且 $y\equiv0\pmod{x}$，构造一个整数 $z$，使其满足：
>
> - $x < z < y$
> - $z\equiv0\pmod{x}$
> - $y\not\equiv 0\pmod{z}$

#### 解题思路

由题意，$x, y, z$ 都是 $x$ 的倍数，不妨将这三个数都除以 $x$，题目变为：

> 给定整数 $a, b$ 满足 $1= a < b\le 10^{18}$，构造一个整数 $c$，使其满足：
>
> - $a < c < b$
> - $b\not\equiv 0\pmod{c}$

也就是说，我们需要在 $a, b$ 之间（不包含 $a, b$）找到一个整数 $c$，使其不是 $b$ 的因数，其中 $a = 1$ 。

我们先考虑 $c$ 的取值范围，由题意 $a < c < b$，那么 $a + 1 \le c\le b - 1$，也就是 $2\le c\le b - 1$。

那么首先要满足 $b - 1 \ge 2$，也就是 $b\ge 3$ 。

其次，对于 $c = b - 1$，我们有定理：

> 对于任意正整数 $n$，$n$ 与 $n+1$ 的最大公约数为 $1$，即 $\gcd⁡(n, n+1)=1$ 。

 也就是说，任意相邻正整数都是互质的。

而 $c = b - 1$ 和 $b$ 刚好满足相邻正整数这一要求，所以 $b, c$ 互质，而互质了显然也不会成倍数关系，所以该构造是合法的。

所以，只要满足 $\frac{y}{x} \ge 3$，我们总是能找到这样的整数 $z$ 。

#### 参考代码（C++）

```cpp
void solve() {
	i64 x, y;
	std::cin >> x >> y;

	if (y / x >= 3) {
		std::cout << "YES\n";
	} else {
		std::cout << "NO\n";
	}
}
```



### [B. Alternating String](https://codeforces.com/contest/2225/problem/B)

#### 简要题意

> 我们定义一个字符串 $t$ 是交替串，当且仅当 $t$ 的所有相邻的字符均不同。
>
> 给定一个仅可能包含字符 $\texttt{a, b}$ 字符串 $s$ $(2\le |s|\le 2\times 10^5)$，你可以按顺序进行如下的操作至多一次：
>
> 1. 选择 $s$ 的一个子串 $str$
> 2. 可选地，将 $str$ 的所有 $\texttt{a}$ 替换为 $\texttt{b}$，且将 $str$ 的所有 $\texttt{b}$ 替换为 $\texttt{a}$
> 3. 反转子串 $str$
>
> 你需要判断是否能够通过至多一次操作使得 $s$ 成为交替串。

#### 解题思路

~~说来惭愧，本人赛时写的是模拟做法，根本没发现真正的性质~~

我们不妨考虑操作会对字符串带来什么影响。

不论是将子串所有字符进行替换，还是将子串进行反转，子串内部的情况是不会变的，如果原来是相邻相同，操作完还会是相邻相同，相邻不同同理。

也就是说，一次操作至多能改变两对相邻字符的相同情况。那么，如果相邻相同的字符对数超过了 $2$，我们就一定无法将 $s$ 变为交替串。

否则相邻相同的字符对数小于等于 $2$，我们不妨分类讨论一下，记相邻字符相等的对数为 $cnt$：

如果 $cnt = 0$，那么说明字符串 $s$ 已经是交替串，我们不需要进行任何操作。

如果 $cnt = 1$，那么说明只有一对相邻相同的字符对，举个例子：

考虑第一组样例的字符串 $\texttt{abbaba}$，我们可以选择从相邻相同的字符对中间切开，变为 $\color{red}\texttt{ab}\color{blue}{\texttt{baba}}$，我们不妨选择其中一边进行操作，如果子串长度为偶数，那么直接反转就是对的；如果长度为奇数（例如字符串 $\color{red}\texttt{aba}\color{blue}\texttt{abab}$），我们多进行一次替换也能得到交替串（此时反转子串是无效操作）。

如果 $cnt = 2$，说明有两对相邻相同的字符对，我们宽泛地考虑一下：

同样从相邻相同的字符对中间切开，字符串可以切分为 $\color{red}\texttt{xxx}\color{blue}\texttt{yyy}\color{red}\texttt{zzz}$，类似地，当 $\color{blue}\texttt{yyy}$ 的长度为偶数时，直接进行交换即可；当 $\color{blue}\texttt{yyy}$ 的长度为奇数时，此时反转是无效的，多进行一次替换即可。

综上所述，字符串 $s$ 能通过至多一次操作变为交替串的充要条件就是 $cnt \le 2$ 。

#### 参考代码（C++）

```cpp
void solve() {
	std::string s;
	std::cin >> s;
	
	int cnt = 0;
	for (int i = 1; i < s.length(); i++) {
		cnt += (s[i] == s[i - 1]);
	}

	if (cnt <= 2) {
		std::cout << "YES\n";
	} else {
		std::cout << "NO\n";
	}
}
```



### [C. Red-Black Pairs](https://codeforces.com/contest/2225/problem/C)

#### 简要题意

> 给定一个 $2\times n$ $(1\le n\le 2\times 10^5)$ 的网格图，每个格子标有 $\texttt{R, B}$ 的其中一种，定义一次操作为，选择一个任意的格子，将其设为 $\texttt{R,B}$ 的任意一种，你需要求最小的操作次数，使得这个网格图能被划分为 $n$ 个格子对，且对于每个格子对满足：
>
> - 两个格子的标记相同
> - 两个格子相邻

#### 解题思路

~~我也不知道为什么 dp，但是赛时第一眼想到的就是 dp，而且这个做法确实比较对，比难以证明的贪心正确~~

考虑 $dp$，设 $dp_{i, j}$ 表示考虑到第 $i$ 列以状态 $j$ 结尾的最小操作次数，设 $s_{1, i}, s_{2, i}$ 分别表示第 $1$ 行第 $i$ 列的字符和第 $2$ 行第 $i$ 列的字符，设 $\mathtt{*}$ 表示任意字符 $(\mathtt{*\in\{R, B\}})$，其中：

- 若 $j = 0$，表示以 $s_{1, i} = \texttt{R}, s_{2, i} = \texttt{R}$ 结尾的状态

$$
\mathtt{*\space R}\\\mathtt{*\space R}
$$

- 若 $j = 1$，表示以 $s_{1, i} = \texttt{R}, s_{2, i} = \texttt{B}$ 结尾的状态

$$
\mathtt{*\space R\space R}\\\mathtt{*\space B\space B}
$$

- 若 $j = 2$，表示以 $s_{1, i} = \texttt{B}, s_{2, i} = \texttt{R}$ 结尾的状态

$$
\mathtt{*\space B\space B}\\\mathtt{*\space R\space R}
$$

- 若 $j = 3$，表示以 $s_{1, i} = \texttt{B}, s_{2, i} = \texttt{B}$ 结尾的状态

$$
\mathtt{*\space B}\\\mathtt{*\space B}
$$

那么有转移：

- 若 $j = 0$ 或 $j = 3$，第 $i$ 列成一对，状态从第 $i - 1$ 列的最小值转移而来（这里要特判 $i = 1$ 时的情况，下面会说到）。

  此时有转移方程：
  $$
  dp_{i, 0} = \min_{j = 0, 1, 2, 3}dp_{i - 1, j} + [s_{1, i} \neq \texttt{R}] + [s_{2, i}\neq\texttt{R}]
  $$

  $$
  dp_{i, 3} = \min_{j = 0, 1, 2, 3}dp_{i - 1, j} + [s_{1, i} \neq \texttt{B}] + [s_{2, i}\neq\texttt{B}]
  $$

- 若 $j = 1$ 或 $j = 2$，只能是第 $i$ 列和第 $i - 1$ 列的同行字符成一对，状态从第 $i - 2$ 列的最小值转移而来。

	此时有转移方程：
	$$
	dp_{i, 1} = \min_{j = 0, 1, 2, 3}dp_{i - 2, j} + [s_{1, i} \neq \texttt{R}] + [s_{2, i}\neq\texttt{B}] + [s_{1, i - 1} \neq \texttt{R}] + [s_{2, i - 1}\neq\texttt{B}]
	$$

	$$
	dp_{i, 2} = \min_{j = 0, 1, 2, 3}dp_{i - 2, j} + [s_{1, i} \neq \texttt{B}] + [s_{2, i}\neq\texttt{R}] + [s_{1, i - 1} \neq \texttt{B}] + [s_{2, i - 1}\neq\texttt{R}]
	$$

其中 $[\space]$ 是艾佛森括号。

这些转移方程看上去很复杂，但是其实道理很简单。

另外要注意 $i = 1$ 时 $dp$ 数组的初值。因为 $i = 1$ 时，若 $j = 1$ 或 $j = 2$，此时 $i - 1$ 列为空，不可能形成类似
$$
\texttt{RR}\qquad\texttt{BB}\\
\texttt{BB}\qquad\texttt{RR}
$$
这两种结构。所以 $dp_{1, 1}$ 和 $dp_{1, 2}$ 应设为 $\infty$ ，最终的答案是 $\displaystyle\min_{j = 0, 1, 2, 3}dp_{n, j}$ 。

#### 参考代码（C++）

```cpp
constexpr int inf = std::numeric_limits<int>::max();

void solve() {
	int n;
	std::cin >> n;

	std::array<std::string, 2 + 1> s;
	std::cin >> s[1] >> s[2];
	s[1] = " " + s[1];
	s[2] = " " + s[2];

	std::vector<std::array<int, 4>> dp(n + 1);
	dp[1][0] = (s[1][1] != 'R') + (s[2][1] != 'R');
	dp[1][1] = inf;
	dp[1][2] = inf;
	dp[1][3] = (s[1][1] != 'B') + (s[2][1] != 'B');
	for (int i = 2; i <= n; i++) {
		int min = inf, premin = inf;
		for (int j = 0; j < 4; j++) {
			min = std::min(min, dp[i - 1][j]);
			premin = std::min(premin, dp[i - 2][j]);
		}
		dp[i][0] = min + (s[1][i] != 'R') + (s[2][i] != 'R');
		dp[i][1] = premin + (s[1][i - 1] != 'R') + (s[2][i - 1] != 'B') + (s[1][i] != 'R') + (s[2][i] != 'B');
		dp[i][2] = premin + (s[1][i - 1] != 'B') + (s[2][i - 1] != 'R') + (s[1][i] != 'B') + (s[2][i] != 'R');
		dp[i][3] = min + (s[1][i] != 'B') + (s[2][i] != 'B');
	}

	int ans = inf;
	for (int i = 0; i < 4; i++) {
		ans = std::min(ans, dp[n][i]);
	}

	std::cout << ans << "\n";
}
```



### [D. Exceptional Segments](https://codeforces.com/contest/2225/problem/D)

#### 简要题意

> 给定两个整数 $n, x$ $(1\le x\le n\le 10^{18})$，你需要计算整数对 $(l, r)$ 的个数，使得：
>
> - $1\le l\le x\le r \le n$
> - $l\oplus l + 1 \oplus \cdots \oplus r = 0$
>
> 结果对 $998244353$ 取模。

#### 解题思路

整数连续区间 $\text{xor}$，不妨转化为整数前缀 $\text{xor}$ 的 $\text{xor}$ 差。为了方便表示，我们记 $\text{prexor}_x = 0\oplus1\oplus\cdots \oplus x$，那么有：
$$
l\oplus l + 1 \oplus \cdots \oplus r = \text{prexor}_r \oplus \text{prexor}_{l - 1} = 0
$$
也就是
$$
\text{prexor}_{r} = \text{prexor}_{l - 1}
$$
此时我们可以打表发现，或者根据做题经验，实际上，对于整数前缀 $\text{xor}$，有如下的结论：
$$
\text{prexor}_{x} = \begin{cases}
x, &x\equiv0\pmod{4}\\
1, &x\equiv1\pmod{4}\\
x + 1, &x\equiv2\pmod{4}\\
0, &x\equiv3\pmod{4}
\end{cases}
$$
要令 $\text{prexor}_{r} = \text{prexor}_{l - 1}$，我们不妨按余数等价类分类讨论一下：

- 若 $r\equiv0\pmod{4}$ 且 $l - 1\equiv0\pmod{4}$，那么我们需要 $r = l - 1$ 成立，而 $l \le  r$，也就是 $l - 1 < r$，等号左右不可能相等，所以该情况下无解。
- 若 $r\equiv1\pmod{4}$ 且 $l - 1\equiv1\pmod{4}$，此时左右的 $\text{prexor}$ 值都是 $1$，答案为区间 $[0, x - 1]$ 范围内模 $4$ 余 $1$ 的数的个数与区间 $[x, n]$ 范围内模 $4$ 余 $1$ 的数的个数的乘积。
- 若 $r\equiv2\pmod{4}$ 且 $l - 1\equiv2\pmod{4}$，那么我们需要 $r +1 = l$ 成立，同第一种情况，该情况下也是无解的。
- 若 $r\equiv3\pmod{4}$ 且 $l - 1\equiv3\pmod{4}$，此时左右的 $\text{prexor}$ 值都是 $0$，同第二种情况计算。
- 另外地，考虑左右等价类不同的情况，考虑到有 $l - 1 < r$ 恒成立，简单讨论，发现只有 $l - 1 =0$ 且 $r\equiv3\pmod{4}$ 时可能成立。我们只需要在计算最后一种情况的时候多加一份右边部分的数个数即可。

#### 参考代码（C++）

```cpp
void solve() {
	i64 n, x;
	std::cin >> n >> x;

	// 计算 1, 2, ..., n 有多少个数 x 满足 x % 4 = p
	// f : 0->不计0   1->计0
	auto cal = [](i64 x, i64 p, int f) -> i64 {
		if (f || p != 0) {
			x += 4;
		}
		return (x - p) / 4;
	};

	i64 ans = 0;
	for (int i = 0; i < 4; i++) {
		if (i == 0 || i == 2) {
			continue;
		}
		// 左边个数 x 右边个数
		i64 res = cal(x - 1, i, 1) % P * ((cal(n, i, 0) - cal(x - 1, i, 0)) % P) % P;
		
		ans = (ans + res) % P;
		// i = 3 多加一份右边的
		if (i == 3) {
			ans = (ans + (cal(n, i, 0) - cal(x - 1, i, 0)) % P) % P;
		}
	}

	std::cout << ans << "\n";
}
```

