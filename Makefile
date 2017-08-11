MODULE_NAME := Geagle

_CSRC := open_eagle.c

_TSRC := open_eagle_tests.c

_FSRC := eagle_types_f.f90 \
         Geagle.f90

_CLIBS := -lHigh5 -lhdf5

_FLIBS :=

include ./Makefile.paCage/Makefile
