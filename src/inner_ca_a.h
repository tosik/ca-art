#ifndef _INCLUDE_GUARD_UUID_D39586CA_ACA9_420C_92E6_E6040FC8A21D_
#define _INCLUDE_GUARD_UUID_D39586CA_ACA9_420C_92E6_E6040FC8A21D_

#include "bitcounter.h"
#include "bitrotate.h"

namespace BCA = BitboardCA;

class InnerCA_A : public BCA::OuterTotalisticCA {
public:
  InnerCA_A(int mode, std::size_t size_x, std::size_t size_y)
      : BCA::OuterTotalisticCA(size_x, size_y), mode(mode) {}

protected:
  BCA::Bitboard Rule(BCA::Bitboard board, BCA::Bitboard s0, BCA::Bitboard s1,
                     BCA::Bitboard s2, BCA::Bitboard s3, BCA::Bitboard s4,
                     BCA::Bitboard s5, BCA::Bitboard s6, BCA::Bitboard s7,
                     BCA::Bitboard s8) {

    if (mode == 1) {
      return s0 * s1 * s2;
    }

    if (mode == 2) {
      if ((~s0 + ~s1 + ~s2 + ~s3 + ~s4) < 0x0FFFFFFFFFFFFFFF) {
        return ~(board | s1 | s2 | s3 | (s4 & s5 & s6 & s7 & s8));
      } else {
        return ~(s1 + s3);
      }
    }

    if (mode == 4) {
      if ((board & 1) == 1) {
        return ~(board | s1 | s2 | s3 | (s4 & s5 & s6 & s7 & s8));
      } else {
        return (board & (s4 | s5)) | (~board & (s2));
      }
    }

    if (mode == 5) {
      if ((board & 1) == 1) {
        return ~s2 & ~s3;
      } else {
        return (board & (s3 | s4 | s5)) | (~board & s2);
      }
    }

    if (mode == 7) {
      auto bits = count_bits(board);
      if (bits > 30) {
        return ~board & (s2);
      } else if (bits < 4) {
        return s2;
      } else {
        return (~board & (s2)) | (board & (s3 | s4 | s5));
      }
    }

    if (mode == 8) {
      auto bits = count_bits(board);
      if (bits == 0) {
        return ~board;
      } else {
        return (~board & (s2)) | (board & (s3 | s4 | s5));
      }
    }

    if (mode == 10) {
      auto bits = count_bits(s1 | s2 | s3);
      if (bits > 40) {
        return (board & ~s2 & ~s3) | s4;
      } else if (bits > 15) {
        return ((~board & (s3)) | (board & (s2 | s3 | s4 | s5)));
      } else if (bits < 2) {
        return board | ~s2;
      } else if (bits < 3) {
        return board | ~s1;
      } else {
        return 0;
      }
    }

    if (mode == 15) {
      if ((~s0 + ~s1 + ~s2 + ~s3 + ~s4) < 0x0FFFFFFFFFFFFFFF) {
        return ~(board | s1 | s2 | s3 | (s4 & s5 & s6 & s7 & s8));
      } else {
        return ~(s1 + s3);
      }
    }

    if (mode == 17) {
      auto bits = count_bits(board);
      if (bits > 20 && bits < 40) {
        return (s1 | s2 | s3 | s4 | s5 | s6 | s7);
      } else if (bits == 0) {
        return 6;
      } else {
        return ((board & (s3 | s4 | s5)) | (~board & s2));
      }
    }

    return 0;
  }

private:
  int mode;
};

#endif
