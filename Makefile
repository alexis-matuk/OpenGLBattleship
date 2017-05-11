CC = g++
CXX = g++
LDFLAGS = -lpthread -lIL -lglm -ljpeg -lpng -lSOIL -lfreetype -lftgl -lm $(LIBGL)
CPPFLAGS = -std=c++0x -Wno-deprecated-declarations -I/usr/include/freetype2
GLMA = glm/glm/.libs/libglm.a
TARGET = battleship
SRC=$(wildcard *.cpp)
OBJ=$(SRC:.cpp=.o)

ifeq ($(shell uname -s), Darwin)
	LIBGL = -framework OpenGL -framework GLUT -framework CoreFoundation
else
	LIBGL = -lGL -lGLU -lglut
endif

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(GLMA) $(CFLAGS) $(LDFLAGS)

.PHONY: clean

clean:
	rm -f *.o *.out $(TARGET)
