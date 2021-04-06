#include <velvet/velvet.hpp>
#include "sn76489.hpp"

namespace velvet {

#include "serialization.cpp"

auto SN76489::clock() -> array<double[2]> {
  tone0.clock();
  tone1.clock();
  tone2.clock();
  noise.clock();

  array<uint4[4]> toneoutput{15, 15, 15, 15};
  if(tone0.output) toneoutput[0] = tone0.volume;
  if(tone1.output) toneoutput[1] = tone1.volume;
  if(tone2.output) toneoutput[2] = tone2.volume;
  if(noise.output) toneoutput[3] = noise.volume;

  array<double[2]> output{0.0, 0.0};

  if (isStereo == false) {
    double sample = 0.0;
    sample += volume[toneoutput[0]];
    sample += volume[toneoutput[1]];
    sample += volume[toneoutput[2]];
    sample += volume[toneoutput[3]];

    output[0] = output[1] = (sample / 4.0);
  } else {
    double left = 0.0;
    if(io.enable.bit(4)) left  += volume[toneoutput[0]];
    if(io.enable.bit(5)) left  += volume[toneoutput[1]];
    if(io.enable.bit(6)) left  += volume[toneoutput[2]];
    if(io.enable.bit(7)) left  += volume[toneoutput[3]];

    double right = 0.0;
    if(io.enable.bit(0)) right += volume[toneoutput[0]];
    if(io.enable.bit(1)) right += volume[toneoutput[1]];
    if(io.enable.bit(2)) right += volume[toneoutput[2]];
    if(io.enable.bit(3)) right += volume[toneoutput[3]];

    output[0] = (left / 4.0);
    output[1] = (right / 4.0);
  }

  return output;
}

auto SN76489::Tone::clock() -> void {
  if(!counter--) {
    counter = pitch;
    output ^= 1;
  }
}

auto SN76489::Noise::clock() -> void {
  if(!counter--) {
    counter = array<uint10[4]>{0x10, 0x20, 0x40, pitch}[rate];
    if(flip ^= 1) {  //0->1 transition
      output = !lfsr.bit(0);
      lfsr = (lfsr.bit(0) ^ lfsr.bit(3) & enable) << 15 | lfsr >> 1;
    }
  }
}

auto SN76489::write(uint8 data) -> void {
  if(data.bit(7)) io.register = data.bit(4,6);

  if(io.register.bit(0)) switch(io.register.bit(1,2)) {
  case 0: tone0.volume = data.bit(0,3); break;
  case 1: tone1.volume = data.bit(0,3); break;
  case 2: tone2.volume = data.bit(0,3); break;
  case 3: noise.volume = data.bit(0,3); break;
  }

  else if(data.bit(7)) switch(io.register.bit(1,2)) {
  case 0: tone0.pitch.bit(0,3) = data.bit(0,3); break;
  case 1: tone1.pitch.bit(0,3) = data.bit(0,3); break;
  case 2: tone2.pitch.bit(0,3) = data.bit(0,3); noise.pitch = tone2.pitch; break;
  case 3: noise.rate   = data.bit(0,1);
          noise.enable = data.bit(2);
          noise.lfsr   = 0x8000;
          break;
  }

  else switch(io.register.bit(1,2)) {
  case 0: tone0.pitch.bit(4,9) = data.bit(0,5); break;
  case 1: tone1.pitch.bit(4,9) = data.bit(0,5); break;
  case 2: tone2.pitch.bit(4,9) = data.bit(0,5); noise.pitch = tone2.pitch; break;
  case 3: noise.volume = data.bit(0,3); break;
  }
}

auto SN76489::power() -> void {
  tone0 = {};
  tone1 = {};
  tone2 = {};
  noise = {};
  io = {};
  io.enable = 0xff;

  for(uint level : range(15)) {
    volume[level] = pow(2, level * -2.0 / 6.0);
  }
  volume[15] = 0;
}

auto SN76489::balance(uint8 data) -> void {
  if (isStereo == true) {
    io.enable = data;
  }
}

auto SN76489::setStereo(bool val) -> void {
  isStereo = val;
}

}
