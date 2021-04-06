velvet.components := $(call unique,$(velvet.components))

velvet.objects += $(if $(findstring ay38910,$(velvet.components)),velvet-audio-ay38910)
velvet.objects += $(if $(findstring msm5205,$(velvet.components)),velvet-audio-msm5205)
velvet.objects += $(if $(findstring sn76489,$(velvet.components)),velvet-audio-sn76489)
velvet.objects += $(if $(findstring t6w28,$(velvet.components)),velvet-audio-t6w28)
velvet.objects += $(if $(findstring ym2149,$(velvet.components)),velvet-audio-ym2149)
velvet.objects += $(if $(findstring ym2413,$(velvet.components)),velvet-audio-ym2413)

velvet.objects += $(if $(findstring m93lcx6,$(velvet.components)),velvet-eeprom-m93lcx6)
velvet.objects += $(if $(findstring x24c01,$(velvet.components)),velvet-eeprom-x24c01)

velvet.objects += $(if $(findstring arm7tdmi,$(velvet.components)),velvet-processor-arm7tdmi)
velvet.objects += $(if $(findstring gsu,$(velvet.components)),velvet-processor-gsu)
velvet.objects += $(if $(findstring hg51b,$(velvet.components)),velvet-processor-hg51b)
velvet.objects += $(if $(findstring huc6280,$(velvet.components)),velvet-processor-huc6280)
velvet.objects += $(if $(findstring m68k,$(velvet.components)),velvet-processor-m68k)
velvet.objects += $(if $(findstring mos6502,$(velvet.components)),velvet-processor-mos6502)
velvet.objects += $(if $(findstring sm83,$(velvet.components)),velvet-processor-sm83)
velvet.objects += $(if $(findstring spc700,$(velvet.components)),velvet-processor-spc700)
velvet.objects += $(if $(findstring tlcs900h,$(velvet.components)),velvet-processor-tlcs900h)
velvet.objects += $(if $(findstring upd96050,$(velvet.components)),velvet-processor-upd96050)
velvet.objects += $(if $(findstring v30mz,$(velvet.components)),velvet-processor-v30mz)
velvet.objects += $(if $(findstring wdc65816,$(velvet.components)),velvet-processor-wdc65816)
velvet.objects += $(if $(findstring z80,$(velvet.components)),velvet-processor-z80)

velvet.objects += $(if $(findstring tms9918,$(velvet.components)),velvet-video-tms9918)
velvet.objects += $(if $(findstring v9938,$(velvet.components)),velvet-video-v9938)

$(object.path)/velvet-audio-ay38910.o:      $(velvet.path)/component/audio/ay38910/ay38910.cpp
$(object.path)/velvet-audio-msm5205.o:      $(velvet.path)/component/audio/msm5205/msm5205.cpp
$(object.path)/velvet-audio-sn76489.o:      $(velvet.path)/component/audio/sn76489/sn76489.cpp
$(object.path)/velvet-audio-t6w28.o:        $(velvet.path)/component/audio/t6w28/t6w28.cpp
$(object.path)/velvet-audio-ym2149.o:       $(velvet.path)/component/audio/ym2149/ym2149.cpp
$(object.path)/velvet-audio-ym2413.o:       $(velvet.path)/component/audio/ym2413/ym2413.cpp

$(object.path)/velvet-eeprom-m93lcx6.o:     $(velvet.path)/component/eeprom/m93lcx6/m93lcx6.cpp
$(object.path)/velvet-eeprom-x24c01.o:      $(velvet.path)/component/eeprom/x24c01/x24c01.cpp

$(object.path)/velvet-processor-arm7tdmi.o: $(velvet.path)/component/processor/arm7tdmi/arm7tdmi.cpp
$(object.path)/velvet-processor-gsu.o:      $(velvet.path)/component/processor/gsu/gsu.cpp
$(object.path)/velvet-processor-hg51b.o:    $(velvet.path)/component/processor/hg51b/hg51b.cpp
$(object.path)/velvet-processor-huc6280.o:  $(velvet.path)/component/processor/huc6280/huc6280.cpp
$(object.path)/velvet-processor-m68k.o:     $(velvet.path)/component/processor/m68k/m68k.cpp
$(object.path)/velvet-processor-mos6502.o:  $(velvet.path)/component/processor/mos6502/mos6502.cpp
$(object.path)/velvet-processor-sm83.o:     $(velvet.path)/component/processor/sm83/sm83.cpp
$(object.path)/velvet-processor-spc700.o:   $(velvet.path)/component/processor/spc700/spc700.cpp
$(object.path)/velvet-processor-tlcs900h.o: $(velvet.path)/component/processor/tlcs900h/tlcs900h.cpp
$(object.path)/velvet-processor-upd96050.o: $(velvet.path)/component/processor/upd96050/upd96050.cpp
$(object.path)/velvet-processor-v30mz.o:    $(velvet.path)/component/processor/v30mz/v30mz.cpp
$(object.path)/velvet-processor-wdc65816.o: $(velvet.path)/component/processor/wdc65816/wdc65816.cpp
$(object.path)/velvet-processor-z80.o:      $(velvet.path)/component/processor/z80/z80.cpp

$(object.path)/velvet-video-tms9918.o:      $(velvet.path)/component/video/tms9918/tms9918.cpp
$(object.path)/velvet-video-v9938.o:        $(velvet.path)/component/video/v9938/v9938.cpp
