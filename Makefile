BUILD_DIR=build
CMAKE_MK=$(BUILD_DIR)/Makefile

BUILDTYPE?=Release
PREFIX?=/usr/local

all: build

build:
	@mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR); cmake ../ -DCMAKE_BUILD_TYPE=$(BUILDTYPE)
	$(MAKE) -C $(BUILD_DIR)

install:
	@$(MAKE) -C $(BUILD_DIR) install

clean:
	@$(MAKE) -C $(BUILD_DIR) clean

distclean:
	@rm -rf $(BUILD_DIR)

format:
	clang-format -i src/**/*.cc

test:
	ECHO "No tests yet :'("

.PHONY: all build install clean distclean format test
