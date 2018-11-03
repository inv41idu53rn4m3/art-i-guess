# Some shorthands
compile := g++ -O3 -std=c++11
libflags := -l:./libglfw.so.3.2 -lGL -ldl
includes := -Iinclude

# Main build target
bin/test: build/test.o build/window.o build/shader.o build/texture.o build/lodepng.o build/glad.o
	$(compile) -o $@ $^ $(libflags) $(includes)
	ctags -R --fields=+l
	bin/test

# Partial compile targets
build/test.o: test.cpp window.hpp shader.hpp texture.hpp
	$(compile) -c -o $@ $< $(libflags) $(includes)
build/window.o: window.cpp window.hpp
	$(compile) -c -o $@ $< $(libflags) $(includes)
build/shader.o: shader.cpp shader.hpp
	$(compile) -c -o $@ $< $(libflags) $(includes)
build/texture.o: texture.cpp texture.hpp
	$(compile) -c -o $@ $< $(libflags) $(includes)
build/lodepng.o: lodepng.cpp
	$(compile) -c -o $@ $< $(libflags) $(includes)
build/glad.o: glad.c
	$(compile) -c -o $@ $< $(libflags) $(includes)

clean:
	rm build/*
