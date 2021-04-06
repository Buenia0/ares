velvet.components += z80 tms9918 sn76489

velvet.objects += velvet-sg-interface
velvet.objects += velvet-sg-cpu velvet-sg-vdp velvet-sg-psg
velvet.objects += velvet-sg-system velvet-sg-cartridge
velvet.objects += velvet-sg-controller

$(object.path)/velvet-sg-interface.o:  $(velvet.path)/sg/interface/interface.cpp
$(object.path)/velvet-sg-cpu.o:        $(velvet.path)/sg/cpu/cpu.cpp
$(object.path)/velvet-sg-vdp.o:        $(velvet.path)/sg/vdp/vdp.cpp
$(object.path)/velvet-sg-psg.o:        $(velvet.path)/sg/psg/psg.cpp
$(object.path)/velvet-sg-system.o:     $(velvet.path)/sg/system/system.cpp
$(object.path)/velvet-sg-cartridge.o:  $(velvet.path)/sg/cartridge/cartridge.cpp
$(object.path)/velvet-sg-controller.o: $(velvet.path)/sg/controller/controller.cpp
