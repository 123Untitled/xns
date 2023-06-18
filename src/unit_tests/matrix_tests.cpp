#include "unit_tests.hpp"
#include "matrix.hpp"


template <>
bool UT::unit_tests<"matrix">() {

	xns::matrix_3x3<float> m1 {
		1.0f, 2.0f, 3.0f,
		4.0f, 5.0f, 6.0f,
		7.0f, 8.0f, 9.0f
	};

	m1.print();

	xns::matrix_3x2<float> m2 {
		1.0f, 2.0f,
		3.0f, 4.0f,
		5.0f, 6.0f,
	};

	m2.print();


	auto m3 = xns::multiply_matrix(m1, m2);

	auto m8 = xns::add_matrix(m1, m1);

	m8.print();

	//m3.print();
	//auto m12 = m1 - m1;

	//m12.print();

	//auto m5 = xns::multiply_matrix(m1, m2);

	m3 = m1 + m1;

	//auto m3 = m1.multiply(m2);

	//xns::matrix_3x3<float> m4 = m1.multiply(2.0f);


	//m4.print();

	m1.scale(2.0f);
	m1.scale(2.0f);
	m1.print();

	/*
	m1 *= 2;

	m1.print();
	*/


	return true;
}