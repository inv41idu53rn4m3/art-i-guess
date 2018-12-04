# Dummy targets
# Main program
build: bin/ build/ bin/test

# Progress showcase
info: screenshots/index.html

# Clean up build directory
clean:
	rm build/*
	rm bin/test

# Some shorthands
compile := g++ -O3 -std=c++11
libflags := -l:./libglfw.so.3.2 -lGL -ldl
includes := -Iinclude

# Main program target
bin/test: build/test.o build/window.o build/shader.o build/texture.o build/framebuffer.o build/lodepng.o build/glad.o
	$(compile) -o $@ $^ $(libflags) $(includes)

# Partial compile targets
build/test.o: test.cpp window.hpp shader.hpp texture.hpp
	$(compile) -c -o $@ $< $(libflags) $(includes)
build/window.o: window.cpp window.hpp
	$(compile) -c -o $@ $< $(libflags) $(includes)
build/shader.o: shader.cpp shader.hpp
	$(compile) -c -o $@ $< $(libflags) $(includes)
build/texture.o: texture.cpp texture.hpp
	$(compile) -c -o $@ $< $(libflags) $(includes)
build/framebuffer.o: framebuffer.cpp framebuffer.hpp
	$(compile) -c -o $@ $< $(libflags) $(includes)
build/lodepng.o: lodepng.cpp
	$(compile) -c -o $@ $< $(libflags) $(includes)
build/glad.o: glad.c
	$(compile) -c -o $@ $< $(libflags) $(includes)

build/:
	mkdir build
bin/:
	mkdir bin

screenshots/index.html: screenshots/info.md screenshots/head.html screenshots/tail.html
	cat screenshots/head.html > screenshots/index.html
	markdown screenshots/info.md >> screenshots/index.html
	cat screenshots/tail.html >> screenshots/index.html
