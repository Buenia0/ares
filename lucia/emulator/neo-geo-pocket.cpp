#include <ngp/interface/interface.hpp>

struct NeoGeoPocket : Emulator {
  NeoGeoPocket();
  auto load() -> bool override;
  auto open(velvet::Node::Object, string name, vfs::file::mode mode, bool required) -> shared_pointer<vfs::file> override;
  auto input(velvet::Node::Input) -> void override;
};

struct NeoGeoPocketColor : Emulator {
  NeoGeoPocketColor();
  auto load() -> bool override;
  auto open(velvet::Node::Object, string name, vfs::file::mode mode, bool required) -> shared_pointer<vfs::file> override;
  auto input(velvet::Node::Input) -> void override;
};

NeoGeoPocket::NeoGeoPocket() {
  interface = new velvet::NeoGeoPocket::NeoGeoPocketInterface;
  medium = mia::medium("Neo Geo Pocket");
  manufacturer = "SNK";
  name = "Neo Geo Pocket";

  firmware.append({"BIOS", "World", "0293555b21c4fac516d25199df7809b26beeae150e1d4504a050db32264a6ad7"});
}

auto NeoGeoPocket::load() -> bool {
  if(!file::exists(firmware[0].location)) {
    errorFirmwareRequired(firmware[0]);
    return false;
  }

  if(auto port = root->find<velvet::Node::Port>("Cartridge Slot")) {
    port->allocate();
    port->connect();
  }

  if(auto fastBoot = root->find<velvet::Node::Boolean>("Fast Boot")) {
    fastBoot->setValue(settings.general.fastBoot);
  }

  return true;
}

auto NeoGeoPocket::open(velvet::Node::Object node, string name, vfs::file::mode mode, bool required) -> shared_pointer<vfs::file> {
  if(name == "manifest.bml") return Emulator::manifest();

  if(name == "bios.rom") {
    return loadFirmware(firmware[0]);
  }

  auto document = BML::unserialize(game.manifest);
  auto programROMSize = document["game/board/memory(content=Program,type=Flash)/size"].natural();

  if(name == "program.flash") {
    auto location = locate(game.location, ".sav", settings.paths.saves);
    if(auto result = vfs::disk::open(location, mode)) return result;
    if(mode == vfs::file::mode::read) return vfs::memory::open(game.image.data(), programROMSize);
  }

  return {};
}

auto NeoGeoPocket::input(velvet::Node::Input node) -> void {
  auto name = node->name();
  maybe<InputMapping&> mapping;
  if(name == "Up"    ) mapping = virtualPad.up;
  if(name == "Down"  ) mapping = virtualPad.down;
  if(name == "Left"  ) mapping = virtualPad.left;
  if(name == "Right" ) mapping = virtualPad.right;
  if(name == "A"     ) mapping = virtualPad.a;
  if(name == "B"     ) mapping = virtualPad.b;
  if(name == "Option") mapping = virtualPad.start;

  if(mapping) {
    auto value = mapping->value();
    if(auto button = node->cast<velvet::Node::Button>()) {
      button->setValue(value);
    }
  }
}

NeoGeoPocketColor::NeoGeoPocketColor() {
  interface = new velvet::NeoGeoPocket::NeoGeoPocketColorInterface;
  medium = mia::medium("Neo Geo Pocket Color");
  manufacturer = "SNK";
  name = "Neo Geo Pocket Color";

  firmware.append({"BIOS", "World", "8fb845a2f71514cec20728e2f0fecfade69444f8d50898b92c2259f1ba63e10d"});
}

auto NeoGeoPocketColor::load() -> bool {
  if(!file::exists(firmware[0].location)) {
    errorFirmwareRequired(firmware[0]);
    return false;
  }

  if(auto port = root->find<velvet::Node::Port>("Cartridge Slot")) {
    port->allocate();
    port->connect();
  }

  if(auto fastBoot = root->find<velvet::Node::Boolean>("Fast Boot")) {
    fastBoot->setValue(settings.general.fastBoot);
  }

  return true;
}

auto NeoGeoPocketColor::open(velvet::Node::Object node, string name, vfs::file::mode mode, bool required) -> shared_pointer<vfs::file> {
  if(name == "manifest.bml") return Emulator::manifest();

  if(name == "bios.rom") {
    return loadFirmware(firmware[0]);
  }

  auto document = BML::unserialize(game.manifest);
  auto programROMSize = document["game/board/memory(content=Program,type=Flash)/size"].natural();

  if(name == "program.flash") {
    auto location = locate(game.location, ".sav", settings.paths.saves);
    if(auto result = vfs::disk::open(location, mode)) return result;
    if(mode == vfs::file::mode::read) return vfs::memory::open(game.image.data(), programROMSize);
  }

  return {};
}

auto NeoGeoPocketColor::input(velvet::Node::Input node) -> void {
  auto name = node->name();
  maybe<InputMapping&> mapping;
  if(name == "Up"    ) mapping = virtualPad.up;
  if(name == "Down"  ) mapping = virtualPad.down;
  if(name == "Left"  ) mapping = virtualPad.left;
  if(name == "Right" ) mapping = virtualPad.right;
  if(name == "A"     ) mapping = virtualPad.a;
  if(name == "B"     ) mapping = virtualPad.b;
  if(name == "Option") mapping = virtualPad.start;

  if(mapping) {
    auto value = mapping->value();
    if(auto button = node->cast<velvet::Node::Button>()) {
      button->setValue(value);
    }
  }
}
