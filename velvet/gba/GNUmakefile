velvet.components += arm7tdmi

velvet.objects += velvet-gba-memory velvet-gba-interface velvet-gba-system
velvet.objects += velvet-gba-cartridge velvet-gba-player
velvet.objects += velvet-gba-cpu velvet-gba-ppu velvet-gba-apu

$(object.path)/velvet-gba-memory.o:    $(velvet.path)/gba/memory/memory.cpp
$(object.path)/velvet-gba-interface.o: $(velvet.path)/gba/interface/interface.cpp
$(object.path)/velvet-gba-system.o:    $(velvet.path)/gba/system/system.cpp
$(object.path)/velvet-gba-cartridge.o: $(velvet.path)/gba/cartridge/cartridge.cpp
$(object.path)/velvet-gba-player.o:    $(velvet.path)/gba/player/player.cpp
$(object.path)/velvet-gba-cpu.o:       $(velvet.path)/gba/cpu/cpu.cpp
$(object.path)/velvet-gba-ppu.o:       $(velvet.path)/gba/ppu/ppu.cpp
$(object.path)/velvet-gba-apu.o:       $(velvet.path)/gba/apu/apu.cpp
