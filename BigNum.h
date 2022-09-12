#pragma once

#include <vector>
#include <string>


class BigNum {
private:
	bool sign;
	
	std::vector < char > arr_of_digits;

public:
	BigNum();

	BigNum(const BigNum& num);

	BigNum(const char right[]);

	BigNum(std::string& str);

	const int32_t Size() const;

	const bool Sign() const;

	void set_sign(bool sign);

	const char get_digit(int32_t pos) const;

	const char get_high_order_digit() const;

	const int32_t remove_leading_zeroes();

	const std::vector < char >& get_arr_of_digits() const;

	std::vector < char >& modify_arr_of_digits();

	BigNum& operator=(const std::string& right);

	BigNum& operator=(std::string &right);

	BigNum& operator=(const char right[]);

	// Унарный минус
	BigNum operator-() const;

	friend std::ostream& operator<<(std::ostream &out, const BigNum& number);
	
	friend bool operator<(const BigNum& left, const BigNum& right);

	friend BigNum operator+(const BigNum& left, const BigNum& right);

	friend BigNum operator+(const BigNum& left, std::string& right);

	friend BigNum operator+(std::string& left, const BigNum& right);

	friend BigNum operator-(const BigNum& left, const BigNum& right);

	// Умножение на 10 в степени right (сдвиг влево на n в десятичной системе счисления)
	// return -> left * 10^right
	friend BigNum operator<<(const BigNum& left, const int32_t& right);

	// Умножение Карацубы
	friend BigNum operator*(const BigNum& left, const BigNum& right);

	~BigNum() {
		
	}
};
