.DEFAULT_GOAL := all
MAKEFLAGS     += --no-builtin-rules
SHELL         := bash

ASTYLE        := astyle
CHECKTESTDATA := checktestdata
CPPCHECK      := cppcheck
DOXYGEN       := doxygen
VALGRIND      := valgrind

ifeq ($(shell uname -s), Darwin)
    BOOST    := /usr/local/include/boost
    CXX      := g++-10
    CXXFLAGS := --coverage -pedantic -std=c++17 -O3 -I/usr/local/include -Wall -Wextra
    GCOV     := gcov-10
    GTEST    := /usr/local/include/gtest
    LDFLAGS  := -lgtest -lgtest_main
else ifeq ($(shell uname -p), unknown)
    BOOST    := /usr/include/boost
    CXX      := g++
    CXXFLAGS := --coverage -pedantic -std=c++17 -O3 -Wall -Wextra
    GCOV     := gcov
    GTEST    := /usr/include/gtest
    LDFLAGS  := -lgtest -lgtest_main -pthread
else
    BOOST    := /usr/include/boost
    CXX      := g++-9
    CXXFLAGS := --coverage -pedantic -std=c++17 -O3 -Wall -Wextra
    GCOV     := gcov-9
    GTEST    := /usr/local/include/gtest
    LDFLAGS  := -lgtest -lgtest_main -pthread
endif

# run docker
docker:
	docker run -it -v $(PWD):/usr/gcc -w /usr/gcc gpdowning/gcc

# get git config
config:
	git config -l

# get git log
Collatz.log:
	git log > Collatz.log

# get git status
status:
	make clean
	@echo
	git branch
	git remote -v
	git status

# download files from the Collatz code repo
pull:
	make clean
	@echo
	git pull
	git status

# upload files to the Collatz code repo
push:
	make clean
	@echo
	git add .gitignore
	git add .gitlab-ci.yml
	git add Collatz.cpp
	git add Collatz.hpp
	-git add Collatz.log
	-git add html
	git add makefile
	git add README.md
	git add RunCollatz.cpp
	git add RunCollatz.ctd
	git add RunCollatz.in
	git add RunCollatz.out
	git add TestCollatz.cpp
	git commit -m "Updated README document"
	#git commit -m "Message" -m "Closes #14, #7"
	git push
	git status

# remove executables and temporary files
clean:
	rm -f *.gcda
	rm -f *.gcno
	rm -f *.gcov
	rm -f *.plist
	rm -f *.tmp
	rm -f RunCollatz
	rm -f TestCollatz

# remove executables, temporary files, and generated files
scrub:
	make clean
	rm -f  Collatz.log
	rm -f  Doxyfile
	rm -rf collatz-tests
	rm -rf html
	rm -rf latex

# compile run harness
RunCollatz: Collatz.hpp Collatz.cpp RunCollatz.cpp
	-$(CPPCHECK) Collatz.cpp
	-$(CPPCHECK) RunCollatz.cpp
	$(CXX) $(CXXFLAGS) Collatz.cpp RunCollatz.cpp -o RunCollatz

# compile test harness
TestCollatz: Collatz.hpp Collatz.cpp TestCollatz.cpp
	-$(CPPCHECK) Collatz.cpp
	-$(CPPCHECK) TestCollatz.cpp
	$(CXX) $(CXXFLAGS) Collatz.cpp TestCollatz.cpp -o TestCollatz $(LDFLAGS)

# run/test files, compile with make all
FILES :=                                  \
    RunCollatz                            \
    TestCollatz

# compile all
all: $(FILES)

# check integrity of input file
ctd-check:
	$(CHECKTESTDATA) RunCollatz.ctd RunCollatz.in

# generate a random input file
ctd-generate:
	$(CHECKTESTDATA) -g RunCollatz.ctd RunCollatz.tmp

# execute run harness and diff with expected output
run: ctd-check RunCollatz
	./RunCollatz < RunCollatz.in > RunCollatz.tmp
	-diff RunCollatz.tmp RunCollatz.out

# execute test harness
test: TestCollatz
	$(VALGRIND) ./TestCollatz
	$(GCOV) Collatz.cpp | grep -B 2 "cpp.gcov"

# clone the Collatz test repo
collatz-tests:
	git clone https://gitlab.com/gpdowning/cs371g-collatz-tests.git collatz-tests

# test files in the Collatz test repo
TFILES := `ls collatz-tests/*.in`

# execute run harness against a test in Collatz test repo and diff with expected output
collatz-tests/%: RunCollatz
	./RunCollatz < $@.in > RunCollatz.tmp
	-diff RunCollatz.tmp $@.out

# execute run harness against all tests in Collatz test repo and diff with expected output
tests: collatz-tests RunCollatz
	-for v in $(TFILES); do make $${v/.in/}; done

# auto format the code
format:
	$(ASTYLE) Collatz.cpp
	$(ASTYLE) Collatz.hpp
	$(ASTYLE) RunCollatz.cpp
	$(ASTYLE) TestCollatz.cpp

# you must edit Doxyfile and
# set EXTRACT_ALL     to YES
# set EXTRACT_PRIVATE to YES
# set EXTRACT_STATIC  to YES
# create Doxfile
Doxyfile:
	$(DOXYGEN) -g

# create html directory
html: Doxyfile Collatz.hpp
	$(DOXYGEN) Doxyfile

# check files, check their existence with make check
CFILES :=                                 \
    .gitignore                            \
    .gitlab-ci.yml                        \
    Collatz.log                           \
    html

# uncomment the following line once you've pushed your test files
# you must replace GitLabID with your GitLabID
#    collatz-tests/GitLabID-RunCollatz.in  \
#    collatz-tests/GitLabID-RunCollatz.out

# check the existence of check files
check: $(CFILES)

# output versions of all tools
versions:
	@echo "% shell uname -p"
	@echo  $(shell uname -p)
	@echo
	@echo "% shell uname -s"
	@echo  $(shell uname -s)
	@echo
	@echo "% which $(ASTYLE)"
	@which $(ASTYLE)
	@echo
	@echo "% $(ASTYLE) --version"
	@$(ASTYLE) --version
	@echo
	@echo "% grep \"#define BOOST_LIB_VERSION \" $(BOOST)/version.hpp"
	@grep "#define BOOST_LIB_VERSION " $(BOOST)/version.hpp
	@echo
	@echo "% which $(CHECKTESTDATA)"
	@which $(CHECKTESTDATA)
	@echo
	@echo "% $(CHECKTESTDATA) --version"
	@$(CHECKTESTDATA) --version
	@echo
	@echo "% which $(CXX)"
	@which $(CXX)
	@echo
	@echo "% $(CXX) --version"
	@$(CXX) --version
	@echo "% which $(CPPCHECK)"
	@which $(CPPCHECK)
	@echo
	@echo "% $(CPPCHECK) --version"
	@$(CPPCHECK) --version
	@echo
	@$(CXX) --version
	@echo "% which $(DOXYGEN)"
	@which $(DOXYGEN)
	@echo
	@echo "% $(DOXYGEN) --version"
	@$(DOXYGEN) --version
	@echo
	@echo "% which $(GCOV)"
	@which $(GCOV)
	@echo
	@echo "% $(GCOV) --version"
	@$(GCOV) --version
	@echo
	@echo "% cat $(GTEST)/README"
	@cat $(GTEST)/README
ifneq ($(shell uname -s), Darwin)
	@echo
	@echo "% which $(VALGRIND)"
	@which $(VALGRIND)
	@echo
	@echo "% $(VALGRIND) --version"
	@$(VALGRIND) --version
endif
