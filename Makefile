CXX = g++
CXXFLAGS = -Wall -pedantic -std=c++17

HEADERS = $(wildcard src/*.h)
SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(SOURCES:src/%.cpp=build/%.o)
TESTS = $(wildcard tests/*.test.cpp)


TEXT_FILES = help.txt welcome.txt
TEXT_FILES_DEST = $(addprefix build/, $(TEXT_FILES))

.DEFAULT_GOAL := all

.PHONY: all
all: compile doc

.PHONY: run
run: compile
	./username

.PHONY: compile
compile: username $(TEXT_FILES_DEST)

username: build/main
	cp $< $@

build/main: $(OBJECTS)
	mkdir -p $(@D)
	$(CXX) $^ -o $@

build/%.o: src/%.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $< -c -o $@

build/%.txt: assets/%.txt
	mkdir -p $(@D)
	cp $< $@

debug/%.test: tests/%.test.cpp $(filter-out build/main.o,$(OBJECTS))
	mkdir -p $(@D)
	g++ $(CXXFLAGS) $< $(filter-out build/main.o,$(OBJECTS)) -I src/ -o $@

.PHONY: doc
doc: Doxyfile $(HEADERS)
	doxygen Doxyfile
	mv doc/html/* doc/
	rm -rf html doc/html
	

Doxyfile:
	doxygen -g Doxyfile

build:
	mkdir -p $@
	
.PHONY: clean
clean:
	rm -rf username debug/ build/ doc/ debug/ 2>/dev/null

.PHONY: test_all
test_all: $(TESTS:tests/%.test.cpp=debug/%.test)
	for TEST in debug/*.test; do ./$$TEST; done

CBinaryExport.o: src/CBinaryExport.cpp src/CBinaryExport.h src/CExport.h \
 src/CParser.h src/CCell.h src/../libs/tabulate.hpp
CCell.o: src/CCell.cpp src/CCell.h
CExport.o: src/CExport.cpp src/CExport.h src/CParser.h src/CCell.h \
 src/../libs/tabulate.hpp src/CInterface.h
CImport.o: src/CImport.cpp src/CImport.h src/CCell.h src/CString.h \
 src/CNum.h
CInterface.o: src/CInterface.cpp src/CInterface.h src/CCell.h \
 src/../libs/tabulate.hpp src/CString.h
CNum.o: src/CNum.cpp src/CNum.h src/CCell.h
CParser.o: src/CParser.cpp src/CParser.h src/CCell.h src/CToken.h \
 src/CString.h src/CInterface.h src/../libs/tabulate.hpp \
 src/CStringToken.h src/CImport.h src/CNum.h src/CExport.h \
 src/CBinaryExport.h src/CTextExport.h
CString.o: src/CString.cpp src/CString.h src/CCell.h
CStringToken.o: src/CStringToken.cpp src/CStringToken.h src/CCell.h
CTextExport.o: src/CTextExport.cpp src/CTextExport.h src/CExport.h \
 src/CParser.h src/CCell.h src/../libs/tabulate.hpp
CToken.o: src/CToken.cpp src/CToken.h src/CCell.h
main.o: src/main.cpp src/CParser.h src/CCell.h

debug/CNum.test.o: tests/CNum.test.cpp src/CNum.cpp src/CNum.h src/CCell.h
debug/CParser.test.o: tests/CParser.test.cpp src/CParser.cpp src/CParser.h src/CCell.h src/CToken.h \
 src/CString.h src/CInterface.h src/../libs/tabulate.hpp \
 src/CStringToken.h src/CImport.h src/CNum.h src/CExport.h \
 src/CBinaryExport.h src/CTextExport.h
debug/CString.test.o: tests/CString.test.cpp src/CString.cpp src/CString.h src/CCell.h

