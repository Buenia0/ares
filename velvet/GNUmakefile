ifeq ($(platform),windows)
  options += -luuid -lkernel32 -luser32 -lgdi32 -lcomctl32 -lcomdlg32 -lshell32
  options += -Wl,-enable-auto-import
  options += -Wl,-enable-runtime-pseudo-reloc
else ifeq ($(platform),macos)
else ifneq ($(filter $(platform),linux bsd),)
  options += -Wl,-export-dynamic
  options += -lX11 -lXext
else
  $(error "unsupported platform")
endif

velvet.objects := velvet

$(object.path)/velvet.o: $(velvet.path)/velvet/velvet.cpp

ifeq ($(profile),accuracy)
  flags += -DPROFILE_ACCURACY
endif

ifeq ($(profile),performance)
  flags += -DPROFILE_PERFORMANCE
endif

ifneq ($(filter $(cores),fc),)
  include $(velvet.path)/fc/GNUmakefile
endif

ifneq ($(filter $(cores),sfc),)
  include $(velvet.path)/sfc/GNUmakefile
endif

ifneq ($(filter $(cores),n64),)
  include $(velvet.path)/n64/GNUmakefile
endif

ifneq ($(filter $(cores),sg),)
  include $(velvet.path)/sg/GNUmakefile
endif

ifneq ($(filter $(cores),ms),)
  include $(velvet.path)/ms/GNUmakefile
endif

ifneq ($(filter $(cores),md),)
  include $(velvet.path)/md/GNUmakefile
endif

ifneq ($(filter $(cores),ps1),)
  include $(velvet.path)/ps1/GNUmakefile
endif

ifneq ($(filter $(cores),pce),)
  include $(velvet.path)/pce/GNUmakefile
endif

ifneq ($(filter $(cores),msx),)
  include $(velvet.path)/msx/GNUmakefile
endif

ifneq ($(filter $(cores),cv),)
  include $(velvet.path)/cv/GNUmakefile
endif

ifneq ($(filter $(cores),gb),)
  include $(velvet.path)/gb/GNUmakefile
endif

ifneq ($(filter $(cores),gba),)
  include $(velvet.path)/gba/GNUmakefile
endif

ifneq ($(filter $(cores),ws),)
  include $(velvet.path)/ws/GNUmakefile
endif

ifneq ($(filter $(cores),ngp),)
  include $(velvet.path)/ngp/GNUmakefile
endif

include $(velvet.path)/component/GNUmakefile

flags += $(foreach c,$(call strupper,$(cores)),-DCORE_$c)

velvet.objects := $(velvet.objects:%=$(object.path)/%.o)
