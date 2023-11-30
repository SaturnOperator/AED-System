FLAGS = -g -std=c++11

all: qt runMac

# Install icons font
font:
	mkdir -p ~/.fonts/
	cp -p assets/fonts/fa-solid-900.ttf ~/.fonts/
	fc-cache -f

qt:
	mkdir -p build
	qmake -o build/Makefile Team17AED.pro
	cd build && $(MAKE)

runMac: 
	./build/Team17AED.app/Contents/MacOS/Team17AED

runLinux:
	./build/Team17AED

clean:
	rm -rf build/*
	rm -rf build