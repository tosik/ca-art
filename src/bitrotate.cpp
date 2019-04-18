#include "bitrotate.h"

BitboardCA::Bitboard rotate_bits(BitboardCA::Bitboard x) {
  x = ((x << 1) & 0xAA00AA00AA00AA00ULL) | ((x >> 1) & 0x0055005500550055ULL) |
      ((x >> 8) & 0x00AA00AA00AA00AAULL) | ((x << 8) & 0x5500550055005500ULL);

  x = ((x << 2) & 0xCCCC0000CCCC0000ULL) | ((x >> 2) & 0x0000333300003333ULL) |
      ((x >> 16) & 0x0000CCCC0000CCCCULL) | ((x << 16) & 0x3333000033330000ULL);

  x = ((x << 4) & 0xF0F0F0F000000000ULL) | ((x >> 4) & 0x000000000F0F0F0FULL) |
      ((x >> 32) & 0x00000000F0F0F0F0ULL) | ((x << 32) & 0x0F0F0F0F00000000ULL);
  return x;
}
