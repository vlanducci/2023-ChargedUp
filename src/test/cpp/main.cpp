#include <hal/HAL.h>

#include "gtest/gtest.h"

#include <iostream>

int main(int argc, char** argv) {
  std::cout << "Test from other" << std::endl;
  HAL_Initialize(500, 0);
  ::testing::InitGoogleTest(&argc, argv);
  int ret = RUN_ALL_TESTS();
  return ret;
}
