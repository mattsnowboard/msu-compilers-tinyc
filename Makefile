SRCS := functions.cpp SymbolTable.cpp AssemblyVisitor.cpp FunctionTable.cpp
OBJS := $(SRCS:%.cpp=%.o)

CXXFLAGS = -Wall -g

DEPDIR = .deps
df = $(DEPDIR)/$(@F)

MAKEDEPEND = $(CXX) $(CPPFLAGS) -MM -o $(df).d $<


# Special make rule to keep intermediate files *.s and *.o
# Comment out this line to have "cleaner" builds
.SECONDARY:

all:	test	

# Generate and run all test files
test:	tinyc
	chmod +x run_tests.sh
	./run_tests.sh

# Build our tiny Compiler using bison and flex files
#	$@	target name
#	$^	source files
#
tinyc:		$(OBJS) tinyc.o y.tab.o lex.yy.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o $@

tinyc.o: tinyc.cpp y.tab.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c tinyc.cpp

# Bison options:
#	-v	Generate micro.output showing states of LALR parser
#	-d	Generate micro.tab.h containing token type definitions
#	$^	source files
#
y.tab.h y.tab.c:	tinyc.y
	bison --yacc -v -d $^  --report=state

# bison --yacc --defines expression.y --report=state

y.tab.o: y.tab.c y.tab.h
	gcc -c y.tab.c

# Build flex
lex.yy.c: tinyc.l y.tab.h
	flex tinyc.l

lex.yy.o: lex.yy.c
	gcc -c lex.yy.c


########################################
# The following build rules use your compiler to build object files
#
# Requires tinyc source code:
#	filename.tc
#
# Usage:
#    make filename
########################################

# Use tinyc command to make assembly file *.s from *.tc files
#       %.s     Generic build rule for any assembly file basename
#       $@      target name
#       $<      first source files
%.s: %.tc tinyc
	./tinyc < $< > $@

# Convert assembly file *.s to object file *.o using gnu assembler (as)
#       %.o     Generic build rule for any object file basename
#       $@      target name
#       $<      first source files
%.o:    %.s
	as --32 $< -o $@

# Link Object file *.o to make executable
#	%	Generic build rule for any file basename
#	$@	target name
#	$^	source files
%:	%.o 
	ld -m elf_i386 $< -o $@ 


#
# Auto dependency stuff
#
.D_TARGET:
	mkdir -p $(DEPDIR)
	touch $@

.PRECIOUS: .D_TARGET

# my other sources

%.o : %.cpp .D_TARGET
	$(MAKEDEPEND);
	@cp $(df).d $(df).P;
	@rm -f $(df).d
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ -c $<

-include $(SRCS:%.cpp=$(DEPDIR)/%.o.P)

# clean

clean: 
	$(RM) -f *.o *.s *.output t3? t2? t1? t? lex.yy.c y.tab.[hc] tinyc \
		.D_TARGET *.log
	$(RM) -rf $(DEPDIR)
