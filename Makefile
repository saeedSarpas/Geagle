MODULE_NAME := Geagle

MAJOR := 0
MINOR := 0
PATCH := 0


OBJS := init_eagle.o \
        read_eagle_dset.o \
        init_hash.o \
        peano_hilbert_key.o \
        crop_eagle.o \
        count_particles.o \
				eagle_types_f.o \
				Geagle.o


TEST_OBJS := init_eagle_tests.o \
             read_eagle_dset_tests.o \
             init_hash_tests.o \
             crop_eagle_tests.o \
             count_particles_tests.o


LIBS := -I ~/.local/include -L ~/.local/lib -lhdf5
paCages := High5


include ./Makefile.paCage/Makefile
