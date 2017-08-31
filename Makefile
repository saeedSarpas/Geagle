MODULE_NAME := Geagle

_CSRC := init_eagle.c \
         read_eagle_dset.c

_TSRC := init_eagle_tests.c \
         read_eagle_dset_tests.c

_FSRC := eagle_types_f.f90 \
         Geagle.f90

_CLIBS := -lHigh5 -lhdf5

_FLIBS := -I /scratch/saeed/.local/include

include ./Makefile.paCage/Makefile
