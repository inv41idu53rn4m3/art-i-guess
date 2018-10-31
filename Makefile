compile := g++ -O3 -std=c++17
libflags := -l:./libglfw.so.3.2 -lGL -ldl
includes := -Iinclude -Ilib
sources := *.cpp *.c #test.cpp glad.c
exec := bin/test
test: $(sources)
	$(compile) -o $(exec) $(sources) $(libflags) $(includes)
	ctags -R --fields=+l
	bin/test
