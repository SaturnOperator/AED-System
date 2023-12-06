FLAGS = -g -std=c++11

# Flag file to keep track of whether the font has been installed
FONT_FLAG := .font_installed

# Get OS name (macOS or Linux)
UNAME := $(shell uname)

all: font $(UNAME)

# Recipe for macOS
Darwin: qt
	@echo "Running on macOS"
	./build/Team17AED.app/Contents/MacOS/Team17AED

# Recipe for Linux
Linux: font qt
	@echo "Running on Linux"
	./build/Team17AED

# Install fonts, only ever needs to run once
font:
	@if [ ! -e $(FONT_FLAG) ]; then \
		echo "Installing fonts..."; \
		mkdir -p ~/.fonts/; \
		cp -p assets/fonts/fa-solid-900.ttf ~/.fonts/; \
		cp -p assets/fonts/frank-light.ttf ~/.fonts/; \
		fc-cache -f; \
		touch $(FONT_FLAG); \
	else \
		echo ""; \
	fi

qt:
	mkdir -p build
	qmake -o build/Makefile Team17AED.pro
	cd build && $(MAKE)

clean:
	rm -rf build/*
	rm -rf build