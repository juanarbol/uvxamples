NINJA?=ninja

BUILD_DIR=build
CMAKE_MK=$(BUILD_DIR)/Makefile

BUILDTYPE?=Release
PREFIX?=/usr/local

all: build

build: $(CMAKE_MK)
	$(NINJA) -C $(BUILD_DIR)

$(CMAKE_MK):
	@mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR); cmake ../ -DCMAKE_BUILD_TYPE=$(BUILDTYPE) -DCMAKE_INSTALL_PREFIX=$(PREFIX) -GNinja

install:
	@$(NINJA) -C $(BUILD_DIR) install

clean:
	@$(NINJA) -C $(BUILD_DIR) clean

distclean:
	@rm -rf $(BUILD_DIR)

format:
	clang-format **/**/*.cc

test:
	ECHO "No tests yet :'("

.PHONY: all build install clean distclean format test
