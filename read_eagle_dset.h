#ifndef _READ_EAGLE_DSET_H_
#define _READ_EAGLE_DSET_H_


#include <hdf5.h>
#include "./eagle_types.h"


int read_eagle_dset(hid_t, char*, hid_t, void*, eagle_dset_info_t*);


#endif /* _READ_EAGLE_DSET_H_ */
