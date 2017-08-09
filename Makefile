MODULE_NAME := eagle

_FILES := open_eagle.c

_TESTS := open_eagle_tests.c

_FSRC := eagle_types_f.f90 \
         eagle.f90

_LIBS := -lHigh5 -lhdf5
_FORT_LIBS :=

include ./Makefile.paCage/Makefile
