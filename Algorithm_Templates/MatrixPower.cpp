/**
 * 矩阵快速幂，矩阵类
 * 
 * Template by Whalica
 * 
 * 模板参数：
 * @param T : 矩阵数据类型，非基本数据类型需要提供默认值
 * @param Operator1 : 聚合运算，需要满足结合律，交换律，需要提供零元
 * @param Operator2 : 连接运算，需要满足结合律，需要提供单位元
 * 
 * 另外地：
 * 1. Operator2 需要对 Operator1 有分配律，即需要有
 * 		Operator2(a, Operator1(b, c)) = Operator1(Operator2(a, b), Operator2(a, c))
 * 		Operator2(Operator1(a, b), c) = Operator1(Operator2(a, c), Operator2(b, c))
 * 
 * 2. Operator1 的零元需要对 Operator2 有吸收性，即需要有
 * 		Operator2(a, zero) = Operator2(zero, a) = zero
 * 
 * 常见运算对：
 * 格式：< Operator1, Operator2, Operator1::zero(), Operator2::identity() >
 * 1. plus-times < +, *, 0, 1 >
 * 2. max/min-plus < max/min, +, -inf/+inf, 0 >
 * 3. max-min / min-max < max, min, -inf, +inf > / < min, max, +inf, -inf >
 * 4. or/xor-and < |/^, &, 0, ~0 >
 * 5. gcd-lcm < gcd, lcm, 0, 1 >
 */
template <typename T>
struct Op1;

template <typename T>
struct Op2;

template <typename T, class Operator1 = Op1<T>, class Operator2 = Op2<T>>
class Matrix {
private:
	int size_;
	std::vector<std::vector<T>> mat;

public:
	Matrix(int size, const T& val = Operator1::zero()) : size_(size), mat(size, std::vector<T>(size, val)) {}

	Matrix(const std::vector<std::vector<T>>& a) : size_(a.size()), mat(a) {}

    Matrix(const Matrix& m) = default;

	int size() const {
		return size_;
	}

	Matrix operator*(const Matrix& m) const {
		Matrix tmp(size_, Operator1::zero());
		Operator1 op1;
		Operator2 op2;
		for (int i = 0; i < size_; i++) {
			for (int k = 0; k < size_; k++) {
				for (int j = 0; j < size_; j++) {
					tmp(i, j) = op1(tmp(i, j), op2(mat[i][k], m(k, j)));
				}
			}
		}

		return tmp;
	}

	Matrix& operator*=(const Matrix& m) {
		(*this) = (*this) * m;
		return (*this);
	}

	T& operator()(int i, int j) {
		return mat[i][j];
	}

	const T& operator()(int i, int j) const {
		return mat[i][j];
	}

	// A^k
	Matrix power(i64 k) const {
		assert(k >= 0);
		Matrix res(size_, Operator1::zero());
		for (int i = 0; i < size_; i++) {
			res(i, i) = Operator2::identity();
		}

		Matrix m = (*this);

		for (; k; m *= m, k >>= 1) {
			if (k & 1) {
				res *= m;
			}
		}

		return res;
	}
};

// 运算结构体，默认运算对为 < +, * >，即一般矩阵乘法

template <typename T>
struct Op1 {
	// 运算 1 零元
	static T zero() {
		return T(0);
	}

	T operator()(const T& a, const T& b) const {
		return a + b;
	}
};

template <typename T>
struct Op2 {
	// 运算 2 单位元
	static T identity() {
		return T(1);
	}

	T operator()(const T& a, const T& b) const {
		return a * b;
	}
};
