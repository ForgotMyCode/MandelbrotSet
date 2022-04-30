#pragma once

template<typename T>
struct Complex {
	T Real;
	T Imaginary;

	inline
	static Complex Zero() {
		return Complex(T(0), T(0));
	}

	inline
	Complex(T real = T(0), T imaginary = T(0))
		:
		Real(real),
		Imaginary(imaginary)
	{}

	inline
	Complex& Square() {
		const T newReal = (this->Real * this->Real) - (this->Imaginary * this->Imaginary);
		const T newImaginary = (this->Real * this->Imaginary) * T(2);

		this->Real = newReal;
		this->Imaginary = newImaginary;

		return *this;
	}

	inline
	Complex& Add(Complex const& other) {
		this->Real += other.Real;
		this->Imaginary += other.Imaginary;

		return *this;
	}

	inline
	T SquaredSize() const {
		return (this->Real * this->Real) + (this->Imaginary * this->Imaginary);
	}
};