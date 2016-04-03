#include <iostream>
#include <string>

#include "gtest/gtest.h"
#include "hex_multiply.h"

using std::cout;
using std::endl;
using std::string;

TEST(hex_multiply_test, to_hex) {
  ASSERT_EQ(to_hex(9), '9');
  ASSERT_EQ(to_hex(10), 'a');
}

TEST(hex_multiply_test, get_int) {
  ASSERT_EQ(get_int('9'), 9);
  ASSERT_EQ(get_int('a'), 10);
}

TEST(hex_multiply_test, empty_element) {
  auto empty_str = string();
  ASSERT_EQ(hex_multipy("", ""), empty_str);
  ASSERT_EQ(hex_multipy("", "0x1234"), empty_str);
  ASSERT_EQ(hex_multipy("0x1234", ""), empty_str);
}

TEST(hex_multiply_test, error_element) {
  auto empty_str = string();
  ASSERT_EQ(hex_multipy("0x", ""), empty_str);
  ASSERT_EQ(hex_multipy("", "0X"), empty_str);
  ASSERT_EQ(hex_multipy("0x1234", "0x"), empty_str);
  ASSERT_EQ(hex_multipy("0x1234", "1234"), empty_str);
}

TEST(hex_multiply_test, multiply_number_only) {
  ASSERT_EQ(hex_multipy("0x9", "0x9"), string("0x51"));
  ASSERT_EQ(hex_multipy("0x12", "0x12"), string("0x144"));
  ASSERT_EQ(hex_multipy("0x23457892172189034", "0x1290834017057802347580"),
            string("0x28ecba3790a4394970b1a63620d45bf8bfde00"));
  ASSERT_EQ(hex_multipy("-0x23457892172189034", "0x1290834017057802347580"),
            string("-0x28ecba3790a4394970b1a63620d45bf8bfde00"));
  ASSERT_EQ(hex_multipy("0x23457892172189034", "-0x1290834017057802347580"),
            string("-0x28ecba3790a4394970b1a63620d45bf8bfde00"));
  ASSERT_EQ(hex_multipy("-0x23457892172189034", "-0x1290834017057802347580"),
            string("0x28ecba3790a4394970b1a63620d45bf8bfde00"));
  ASSERT_EQ(
      hex_multipy("0x9999999999999999999999999999999999",
                  "0x9999999999999999999999999999999999"),
      string("0x5c28f5c28f5c28f5c28f5c28f5c28f5c283d70a3d70a3d70a3d70a3d70a"
             "3d70a3d71"));
}

TEST(hex_multiply_test, multiply_mixed) {
  ASSERT_EQ(hex_multipy("0x9a", "0x9a"), string("0x5ca4"));
  ASSERT_EQ(
      hex_multipy(
          "0x5c28f5c28f5c28f5c28f5c28f5c28f5c283d70a3d70a3d70a3d70a3d70a",
          "0x5c28f5c28f5c28f5c28f5c28f5c28f5c283d70a3d70a3d70a3d70a3d70a"),
      string(
          "0x212d77318fc504816f0068db8bac710cb2113404ea4a8c154c985f06f69182a99"
          "30c6594af4f0d844d013a92a30558adab9f559b3d07c84b5dcc64"));
  ASSERT_EQ(
      hex_multipy(
          "-0x5c28f5c28f5c28f5c28f5c28f5c28f5c283d70a3d70a3d70a3d70a3d70a",
          "0x5c28f5c28f5c28f5c28f5c28f5c28f5c283d70a3d70a3d70a3d70a3d70a"),
      string(
          "-0x212d77318fc504816f0068db8bac710cb2113404ea4a8c154c985f06f69182a99"
          "30c6594af4f0d844d013a92a30558adab9f559b3d07c84b5dcc64"));
}
