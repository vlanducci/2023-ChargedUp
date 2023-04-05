// #include "klein/klein.hpp"

#ifndef _IMMINTRIN_H_INCLUDED
#define _IMMINTRIN_H_INCLUDED
#ifdef __MMX__
#include <mmintrin.h>
#define TEST_THING "test"
#endif
#ifdef __SSE__
#include <xmmintrin.h>
#define TEST_THING "test"
#endif
#ifdef __SSE2__
#include <emmintrin.h>
#define TEST_THING "test"
#endif
#ifdef __SSE3__
#include <pmmintrin.h>
#define TEST_THING "test"
#endif
#ifdef __SSSE3__
#include <tmmintrin.h>
#define TEST_THING "test"
#endif
#if defined (__SSE4_2__) || defined (__SSE4_1__)
#include <smmintrin.h>
#define TEST_THING "test"
#endif
#if defined (__AES__) || defined (__PCLMUL__)
#include <wmmintrin.h>
#define TEST_THING "test"
#endif
#ifdef __AVX__
#include <avxintrin.h>
#define TEST_THING "test"
#endif
#endif /* _IMMINTRIN_H_INCLUDED */

#include <iostream>

int main() {
  // point pElevator{1, 0, 0};
  // point pArm{1, 0, 0};

  // translator t{1.f, 0.f, 1.f, 1.f};
  // rotor r{M_PI * 0.5f, 0.f, 0.f, 1.f};
  // motor m = r * t;

  // #ifdef TEST_THING
  // #endif
  std::cout << "Test running" << std::endl;
  return;
}