#include <ruby/ruby.hpp>
using namespace ruby;

#include <hiro/hiro.hpp>
using namespace hiro;

#include <velvet/velvet.hpp>
extern shared_pointer<velvet::Interface> interface;
extern vector<shared_pointer<velvet::Interface>> interfaces;

#include <nall/instance.hpp>

namespace nall::Path {
  extern string settings;   // ~/.local/share/luna/
  extern string templates;  // ~/.local/share/luna/Systems/
  extern string data;       // ~/luna/
}

extern Video videoInstance;
extern Audio audioInstance;
extern Input inputInstance;

#include "resource/resource.hpp"
#include "menus/menus.hpp"
#include "program/program.hpp"
#include "settings/settings.hpp"
#include "input/input.hpp"
#include "emulator/emulator.hpp"
