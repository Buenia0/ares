#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include <nall/nall.hpp>
#include <nall/main.hpp>
#include <velvet/velvet.hpp>
#include <gb/interface/interface.hpp>
#include <md/interface/interface.hpp>
#include <ms/interface/interface.hpp>
#include <sfc/interface/interface.hpp>
using namespace velvet;

shared_pointer<velvet::Interface> interface;

struct Emulator : velvet::Platform
{
    bool create(string location)
    {
      velvet::platform = this;
      tick = SDL_GetTicks();

      // load system
      string configfile = file::read({location, "settings.bml"});

      interface->load(root);
      root->copy(velvet::Node::unserialize(configfile));
      interface->power();

      window = SDL_CreateWindow(
        string{interface->game(), " - celes"},
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        100, 100, SDL_WINDOW_HIDDEN
      );

      SDL_AudioSpec desired;
      desired.freq = 48000;
      desired.format = AUDIO_F32SYS;
      desired.channels = 2;
      desired.samples = 512;
      desired.callback = NULL;

      if (SDL_OpenAudio(&desired, NULL) < 0)
      {
        print("audio device could not be opened! SDL_Error: ", SDL_GetError(), "\n");
      }
      else
      {
        SDL_PauseAudio(0);
      }

      return true;
    }

    bool destroy()
    {
      unload();
      SDL_DestroyWindow(window);
      SDL_CloseAudio();
      return true;
    }

    bool run()
    {
      SDL_Event ev;

      while (SDL_PollEvent(&ev)) {
        switch (ev.type) {
          case SDL_KEYDOWN:
          case SDL_KEYUP: {
            bool value = ev.type == SDL_KEYDOWN;

            switch (ev.key.keysym.sym) {
              case SDLK_UP: button.up = value; break;
              case SDLK_DOWN: button.down = value; break;
              case SDLK_LEFT: button.left = value; break;
              case SDLK_RIGHT: button.right = value; break;
              case SDLK_RETURN: button.start = value; break;
              case SDLK_SPACE: button.select = value; break;
              case SDLK_a: button.a = value; break;
              case SDLK_b: button.b = value; break;
              case SDLK_c: button.c = value; break;
              case SDLK_x: button.x = value; break;
              case SDLK_y: button.y = value; break;
              case SDLK_z: button.z = value; break;
              case SDLK_l: button.lb = value; break;
              case SDLK_r: button.rb = value; break;
            }
          }
          break;
          case SDL_QUIT: {
            return false;
          }
          break;
        }
      }

      if (interface) interface->run();

      return !!interface;
    }

    void sync()
    {
      constexpr auto audioBufLowWatermark = 1024 * sizeof(float) * 2;
      constexpr auto audioBufHighWatermark = 2048 * sizeof(float) * 2;
      constexpr auto audioBufMaxWatermark = 4096 * sizeof(float) * 2;
      int32_t tickdelta = samplecount / 48;
      samplecount %= 48;

      auto qlen = SDL_GetQueuedAudioSize(1);
      if (qlen < audioBufLowWatermark) tickdelta -= 1;
      if (qlen > audioBufHighWatermark) tickdelta += 1;
      if (qlen > audioBufMaxWatermark) SDL_ClearQueuedAudio(1);
      tickdelta = max(tickdelta, 0);

      tick += tickdelta;
      if (auto currentTick = SDL_GetTicks(); tick > currentTick)
      {
        SDL_Delay(tick - currentTick);
      }
      else if (currentTick - tick > 125) 
      {
        tick = SDL_GetTicks();
      }
    }

    void attach(Node::Object node)
    {
      if (interface && node->is<velvet::Node::Screen>()) {
        screens = root->find<velvet::Node::Screen>();
      }

      if (interface && node->is<velvet::Node::Stream>()) {
        streams = root->find<velvet::Node::Stream>();
      }
    }

    void detach(Node::Object node)
    {
      if (interface && node->is<velvet::Node::Screen>()) {
        screens = root->find<velvet::Node::Screen>();
      }

      if (interface && node->is<velvet::Node::Stream>()) {
        streams = root->find<velvet::Node::Stream>();
      }
    }

    shared_pointer<vfs::file> open(Node::Object node, string name, vfs::file::mode mode, bool required) override
    {
      using disk = vfs::disk;
      if (auto r = disk::open({node->attribute("location"), name}, mode)) return r;
      if (auto r = disk::open({root->attribute("location"), name}, mode)) return r;

      print("missing ", (required) ? "required" : "optional", " file: ", name, "\n");

      return {};
    }

    void event(velvet::Event) override {}

    void log(string_view message) override {}

    void video(Node::Screen, const u32 *data, uint pitch, uint width, uint height) override
    {
      if (w != width || h != height) {
        w = width, h = height;
        SDL_SetWindowSize(window, w * scale, h * scale);
        SDL_ShowWindow(window);
      }

      auto b = SDL_CreateRGBSurfaceFrom(const_cast<u32*>(data), w, h, 32, pitch, 0xff<<16, 0xff<<8, 0xff, 0);
      if (!b) return (void)print("surface could not be created! SDL_Error: ", SDL_GetError(), "\n");
      SDL_BlitScaled(b, nullptr, SDL_GetWindowSurface(window), nullptr);
      SDL_UpdateWindowSurface(window);
      SDL_FreeSurface(b);
      sync();
    }

    void audio(Node::Stream) override
    {
      if (!streams) return;

      vector<float> data;

      while (true) {
        for (auto& stream : streams) {
          if (!stream->pending()) {

            if (data.size() != 0) {
              SDL_QueueAudio(1, data.data(), data.size() * sizeof(float));
            }

            return;
          }
        }

        double samples[2] = {0.0, 0.0};

        for (auto& stream : streams) {
          double buffer[2];
          auto channels = stream->read(buffer);

          for (uint c : range(2)) {
            samples[c] += buffer[c % channels];
          }
        }

        // Mix down all the acquired audio samples to avoid clipping issues

        for (uint c : range(2)) {
          samples[c] /= streams.size();
        }

        for (uint c : range(2)) {
          data.append(max(-1.0, min(+1.0, samples[c])));
        }

        samplecount += 1;
      }
    }

    void input(Node::Input node) override
    {
      if (auto b = node->cast<Node::Button>()) {
        auto name = node->name();

        if (name == "Up") b->setValue(button.up);
        else if (name == "Down") b->setValue(button.down);
        else if (name == "Left") b->setValue(button.left);
        else if (name == "Right") b->setValue(button.right);
        else if (name == "Start") b->setValue(button.start);
        else if (name == "Select") b->setValue(button.select);
        else if (name == "A") b->setValue(button.a);
        else if (name == "B") b->setValue(button.b);
        else if (name == "C") b->setValue(button.c);
        else if (name == "X") b->setValue(button.x);
        else if (name == "Y") b->setValue(button.y);
        else if (name == "Z") b->setValue(button.z);
        else if (name == "L") b->setValue(button.lb);
        else if (name == "R") b->setValue(button.rb);
        else if (name != "Reset") print(name, "\n");
      }
    }

    void unload()
    {
        if (interface) interface->unload();
    }


    Node::Object root;

    vector<Node::Screen> screens;
    vector<Node::Stream> streams;

    SDL_Window *window = NULL;
    SDL_AudioDeviceID audioDev = 0;

    u32 w = 0;
    u32 h = 0;
    u32 scale = 2;
    u32 samplecount = 0;
    u32 tick;

    struct Buttons {
      bool up{}, down{}, left{}, right{};
      bool a{}, b{}, x{}, y{}, c{}, z{};
      bool lb{}, lt{}, rb{}, rt{};
      bool back{}, start{}, select{};
    } button;

} emulator;

void nall::main(Arguments arguments) {
  auto location = arguments.take();
  if (!location) return (void)print("usage: celes <system folder>\n");

  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
    return (void)print("SDL2 could not be initialized! SDL_Error: ", SDL_GetError(), "\n");
  }

  string system;

  if (auto f = file::read({location, "manifest.bml"}); f) {
    if (auto manifest = BML::unserialize(f); manifest) {
      system = manifest["system"].value().strip();
    }
    else {
      return (void)print("could not parse system manifest\n");
    }
  }
  else {
    return (void)print("could not open system manifest\n");
  }

  #ifdef CORE_GB
  if (interface = new GameBoy::GameBoyInterface; interface->name() == system); else
  #endif
  #ifdef CORE_GB
  if (interface = new GameBoy::GameBoyColorInterface; interface->name() == system); else
  #endif
  #ifdef CORE_MD
  if (interface = new MegaDrive::MegaDriveInterface; interface->name() == system); else
  #endif
  #ifdef CORE_MS
  if (interface = new MasterSystem::GameGearInterface; interface->name() == system); else
  #endif
  #ifdef CORE_MS
  if (interface = new MasterSystem::MasterSystemInterface; interface->name() == system); else
  #endif
  #ifdef CORE_SFC
  if (interface = new SuperFamicom::SuperFamicomInterface; interface->name() == system); else
  #endif
  return (void)print("unknown or unsupported system: ", system, "\n");
  emulator.create(location);
  while (emulator.run());
  emulator.destroy();
  SDL_Quit();
}