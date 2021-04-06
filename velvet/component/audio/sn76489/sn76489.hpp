#pragma once

namespace velvet {

//Texas Instruments SN76489

struct SN76489 {
  //sn76489.cpp
  auto clock() -> array<double[2]>;
  auto write(uint8 data) -> void;
  auto balance(uint8 data) -> void;
  auto power() -> void;
  auto setStereo(bool val) -> void;

  //serialization.cpp
  auto serialize(serializer&) -> void;

protected:
  struct Tone {
    //sn76489.cpp
    auto clock() -> void;

    //serialization.cpp
    auto serialize(serializer&) -> void;

    uint4  volume = 15;
    uint10 counter;
    uint10 pitch;
    uint1  output;
  };

  struct Noise {
    //sn76489.cpp
    auto clock() -> void;

    //serialization.cpp
    auto serialize(serializer&) -> void;

    uint4  volume = 15;
    uint10 counter;
    uint10 pitch;
    uint1  enable;
    uint2  rate;
    uint16 lfsr = 0x8000;
    uint1  flip;
    uint1  output;
  };

  struct IO {
    uint3 register;
    uint8 enable = 0xff;
  };

  Tone tone0;
  Tone tone1;
  Tone tone2;
  Noise noise;
  IO io;
  double volume[16];
  bool isStereo = false;
};

}
