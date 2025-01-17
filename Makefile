ifeq ($(OS),Windows_NT)
	SHELL := pwsh.exe
else
	SHELL := pwsh
endif

ifneq (,$(wildcard .env))
	include .env
	export
endif

.SHELLFLAGS := -NoProfile -Command
.PHONY: configure build test clean

PRESET ?= default
OUT ?= out
CONFIG ?= Release

$(OUT)/$(PRESET)/CMakeCache.txt: CMakeLists.txt
	cmake \
		--preset $(PRESET)

configure: $(OUT)/$(PRESET)/CMakeCache.txt

build: configure
	cmake \
		--build $(OUT)/$(PRESET) \
		--config $(CONFIG)

test: build
	ctest \
		--output-on-failure \
		--test-dir $(OUT)/$(PRESET) \
		--build-config $(CONFIG)

clean:
	@-Remove-Item -Recurse -Force -Path $(OUT)