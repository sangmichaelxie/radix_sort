# the compiler: gcc for C program, define as g++ for C++
  CC = g++

  # compiler flags:
  #  -g    adds debugging information to the executable file
  #  -Wall turns on most, but not all, compiler warnings
  CFLAGS  = -g -Wall -pedantic -O0 -std=c++0x -I/usr/include
LDFLAGS = -lm

SOURCE1 = radix_sort.cc
TEST_SOURCE = generate_numfile.cc

SOURCE_OBJ = $(SOURCE1:.cc=.o)
TEST_OBJ = $(TEST_SOURCE:.cc=.o)
  # the build target executable:
  EXECUTABLE = radix_sort 
TEST_EXECUTABLE = generate_numfile

all: target tests clean

target : $(EXECUTABLE)
tests: $(TEST_EXECUTABLE)

$(SOURCE_OBJ): $(SOURCE1)
	$(CC) $(CFLAGS) $< -c $(SOURCE1)
$(TEST_OBJ): $(TEST_SOURCE)
	$(CC) $(CFLAGS) $< -c $(TEST_SOURCE)

$(EXECUTABLE): $(SOURCE_OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(TEST_EXECUTABLE): $(TEST_OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)


.PHONY: clean spartan
clean:
	@rm -f $(SOURCE_OBJ) $(TEST_OBJ)  core
spartan: clean
	@rm -f *~ .*~
