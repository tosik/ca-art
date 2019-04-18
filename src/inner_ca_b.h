#ifndef _INCLUDE_GUARD_UUID_60412ED4_F3C5_41AA_B5CE_6AE7E1DFBE66_
#define _INCLUDE_GUARD_UUID_60412ED4_F3C5_41AA_B5CE_6AE7E1DFBE66_

#include "bitcounter.h"
#include "bitrotate.h"

namespace BCA = BitboardCA;

class InnerCA_B : public BCA::OuterTotalisticCA {
public:
  InnerCA_B(int mode, std::size_t size_x, std::size_t size_y)
      : BCA::OuterTotalisticCA(size_x, size_y), mode(mode) {}

protected:
  BCA::Bitboard Rule(BCA::Bitboard board, BCA::Bitboard s0, BCA::Bitboard s1,
                     BCA::Bitboard s2, BCA::Bitboard s3, BCA::Bitboard s4,
                     BCA::Bitboard s5, BCA::Bitboard s6, BCA::Bitboard s7,
                     BCA::Bitboard s8) {

    if (mode == 1) {
      return 0;
    }

    if (mode == 3) {
      if (((s0 | s1 | s2 | s3 | s4) & ~board) > s3) {
        return (board & (s3 | s4 | s5 | s6)) | (~board & (s2 | s6));
      } else {
        return ~board | s1 | s2 | s3;
      }
    }

    if (mode == 5) {
      if ((board & 5) == 5) {
        return ~s2 & ~s3;
      } else {
        return (board & (s3 | s4 | s5)) | (~board & s2);
      }
    }

    if (mode == 6) {
      auto bits = count_bits(board);
      if (bits > 40) {
        return board | s0 | s1 | s2;
      } else if (bits < 20) {
        return board | s3;
      } else {
        return (board & ~s2 & ~s3) | s4;
      }
    }

    if (mode == 7) {
      auto bits = count_bits(board);
      if (bits < 4) {
        return s2;
      } else if (bits < 10) {
        return ~board & (s2 | s4 | (bits * 102));
      } else {
        return (~board & (s2)) | (board & (s3 | s4 | s5));
      }
    }

    if (mode == 9) {
      auto bits = count_bits(board);
      if (bits > 34) {
        return 0;
      } else {
        return ((~board & (s3)) | (board & (s2 | s3 | s4 | s5)));
      }
    }

    if (mode == 10) {
      auto bits = count_bits(s1 | s2 | s3);
      if (bits > 40) {
        return (board & ~s2 & ~s3) | s4;
      } else if (bits > 15) {
        return ((~board & (s3)) | (board & (s2 | s3 | s4 | s5)));
      } else if (bits < 2) {
        return board | s1;
      } else if (bits < 3) {
        return board | ~s1;
      } else {
        return 0;
      }
    }

    if (mode == 11) {
      auto bits = count_bits(board);
      if (bits > 20) {
        return rotate_bits(board) | (board & ~s2 & ~s3);
      } else {
        return board | (board & ~s2 & ~s3) | s4;
      }
    }

    if (mode == 12) {
      auto bits = count_bits(board);
      if (bits > 30) {
        return rotate_bits(~board);
      } else if (bits > 15) {
        return rotate_bits(board);
      } else {
        return rotate_bits(rotate_bits(rotate_bits(board))) |
               (board & ~s2 & ~s3) | s4;
      }
    }

    if (mode == 13) {
      auto bits = count_bits(board);
      if (bits < 40) {
        return rotate_bits(rotate_bits(board)) | (board & s3 & s5) | s4;
      } else {
        return rotate_bits(board) | (board | s2);
      }
    }

    if (mode == 14) {
      auto bits = count_bits(board);
      if (bits < 2)
        return s2;
      else if (bits < 10)
        return rotate_bits(s2 | (s3 & s4 & s5 & s6));
      else if (bits > 20)
        return ~board;
      else
        return 0;
    }

    if (mode == 15) {
      auto bits = count_bits(board);
      if (bits > 25)
        return 0xAA55AA55AA55AA55;
      else if (bits > 3)
        return (board & (s3 | s4 | s5)) | (~board & s2);
      else
        return board | s1;
    }

    if (mode == 16) {
      auto bits = count_bits(board);
      if (bits > 20 && bits < 40) {
        return (s1 | s2 | s3 | s4 | s5 | s6 | s7) & 0xAA55AA55AA55AA55;
      } else if (bits == 0) {
        return 6;
      } else {
        return ((board & (s3 | s4 | s5)) | (~board & s2));
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
