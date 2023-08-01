
#include "catch.hpp"
#include <iostream>

TEST_CASE("testing for DataRepresentation", "") {
	SECTION("408真题") {
		unsigned int usi = 0xFFFFFFFF;
		int si = usi;
		CHECK(usi == 65536 * 65536 - 1);
		CHECK(si == -1);
	}

	SECTION("补码的增长规律") {
		int si = 0;
		
		unsigned int usi_0 = 0x00000000;//0b0000...
		si = usi_0;
		CHECK(si == 0);

		unsigned int usi_maxPositive = 0x7FFFFFFF;//...0b0111
		si = usi_maxPositive;
		CHECK(si == 2147483647);//2的31次方-1

		unsigned int usi_minNagetive = 0x80000000;//0b1000...
		si = usi_minNagetive;
		CHECK(si == -2147483648);//-2的31次方

		unsigned int usi_minus1 = 0xFFFFFFFF;//...0b1111
		si = usi_minus1;
		CHECK(si == -1);
	}

	SECTION("int被赋予超出范围的值") {
		std::cout << "***int被赋予超出范围的值：***" << std::endl; 
		int si = 0 + 0xffffffff;//超出范围 成了最大负数
		CHECK(si == 0 + (0xffffffff - 0x100000000));

		//cyclic
		si = 0x80000000;//范围内 最小负数
		std::cout << si << std::endl;
		--si;//超出范围 成了最大正数
		std::cout << si << std::endl;

		si = 0x7fffffff;//范围内 最大正数
		std::cout << si << std::endl;
		++si;//超出范围 成了最小负数
		std::cout << si << std::endl;
		std::cout << "***int被赋予超出范围的值：***" << std::endl;
	}
}