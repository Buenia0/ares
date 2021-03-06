#include "luna.hpp"

shared_pointer<velvet::Interface> interface;
vector<shared_pointer<velvet::Interface>> interfaces;

namespace nall::Path {
  string settings;
  string templates;
  string data;
}

Video videoInstance;
Audio audioInstance;
Input inputInstance;

#include <cv/interface/interface.hpp>
#include <fc/interface/interface.hpp>
#include <gb/interface/interface.hpp>
#include <gba/interface/interface.hpp>
#include <md/interface/interface.hpp>
#include <ms/interface/interface.hpp>
#include <msx/interface/interface.hpp>
#include <n64/interface/interface.hpp>
#include <ngp/interface/interface.hpp>
#include <pce/interface/interface.hpp>
#include <ps1/interface/interface.hpp>
#include <sfc/interface/interface.hpp>
#include <sg/interface/interface.hpp>
#include <ws/interface/interface.hpp>

#include <nall/main.hpp>
auto nall::main(Arguments arguments) -> void {
  Application::setName("luna");
  Application::setScreenSaver(false);
  settings.load();

  if(file::exists({Path::program(), "paths.bml"})) {
    Path::settings = Path::program();
  } else {
    Path::settings = {Path::userSettings(), "luna/"};
    directory::create(Path::settings);
  }
  if(auto document = BML::unserialize(file::read({Path::settings, "paths.bml"}))) {
    Path::templates = document["templates"].text();
    Path::data = document["data"].text();
  }
  if(!directory::exists(Path::templates)) {
    Path::templates = {Path::userData(), "luna/"};
    directory::create(Path::templates);
  }
  if(!directory::exists(Path::data)) {
    Path::data = {Path::user(), "luna/"};
    directory::create(Path::data);
  }
  file::write({Path::settings, "paths.bml"}, string{
    "data: ", Path::data, "\n",
    "templates: ", Path::templates, "\n"
  });

  //create interfaces list in alphabetical order of interface->name() values

  #ifdef CORE_CV
  interfaces.append(new velvet::ColecoVision::ColecoVisionInterface);
  #endif

  #ifdef CORE_FC
  interfaces.append(new velvet::Famicom::FamicomInterface);
  #endif

  #ifdef CORE_GB
  interfaces.append(new velvet::GameBoy::GameBoyInterface);
  #endif

  #ifdef CORE_GB
  interfaces.append(new velvet::GameBoy::GameBoyColorInterface);
  #endif

  #ifdef CORE_GBA
  interfaces.append(new velvet::GameBoyAdvance::GameBoyAdvanceInterface);
  #endif

  #ifdef CORE_GBA
  interfaces.append(new velvet::GameBoyAdvance::GameBoyPlayerInterface);
  #endif

  #ifdef CORE_MD
  interfaces.append(new velvet::MegaDrive::MegaDriveInterface);
  #endif

  #ifdef CORE_MS
  interfaces.append(new velvet::MasterSystem::GameGearInterface);
  #endif

  #ifdef CORE_MS
  interfaces.append(new velvet::MasterSystem::MasterSystemInterface);
  #endif

  #ifdef CORE_MSX
  interfaces.append(new velvet::MSX::MSXInterface);
  #endif

  #ifdef CORE_MSX
  interfaces.append(new velvet::MSX::MSX2Interface);
  #endif

  #ifdef CORE_N64
  interfaces.append(new velvet::Nintendo64::Nintendo64Interface);
  #endif

  #ifdef CORE_NGP
  interfaces.append(new velvet::NeoGeoPocket::NeoGeoPocketInterface);
  #endif

  #ifdef CORE_NGP
  interfaces.append(new velvet::NeoGeoPocket::NeoGeoPocketColorInterface);
  #endif

  #ifdef CORE_PCE
  interfaces.append(new velvet::PCEngine::PCEngineInterface);
  #endif

  #ifdef CORE_PCE
  interfaces.append(new velvet::PCEngine::PCEngineDuoInterface);
  #endif

  #ifdef CORE_PS1
  interfaces.append(new velvet::PlayStation::PlayStationInterface);
  #endif

  #ifdef CORE_WS
  interfaces.append(new velvet::WonderSwan::PocketChallengeV2Interface);
  #endif

  #ifdef CORE_SG
  interfaces.append(new velvet::SG1000::SC3000Interface);
  #endif

  #ifdef CORE_SG
  interfaces.append(new velvet::SG1000::SG1000Interface);
  #endif

  #ifdef CORE_SFC
  interfaces.append(new velvet::SuperFamicom::SuperFamicomInterface);
  #endif

  #ifdef CORE_PCE
  interfaces.append(new velvet::PCEngine::SuperGrafxInterface);
  #endif

  #ifdef CORE_WS
  interfaces.append(new velvet::WonderSwan::SwanCrystalInterface);
  #endif

  #ifdef CORE_WS
  interfaces.append(new velvet::WonderSwan::WonderSwanInterface);
  #endif

  #ifdef CORE_WS
  interfaces.append(new velvet::WonderSwan::WonderSwanColorInterface);
  #endif

  velvet::platform = &emulator;

  Instances::program.construct();
  emulator.inputUpdate();
  inputManager.poll();
  hotkeys.bind();

  Application::onMain({&Emulator::main, &emulator});
  Application::run();

  settings.save();
  Instances::program.destruct();
}
