velvet.components += mos6502 ym2149 ym2413 x24c01

velvet.objects += velvet-fc-interface velvet-fc-system velvet-fc-controller
velvet.objects += velvet-fc-cartridge velvet-fc-cpu velvet-fc-apu velvet-fc-ppu
velvet.objects += velvet-fc-fds

$(object.path)/velvet-fc-interface.o:  $(velvet.path)/fc/interface/interface.cpp
$(object.path)/velvet-fc-system.o:     $(velvet.path)/fc/system/system.cpp
$(object.path)/velvet-fc-controller.o: $(velvet.path)/fc/controller/controller.cpp
$(object.path)/velvet-fc-cartridge.o:  $(velvet.path)/fc/cartridge/cartridge.cpp
$(object.path)/velvet-fc-cpu.o:        $(velvet.path)/fc/cpu/cpu.cpp
$(object.path)/velvet-fc-apu.o:        $(velvet.path)/fc/apu/apu.cpp
$(object.path)/velvet-fc-ppu.o:        $(velvet.path)/fc/ppu/ppu.cpp
$(object.path)/velvet-fc-fds.o:        $(velvet.path)/fc/fds/fds.cpp
