#include "BigNum.h"
#include <iostream>


BigNum::BigNum() {
	this->sign = false;
}

BigNum::BigNum(const BigNum& num) {
	this->sign = num.sign;
	this->arr_of_digits = num.arr_of_digits;
}

BigNum::BigNum(const char str[]) {
	BigNum temp;
	temp = str;

	this->sign = temp.Sign();
	this->arr_of_digits = temp.arr_of_digits;

	this->remove_leading_zeroes();
}

BigNum::BigNum(std::string& str) {
	BigNum temp;
	temp = str;

	this->sign = temp.Sign();
	this->arr_of_digits = temp.arr_of_digits;

	this->remove_leading_zeroes();
}

const int32_t BigNum::Size() const {
	return arr_of_digits.size();
}

const bool BigNum::Sign() const {
	return this->sign;
}

void BigNum::set_sign(bool sign) {
	this->sign = sign;
}

const char BigNum::get_digit(int32_t pos) const {
	return arr_of_digits[pos];
}

const char BigNum::get_high_order_digit() const {
	return *(arr_of_digits.end() - 1);
}

const int32_t BigNum::remove_leading_zeroes() {
	int32_t count = 0;

	while (this->Size() > 1 && this->get_high_order_digit() == 0) {
		arr_of_digits.pop_back();
		++count;
	}

	return count;
}

const std::vector < char >& BigNum::get_arr_of_digits() const {
	return this->arr_of_digits;
}

std::vector < char >& BigNum::modify_arr_of_digits() {
	return arr_of_digits;
}

BigNum& BigNum::operator=(const std::string& right) {
	arr_of_digits.clear();

	std::string Right;

	if (right[0] == '-') {
		Right = right.substr(1, right.size()-1);
		this->sign = true;
	} else {
		Right = right;
		this->sign = false;
	}

	int32_t i;
	for (i = (int32_t)right.size() - 2; i >= 0; i -= 2) {
		arr_of_digits.push_back((right[i] - 48) * 10 + right[i + 1] - 48);
	}

	if (i == -1) {
		arr_of_digits.push_back(right[0] - 48);
	}

	this->remove_leading_zeroes();

	return *this;
}

BigNum& BigNum::operator=(std::string& right) {
	arr_of_digits.clear();

	std::string Right;

	if (right[0] == '-') {
		Right = right.substr(1, right.size() - 1);
		this->sign = true;
	}
	else {
		Right = right;
		this->sign = false;
	}

	int32_t i;
	for (i = (int32_t)Right.size() - 2; i >= 0; i -= 2) {
		arr_of_digits.push_back((Right[i] - 48) * 10 + Right[i + 1] - 48);
	}

	if (i == -1) {
		arr_of_digits.push_back(Right[0] - 48);
	}

	this->remove_leading_zeroes();

	return *this;
}

BigNum& BigNum::operator=(const char right[]) {
	arr_of_digits.clear();

	std::string str = right;


	if (right[0] == '-') {
		str = str.substr(1, str.size() - 1);
		this->sign = true;
	} else {
		this->sign = false;
	}

	int32_t i;
	for (i = (int32_t)str.size() - 2; i >= 0; i -= 2) {
		arr_of_digits.push_back((str[i] - 48) * 10 + str[i + 1] - 48);
	}

	if (i == -1) {
		arr_of_digits.push_back(str[0] - 48);
	}

	this->remove_leading_zeroes();

	return *this;
}

// Унарный минус
BigNum BigNum::operator-() const {
	BigNum res = *this;
	res.set_sign(!(this->sign));

	return res;
}

// Вывод в консоль
std::ostream& operator<<(std::ostream& out, const BigNum& right) {
	if (right.Sign()) {
		out << '-';
	}

	out << (int16_t)right.get_high_order_digit();

	int32_t i;
	int32_t size = right.Size();
	for (i = size - 2; i >= 0; --i) {
		if (right.get_digit(i) < 10) {
			out << '0' << (int16_t)right.get_digit(i);
		} else {
			out << (int16_t)right.get_digit(i);
		}
	}

	return out;
}

bool operator<(const BigNum& left, const BigNum& right) {
	if (left.Sign() > right.Sign()) {
		return true;

	}
	else if (left.Sign() < right.Sign()) {
		return false;

	}
	else if (left.Sign() && left.Size() > right.Size()) {
		return true;

	}
	else if (left.Sign() && left.Size() < right.Size()) {
		return false;

	}
	else if (!left.Sign() && left.Size() > right.Size()) {
		return false;

	}
	else if (!left.Sign() && left.Size() < right.Size()) {
		return true;

	}
	else {
		for (int32_t i = left.Size() - 1; i >= 0; --i) {
			if (left.get_digit(i) < right.get_digit(i)) {
				return true;

			}
			else if (left.get_digit(i) > right.get_digit(i)) {
				return false;
			}
		}

		return false;
	}
}

BigNum operator+(const BigNum& left, const BigNum& right) {
	if ( left.Sign() == right.Sign() ) {
		BigNum res;

		char tmp = 0;
		char sum = 0;
		int32_t i;
		int32_t sum_to = std::min(left.Size(), right.Size());
		for (i = 0; i < sum_to; ++i) {
			sum = (left.get_digit(i) + right.get_digit(i)) % 100 + tmp;
			tmp = (left.get_digit(i) + right.get_digit(i)) / 100;

			res.modify_arr_of_digits().push_back(sum);
		}

		if (left.Size() == right.Size()) {
			if (tmp != 0) {
				res.modify_arr_of_digits().push_back(tmp);
			}

			if (left.Sign()) {
				res.set_sign(true);
			}

			return res;
		}

		sum_to = std::max(left.Size(), right.Size());

		if (sum_to == left.Size()) {
			sum = left.get_digit(i) % 100 + tmp;
			tmp = left.get_digit(i) / 100;

			res.modify_arr_of_digits().push_back(sum);

			for (++i; i < sum_to; ++i) {
				sum = left.get_digit(i);
				res.modify_arr_of_digits().push_back(sum);
			}
		}
		else {
			sum = right.get_digit(i) % 100 + tmp;
			tmp = right.get_digit(i) / 100;

			res.modify_arr_of_digits().push_back(sum);

			for (++i; i < sum_to; ++i) {
				sum = right.get_digit(i);
				res.modify_arr_of_digits().push_back(sum);
			}
		}

		if (left.Sign()) {
			res.set_sign(true);
		}

		return res;
	}

	if (left.Sign()) {
		return right - (-left);
	}

	return left - (-right);
}

BigNum operator+(const BigNum& left, std::string& right) {
	BigNum Right;
	Right = right;

	return left + Right;
}

BigNum operator+(std::string& left, const BigNum& right) {
	BigNum Left;
	Left = left;

	return Left + right;
}

BigNum operator-(const BigNum& left, const BigNum& right) {
	if (left.Sign() != right.Sign()) {
		return left + (-right);
	}

	if (left.Sign()) {
		return (-right) - (-left);
	}

	if (left < right) {
		return -(right - left);
	}

	BigNum res;

	char tmp = 0;
	char diff = 0;
	int32_t i;
	int32_t diff_to = right.Size();
	for (i = 0; i < diff_to; ++i) {
		if (left.get_digit(i) - tmp < right.get_digit(i)) {
			diff = (left.get_digit(i) + 100 - right.get_digit(i)) - tmp;
			tmp = 1;
		
		} else {
			diff = (left.get_digit(i) - right.get_digit(i)) - tmp;
			tmp = 0;
		}
		
		res.modify_arr_of_digits().push_back(diff);
	}

	diff_to = left.Size();

	if (diff_to != right.Size()) {
		diff = left.get_digit(i) - tmp;
		res.modify_arr_of_digits().push_back(diff);

	}

	for (++i; i < diff_to; ++i) {
		diff = left.get_digit(i);
		res.modify_arr_of_digits().push_back(diff);
	}

	res.remove_leading_zeroes();

	return res;
}

// Умножение на 10 в степени right (сдвиг влево на n в десятичной системе счисления)
// return -> left * 10^right
BigNum operator<<(const BigNum& left, const int32_t& right) {
	BigNum res;

	res.set_sign(left.Sign());

	for (int32_t i = 0; i < right / 2; ++i) {
		res.modify_arr_of_digits().push_back('0' - 48);
	}

	if (right & 1) {
		int32_t i = 0;
		res.modify_arr_of_digits().push_back((left.get_digit(0) % 10) * 10);
		++i;

		for (i = 1; i < left.Size(); ++i) {
			res.modify_arr_of_digits().push_back((left.get_digit(i - 1) / 10) + left.get_digit(i) % 10 * 10);
		}

		if (left.get_high_order_digit() >= 10) {
			res.modify_arr_of_digits().push_back(left.get_digit(i - 1) / 10);
		}

		return res;
	}

	for (int32_t i = 0; i < left.Size(); ++i) {
		res.modify_arr_of_digits().push_back(left.get_digit(i));
	}

	return res;
}

// Умножение Карацубы
BigNum operator*(const BigNum& left, const BigNum& right) {
	BigNum res;

	if ((left.Size() == 1) && (left.get_digit(0) == 0) || (right.Size() == 1) && (right.get_digit(0) == 0)) {
		res = "0";

		return res;
	}

	
	bool sign = (left.Sign() && !right.Sign()) || (!left.Sign() && right.Sign());

	
	if (left.Size() == 1 && left.get_digit(0) == 1) {
		res = right;

		res.set_sign(sign);
		
		return res;
	}

	if (right.Size() == 1 && right.get_digit(0) == 1) {
		res = left;

		res.set_sign(sign);

		return res;
	}

	if (left.Size() > right.Size()) {
		int32_t len_sup = left.Size() - right.Size();
		
		BigNum left_len_eq;
		for (int32_t i = 0; i < right.Size(); ++i) {
			left_len_eq.modify_arr_of_digits().push_back(left.get_digit(i));
		}

		BigNum  left_len_sup;
		for (int32_t i = 0; i < right.Size() - len_sup; ++i) {
			left_len_sup.modify_arr_of_digits().push_back(0);
		}
		for (int32_t i = left.Size() - len_sup; i < left.Size(); ++i) {
			left_len_sup.modify_arr_of_digits().push_back(left.get_digit(i));
		}

		res = right * left_len_eq + ((right * left_len_sup) << (len_sup * 2));
		
		res.set_sign(sign);

		return res;
	}

	if (left.Size() < right.Size()) {
		res = right * left;

		res.set_sign(sign);

		return res;
	}

	if (left.Size() == 1 && right.Size() == 1) {
		res = std::to_string((int16_t)left.get_digit(0) * (int16_t)right.get_digit(0));

		res.set_sign(sign);

		return res;
	}

	BigNum left_first;
	for (int32_t i = 0; i < left.Size() / 2; ++i) {
		left_first.modify_arr_of_digits().push_back(left.get_digit(i));
	}

	BigNum left_second;
	for (int32_t i = left.Size() / 2; i < left.Size(); ++i) {
		left_second.modify_arr_of_digits().push_back(left.get_digit(i));
	}

	BigNum right_first;
	for (int32_t i = 0; i < right.Size() / 2; ++i) {
		right_first.modify_arr_of_digits().push_back(right.get_digit(i));
	}

	BigNum right_second;
	for (int32_t i = right.Size() / 2; i < right.Size(); ++i) {
		right_second.modify_arr_of_digits().push_back(right.get_digit(i));
	}

	BigNum first;
	first = (left_first * right_first);

	BigNum second;
	second = (left_second * right_second);

	res = (second << (left.Size() * 2)) + (((left_first + left_second) * (right_first + right_second) - first - second) << left.Size()) + first;

	res.set_sign(sign);

	res.remove_leading_zeroes();

	return res;
}
