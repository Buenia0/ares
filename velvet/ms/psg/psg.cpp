#include <ms/ms.hpp>

namespace velvet::MasterSystem {

PSG psg;
#include "serialization.cpp"

auto PSG::load(Node::Object parent) -> void {
  node = parent->append<Node::Component>("PSG");

  stream = node->append<Node::Stream>("PSG");
  stream->setChannels(Model::MasterSystem() ? 1 : 2);
  stream->setFrequency(system.colorburst() / 16.0);
  stream->addHighPassFilter(20.0, 1);
}

auto PSG::unload() -> void {
  node = {};
  stream = {};
}

auto PSG::main() -> void {
  auto samples = SN76489::clock();

  if (Model::GameGear()) {
    stream->sample(samples[0], samples[1]);
  } else if (Model::MasterSystem()) {
    stream->sample(samples[0]);
  }

  step(1);
}

auto PSG::step(uint clocks) -> void {
  Thread::step(clocks);
  Thread::synchronize(cpu);
}

auto PSG::balance(uint8 data) -> void {
  SN76489::balance(data);
}

auto PSG::power() -> void {
  SN76489::power();
  SN76489::setStereo(Model::GameGear());
  Thread::create(system.colorburst() / 16.0, {&PSG::main, this});

  io = {};
}

}
