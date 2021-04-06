velvet.components += z80 tms9918 sn76489

velvet.objects += velvet-cv-interface
velvet.objects += velvet-cv-cpu velvet-cv-vdp velvet-cv-psg
velvet.objects += velvet-cv-system velvet-cv-cartridge
velvet.objects += velvet-cv-controller

$(object.path)/velvet-cv-interface.o:  $(velvet.path)/cv/interface/interface.cpp
$(object.path)/velvet-cv-cpu.o:        $(velvet.path)/cv/cpu/cpu.cpp
$(object.path)/velvet-cv-vdp.o:        $(velvet.path)/cv/vdp/vdp.cpp
$(object.path)/velvet-cv-psg.o:        $(velvet.path)/cv/psg/psg.cpp
$(object.path)/velvet-cv-system.o:     $(velvet.path)/cv/system/system.cpp
$(object.path)/velvet-cv-cartridge.o:  $(velvet.path)/cv/cartridge/cartridge.cpp
$(object.path)/velvet-cv-controller.o: $(velvet.path)/cv/controller/controller.cpp
