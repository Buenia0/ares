name := celes
build := performance
openmp := false
local := true
flags += -I. -I.. -I../velvet

ifeq ($(local),true)
  flags += -march=native
endif

nall.path := ../nall
include $(nall.path)/GNUmakefile

libco.path := ../libco
include $(libco.path)/GNUmakefile

profile := performance
cores := gb ms md sfc

velvet.path := ../velvet
include $(velvet.path)/GNUmakefile

$(object.path)/mia.o: $(mia.path)/mia.cpp
$(object.path)/mia-resource.o: $(mia.path)/resource/resource.cpp

celes.path = ../celes
celes.flags += $(shell sdl2-config --cflags)
celes.options += $(shell sdl2-config --static-libs)

celes.objects += celes
celes.objects := $(celes.objects:%=$(object.path)/%.o)

$(object.path)/celes.o: $(celes.path)/main.cpp

all.objects := $(libco.objects) $(velvet.objects) $(celes.objects)
all.options := $(libco.options) $(velvet.options) $(celes.options) $(options)

all: $(all.objects)
	$(info Linking $(output.path)/$(name) ...)
	+@$(compiler) -o $(output.path)/$(name) $(all.objects) $(all.options)
ifeq ($(platform),macos)
	rm -rf $(output.path)/$(name).app
	mkdir -p $(output.path)/$(name).app/Contents/MacOS/
	mkdir -p $(output.path)/$(name).app/Contents/Resources/
	mv $(output.path)/$(name) $(output.path)/$(name).app/Contents/MacOS/$(name)
	cp resource/$(name).plist $(output.path)/$(name).app/Contents/Info.plist
	sips -s format icns resource/$(name).png --out $(output.path)/$(name).app/Contents/Resources/$(name).icns
endif

verbose: nall.verbose all;

clean:
ifeq ($(platform),macos)
	rm -rf $(output.path)/$(name).app
endif
	$(call delete,$(object.path)/*)
	$(call delete,$(output.path)/*)

install: all
ifeq ($(platform),windows)
	mkdir -p $(prefix)/$(name)/
else ifeq ($(shell id -un),root)
	$(error "make install should not be run as root")
else ifeq ($(platform),macos)
	mkdir -p ~/Library/Application\ Support/$(name)/
	cp -R $(output.path)/$(name).app /Applications/$(name).app
else ifneq ($(filter $(platform),linux bsd),)
	mkdir -p $(prefix)/bin/
	mkdir -p $(prefix)/share/applications/
	mkdir -p $(prefix)/share/$(name)/
	cp $(output.path)/$(name) $(prefix)/bin/$(name)
	sed "/^Exec/s:$(name):$(prefix)/bin/$(name):" resource/$(name).desktop >$(prefix)/share/applications/$(name).desktop
endif

uninstall:
ifeq ($(platform),windows)
else ifeq ($(shell id -un),root)
	$(error "make uninstall should not be run as root")
else ifeq ($(platform),macos)
	rm -rf /Applications/$(name).app
else ifneq ($(filter $(platform),linux bsd),)
	rm -f $(prefix)/bin/$(name)
	rm -f $(prefix)/share/applications/$(name).desktop
endif

-include $(object.path)/*.d