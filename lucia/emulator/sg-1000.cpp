#include <sg/interface/interface.hpp>

struct SG1000 : Emulator {
  SG1000();
  auto load() -> bool override;
  auto open(velvet::Node::Object, string name, vfs::file::mode mode, bool required) -> shared_pointer<vfs::file> override;
  auto input(velvet::Node::Input) -> void override;
};

SG1000::SG1000() {
  interface = new velvet::SG1000::SG1000Interface;
  medium = mia::medium("SG-1000");
  manufacturer = "Sega";
  name = "SG-1000";
}

auto SG1000::load() -> bool {
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

auto SG1000::open(velvet::Node::Object node, string name, vfs::file::mode mode, bool required) -> shared_pointer<vfs::file> {
  if(name == "manifest.bml") return Emulator::manifest();

  auto document = BML::unserialize(game.manifest);
  auto programROMSize = document["game/board/memory(content=Program,type=ROM)/size"].natural();
  auto saveRAMVolatile = (bool)document["game/board/memory(Content=Save,type=RAM)/volatile"];

  if(name == "program.rom") {
    return vfs::memory::open(game.image.data(), programROMSize);
  }

  if(name == "save.ram" && !saveRAMVolatile) {
    auto location = locate(game.location, ".sav", settings.paths.saves);
    if(auto result = vfs::disk::open(location, mode)) return result;
  }

  return {};
}

auto SG1000::input(velvet::Node::Input node) -> void {
  auto name = node->name();
  maybe<InputMapping&> mapping;
  if(name == "Up"   ) mapping = virtualPad.up;
  if(name == "Down" ) mapping = virtualPad.down;
  if(name == "Left" ) mapping = virtualPad.left;
  if(name == "Right") mapping = virtualPad.right;
  if(name == "1"    ) mapping = virtualPad.a;
  if(name == "2"    ) mapping = virtualPad.b;

  if(mapping) {
    auto value = mapping->value();
    if(auto button = node->cast<velvet::Node::Button>()) {
      button->setValue(value);
    }
  }
}
