velvet.components += wdc65816 spc700 arm7tdmi gsu hg51b upd96050

velvet.objects += velvet-sfc-interface velvet-sfc-system velvet-sfc-controller
velvet.objects += velvet-sfc-cartridge velvet-sfc-memory
velvet.objects += velvet-sfc-cpu velvet-sfc-smp velvet-sfc-dsp velvet-sfc-ppu
velvet.objects += velvet-sfc-coprocessor velvet-sfc-expansion velvet-sfc-slot

$(object.path)/velvet-sfc-interface.o:   $(velvet.path)/sfc/interface/interface.cpp
$(object.path)/velvet-sfc-system.o:      $(velvet.path)/sfc/system/system.cpp
$(object.path)/velvet-sfc-controller.o:  $(velvet.path)/sfc/controller/controller.cpp
$(object.path)/velvet-sfc-cartridge.o:   $(velvet.path)/sfc/cartridge/cartridge.cpp
$(object.path)/velvet-sfc-memory.o:      $(velvet.path)/sfc/memory/memory.cpp

$(object.path)/velvet-sfc-cpu.o:         $(velvet.path)/sfc/cpu/cpu.cpp
$(object.path)/velvet-sfc-smp.o:         $(velvet.path)/sfc/smp/smp.cpp
$(object.path)/velvet-sfc-dsp.o:         $(velvet.path)/sfc/dsp/dsp.cpp
$(object.path)/velvet-sfc-ppu.o:         $(velvet.path)/sfc/ppu/ppu.cpp

$(object.path)/velvet-sfc-coprocessor.o: $(velvet.path)/sfc/coprocessor/coprocessor.cpp
$(object.path)/velvet-sfc-expansion.o:   $(velvet.path)/sfc/expansion/expansion.cpp
$(object.path)/velvet-sfc-slot.o:        $(velvet.path)/sfc/slot/slot.cpp
