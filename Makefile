# Set compiler.
# CC=gcc
CXX:=g++

# Set flags.
# CFLAGS=
CXXFLAGS:=-Wall -O3 -std=c++23
DEPFLAGS:=-MD -MP # Autogenerate dependencies.
# CPPFLAGS:=
# LDFLAGS:=
# INCLUDES:=

# Directories.
BUILDDIR:=build
SRCDIR:=examples
OBJDIR:=$(BUILDDIR)/obj

# Files.
DEPS:=$(subst $(SRCDIR),$(OBJDIR),$(SRCS:%.cpp=%.d))

#
# Executables.
#
TEST_VECTOR_OBS:=$(OBJDIR)/test_vector.o
TEST_VECTOR:=$(BUILDDIR)/test_vector

TEST_SEGMENTED_VECTOR_OBS:=$(OBJDIR)/test_segmented_vector.o
TEST_SEGMENTED_VECTOR:=$(BUILDDIR)/test_segmented_vector

TEST_GROWING_ALLOCATOR_OBS:=$(OBJDIR)/test_growing_allocator.o
TEST_GROWING_ALLOCATOR:=$(BUILDDIR)/test_growing_allocator

#
# Generate executables
#
TESTS:=$(TEST_VECTOR) $(TEST_SEGMENTED_VECTOR) $(TEST_GROWING_ALLOCATOR)

# Generic link rule for all binaries in $(BUILDDIR)
$(BUILDDIR)/%: $(OBJDIR)/%.o
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o $@

#
# Generate objects.
#
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	mkdir -p $(@D)
	$(CXX) $(INCLUDES) $(DEPFLAGS) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

# Include dependencies.
-include $(DEPS)

# The default goal is the next goal.
.DEFAULT_GOAL:=
.PHONY: all
all: main

main: $(TESTS)

.PHONY: clean
clean:
	rm -rf $(BUILDDIR)/*