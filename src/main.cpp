#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "../externals/BitboardCA-embedded/include/GenerationOuterTotalisticCA.h"
#include "inner_ca_a.h"
#include "inner_ca_b.h"

const std::string title = "Cellular automata art";
constexpr int pixel_size = 2;
constexpr int board_width = 400;
constexpr int board_height = 400;

namespace BCA = BitboardCA;

int main(int argc, char *argv[]) {
  SDL2pp::SDL sdl(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER |
                  SDL_INIT_EVENTS);
  SDL2pp::Window window(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                        board_width * pixel_size, board_height * pixel_size, 0);
  SDL2pp::Renderer renderer(
      window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  int start_mode = 1;
  // int start_mode = 17;
  for (int mode = start_mode; mode < 23; mode++) {

    BCA::GenerationOuterTotalisticCA ca_a(board_width, board_height, 4);
    InnerCA_A inner_ca_a(mode, ca_a.GetSizeX(), ca_a.GetSizeY());
    ca_a.SetInnerCAInstance(&inner_ca_a);
    for (int y = 0; y < board_height; y++) {
      for (int x = 0; x < board_width; x++) {
        ca_a.SetCellState(x, y, rand() % 4);
      }
    }

    BCA::GenerationOuterTotalisticCA ca_b(board_width, board_height, 4);
    InnerCA_B inner_ca_b(mode, ca_b.GetSizeX(), ca_b.GetSizeY());
    ca_b.SetInnerCAInstance(&inner_ca_b);
    for (int y = 0; y < board_height; y++) {
      for (int x = 0; x < board_width; x++) {
        ca_b.SetCellState(x, y, rand() % 4);
      }
    }

    for (int i = 0; i < 500; i++) {
      SDL_Event event;
      SDL_PollEvent(&event);
      if (event.type == SDL_QUIT)
        return 0;
      renderer.SetDrawColor(0, 0, 0, 255);
      renderer.Clear();
      for (int y = 0; y < board_height; y++) {
        for (int x = 0; x < board_width; x++) {
          {
            auto state_a = ca_a.GetCellState(x, y);
            auto state_b = ca_b.GetCellState(x, y);
            // auto r = ((state_a * 7 + state_b * 13) * 19) % 255;
            // auto g = ((state_a * 13 + state_b * 7) * 23) % 255;
            // auto b = ((state_a * 3 + state_b * 5) * 7) % 255;
            auto r = ((state_a + state_b) * 67) % 255;
            auto g = ((state_a + state_b) * 317) % 255;
            auto b = ((state_a + state_b) * 299) % 255;
            renderer.SetDrawColor(r, g, b, 255);
            renderer.FillRect(x * pixel_size, y * pixel_size,
                              x * pixel_size + pixel_size - 1,
                              y * pixel_size + pixel_size - 1);
          }
        }
      }
      renderer.Present();

      ca_a.Step();
      ca_b.Step();
    }
  }

  return 0;
}
