#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "../externals/BitboardCA-embedded/include/GenerationOuterTotalisticCA.h"

const std::string title = "Cellular automata art";
constexpr int pixel_size = 2;
constexpr int board_width = 400;
constexpr int board_height = 400;

namespace BCA = BitboardCA;

class InnerCA_A : public BCA::OuterTotalisticCA {
public:
  InnerCA_A(std::size_t size_x, std::size_t size_y)
      : BCA::OuterTotalisticCA(size_x, size_y) {}

protected:
  BCA::Bitboard Rule(BCA::Bitboard board, BCA::Bitboard s0, BCA::Bitboard s1,
                     BCA::Bitboard s2, BCA::Bitboard s3, BCA::Bitboard s4,
                     BCA::Bitboard s5, BCA::Bitboard s6, BCA::Bitboard s7,
                     BCA::Bitboard s8) {
    return (board & (s3 | s4 | s5 | s6)) | (~board & (s2 | s5));
  }
};

int main(int argc, char *argv[]) {
  SDL2pp::SDL sdl(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER |
                  SDL_INIT_EVENTS);
  SDL2pp::Window window(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                        board_width * pixel_size, board_height * pixel_size, 0);
  SDL2pp::Renderer renderer(
      window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  BCA::GenerationOuterTotalisticCA ca(board_width, board_height, 4);
  InnerCA_A inner_ca_a(ca.GetSizeX(), ca.GetSizeY());
  ca.SetInnerCAInstance(&inner_ca_a);
  for (int y = 0; y < board_height; y++) {
    for (int x = 0; x < board_width; x++) {
      ca.SetCellState(x, y, rand() % 4);
    }
  }

  while (true) {
    SDL_Event event;
    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT)
      break;
    renderer.SetDrawColor(0, 0, 0, 255);
    renderer.Clear();
    for (int y = 0; y < board_height; y++) {
      for (int x = 0; x < board_width; x++) {
        auto state = ca.GetCellState(x, y);
        switch (state) {
        case 0:
          renderer.SetDrawColor(255, 255, 255, 255);
          break;
        case 1:
          renderer.SetDrawColor(255, 0, 0, 255);
          break;
        case 2:
          renderer.SetDrawColor(255, 127, 0, 255);
          break;
        case 3:
          renderer.SetDrawColor(255, 127, 127, 255);
          break;
        }
        renderer.FillRect(x * pixel_size, y * pixel_size,
                          x * pixel_size + pixel_size - 1,
                          y * pixel_size + pixel_size - 1);
      }
    }
    renderer.Present();

    ca.Step();
  }

  return 0;
}
