
#include "catch.hpp"

TEST_CASE("testing for DataRepresentation", "") {
	SECTION("408����") {
		unsigned int usi = 0xFFFFFFFF;
		int si = usi;
		CHECK(usi == 65536 * 65536 - 1);
		CHECK(si == -1);
	}

	SECTION("�������������") {
		int si = 0;
		
		unsigned int usi_0 = 0x00000000;//0b0000...
		si = usi_0;
		CHECK(si == 0);

		unsigned int usi_maxPositive = 0x7FFFFFFF;//...0b0111
		si = usi_maxPositive;
		CHECK(si == 2147483647);//2��31�η�-1

		unsigned int usi_minNagetive = 0x80000000;//0b1000...
		si = usi_minNagetive;
		CHECK(si == -2147483648);//-2��31�η�

		unsigned int usi_minus1 = 0xFFFFFFFF;//...0b1111
		si = usi_minus1;
		CHECK(si == -1);
	}
}