Common variable meaning.(for more http://www.gnu.org/software/make/manual/make.html#Using-Implicit)

AR
Archive-maintaining program; default ‘ar’.

CC
Program for compiling C programs; default ‘cc’.

CXX
Program for compiling C++ programs; default ‘g++’.

CPP
Program for running the C preprocessor, with results to standard output; default ‘$(CC) -E’.

CFLAGS
Extra flags to give to the C compiler.

CXXFLAGS
Extra flags to give to the C++ compiler.

CPPFLAGS
Extra flags to give to the C preprocessor and programs that use it (the C and Fortran compilers).

LDFLAGS
Extra flags to give to compilers when they are supposed to invoke the linker, ‘ld’, such as -L. Libraries (-lfoo) should be added to the LDLIBS variable instead.