# Main names.
CAESAR_F = caesar_f # fast version
CAESAR_D = caesar_d # debug version
CAESAR_T = caesar_t # test version
CAESAR_P = caesar_p # profile version

#-------------------------------------------------------------------------------

# Compiler and linker.
COMPILER = mpicxx
LINKER = mpicxx

#-------------------------------------------------------------------------------

# Make options.
FLAGS = -MMD -MP -fopenmp \
        -Werror -pedantic-errors -Wall -Wextra -Wpedantic \
        -Wcast-align -Wcast-qual -Wconversion -Wctor-dtor-privacy \
        -Wfloat-equal -Wlogical-op -Wnon-virtual-dtor \
        -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wsign-conversion -Wsign-promo
FLAGS_F = $(FLAGS) -std=c++11 -O3
FLAGS_D = $(FLAGS) -std=c++11 -DDEBUG
# Catch2 v3 requires c++ 14.
FLAGS_T = $(FLAGS) -std=c++14
FLAGS_P = $(FLAGS) -std=c++11 -pg

#-------------------------------------------------------------------------------

# Includes.
INCLUDES = -Isrc

#-------------------------------------------------------------------------------

# Files.
SOURCES = $(shell find src -type f -name "*.cpp")
TESTS_SOURCES = $(shell find test/unit_catch2 -type f -name "*.cpp")
SOURCES_F = $(SOURCES)
SOURCES_D = $(SOURCES)
SOURCES_T = $(filter-out src/caesar.cpp, $(SOURCES)) $(TESTS_SOURCES)
SOURCES_P = $(SOURCES)

#-------------------------------------------------------------------------------

# Objects.
OBJS_F = $(SOURCES_F:.cpp=_f.o)
OBJS_D = $(SOURCES_D:.cpp=_d.o)
OBJS_T = $(SOURCES_T:.cpp=_t.o)
OBJS_P = $(SOURCES_P:.cpp=_p.o)
ALL_OBJS = $(OBJS_F) $(OBJS_D) $(OBJS_T) $(OBJS_P)

#-------------------------------------------------------------------------------

# Dependencies.
DEPS_F = $(SOURCES_F:.cpp=_f.d)
DEPS_D = $(SOURCES_D:.cpp=_d.d)
DEPS_T = $(SOURCES_T:.cpp=_t.d)
DEPS_P = $(SOURCES_P:.cpp=_p.d)
ALL_DEPS = $(DEPS_F) $(DEPS_D) $(DEPS_T) $(DEPS_P)

#-------------------------------------------------------------------------------

# Libraries.
LIBS = -lm -fopenmp
LIBS_F = $(LIBS)
LIBS_D = $(LIBS)
LIBS_T = $(LIBS) -lCatch2Main -lCatch2
LIBS_P = $(LIBS)

#-------------------------------------------------------------------------------

# Build all targets.
.PHONY : all
all : fast debug test profile

#-------------------------------------------------------------------------------

# Build fast version.
.PHONY : fast
fast : $(CAESAR_F)

# Build debug version.
.PHONY : debug
debug : $(CAESAR_D)

# Build test version.
.PHONY : test
test : $(CAESAR_T)

# Build profile version.
.PHONY : profile
profile : $(CAESAR_P)

#-------------------------------------------------------------------------------

# Build fast version.
$(CAESAR_F) : $(OBJS_F)
	$(LINKER) $^ $(LIBS_F) -o $@

# Build fast version.
$(CAESAR_D) : $(OBJS_D)
	$(LINKER) $^ $(LIBS_D) -o $@

# Build fast version.
$(CAESAR_T) : $(OBJS_T)
	$(LINKER) $^ $(LIBS_T) -o $@

# Build fast version.
$(CAESAR_P) : $(OBJS_P)
	$(LINKER) $^ $(LIBS_P) -pg -o $@

#-------------------------------------------------------------------------------

# Build fast sources.
%_f.o : %.cpp
	$(COMPILER) $(FLAGS_F) $(INCLUDES) -c $< -o $@

# Build debug sources.
%_d.o : %.cpp
	$(COMPILER) $(FLAGS_D) $(INCLUDES) -c $< -o $@

# Build test sources.
%_t.o : %.cpp
	$(COMPILER) $(FLAGS_T) $(INCLUDES) -c $< -o $@

# Build profile sources.
%_p.o : %.cpp
	$(COMPILER) $(FLAGS_P) $(INCLUDES) -c $< -o $@

#-------------------------------------------------------------------------------

# Clean.
.PHONY : clean
clean :
	rm -f $(ALL_OBJS) $(ALL_DEPS)

#-------------------------------------------------------------------------------
