#include "bitcounter.h"

int count_bits(BitboardCA::Bitboard n) {
  n = ((n >> 1) & 0x5555555555555555ULL) + (n & 0x5555555555555555ULL);
  n = ((n >> 2) & 0x3333333333333333ULL) + (n & 0x3333333333333333ULL);
  n = ((n >> 4) & 0x0f0f0f0f0f0f0f0fULL) + (n & 0x0f0f0f0f0f0f0f0fULL);
  n = ((n >> 8) & 0x00ff00ff00ff00ffULL) + (n & 0x00ff00ff00ff00ffULL);
  n = ((n >> 16) & 0x0000ffff0000ffffULL) + (n & 0x0000ffff0000ffffULL);
  n = (n >> 32) + (n & 0x00000000ffffffffULL);
  return (int)n;
}
