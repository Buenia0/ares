#include <msx/interface/interface.hpp>

struct MSX : Emulator {
  MSX();
  auto load() -> bool override;
  auto open(velvet::Node::Object, string name, vfs::file::mode mode, bool required) -> shared_pointer<vfs::file> override;
  auto input(velvet::Node::Input) -> void override;
};

struct MSX2 : Emulator {
  MSX2();
  auto load() -> bool override;
  auto open(velvet::Node::Object, string name, vfs::file::mode mode, bool required) -> shared_pointer<vfs::file> override;
  auto input(velvet::Node::Input) -> void override;
};

MSX::MSX() {
  interface = new velvet::MSX::MSXInterface;
  medium = mia::medium("MSX");
  manufacturer = "Microsoft";
  name = "MSX";
}

auto MSX::load() -> bool {
  if(auto port = root->find<velvet::Node::Port>("Cartridge Slot")) {
    port->allocate();
    port->connect();
  }

  if(auto port = root->find<velvet::Node::Port>("Controller Port 1")) {
    port->allocate("Gamepad");
    port->connect();
  }

  return true;
}

auto MSX::open(velvet::Node::Object node, string name, vfs::file::mode mode, bool required) -> shared_pointer<vfs::file> {
  if(name == "manifest.bml") return Emulator::manifest();

  if(name == "bios.rom") {
    return vfs::memory::open(Resource::MSX::BIOS, sizeof Resource::MSX::BIOS);
  }

  auto document = BML::unserialize(game.manifest);
  auto programROMSize = document["game/board/memory(content=Program,type=ROM)/size"].natural();

  if(name == "program.rom") {
    return vfs::memory::open(game.image.data(), programROMSize);
  }

  return {};
}

auto MSX::input(velvet::Node::Input node) -> void {
  auto name = node->name();
  maybe<InputMapping&> mapping;
  if(name == "Up"   ) mapping = virtualPad.up;
  if(name == "Down" ) mapping = virtualPad.down;
  if(name == "Left" ) mapping = virtualPad.left;
  if(name == "Right") mapping = virtualPad.right;
  if(name == "A"    ) mapping = virtualPad.a;
  if(name == "B"    ) mapping = virtualPad.b;

  if(mapping) {
    auto value = mapping->value();
    if(auto button = node->cast<velvet::Node::Button>()) {
      button->setValue(value);
    }
  }
}

MSX2::MSX2() {
  interface = new velvet::MSX::MSX2Interface;
  medium = mia::medium("MSX2");
  manufacturer = "Microsoft";
  name = "MSX2";
}

auto MSX2::load() -> bool {
  if(auto port = root->find<velvet::Node::Port>("Cartridge Slot")) {
    port->allocate();
    port->connect();
  }

  if(auto port = root->find<velvet::Node::Port>("Controller Port 1")) {
    port->allocate("Gamepad");
    port->connect();
  }

  return true;
}

auto MSX2::open(velvet::Node::Object node, string name, vfs::file::mode mode, bool required) -> shared_pointer<vfs::file> {
  if(name == "manifest.bml") return Emulator::manifest();

  if(name == "bios.rom") {
    return vfs::memory::open(Resource::MSX2::BIOS, sizeof Resource::MSX2::BIOS);
  }

  if(name == "sub.rom") {
    return vfs::memory::open(Resource::MSX2::Sub, sizeof Resource::MSX2::Sub);
  }

  auto document = BML::unserialize(game.manifest);
  auto programROMSize = document["game/board/memory(content=Program,type=ROM)/size"].natural();

  if(name == "program.rom") {
    return vfs::memory::open(game.image.data(), programROMSize);
  }

  return {};
}

auto MSX2::input(velvet::Node::Input node) -> void {
  auto name = node->name();
  maybe<InputMapping&> mapping;
  if(name == "Up"   ) mapping = virtualPad.up;
  if(name == "Down" ) mapping = virtualPad.down;
  if(name == "Left" ) mapping = virtualPad.left;
  if(name == "Right") mapping = virtualPad.right;
  if(name == "A"    ) mapping = virtualPad.a;
  if(name == "B"    ) mapping = virtualPad.b;

  if(mapping) {
    auto value = mapping->value();
    if(auto button = node->cast<velvet::Node::Button>()) {
      button->setValue(value);
    }
  }
}
