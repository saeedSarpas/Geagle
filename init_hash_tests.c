/*
 * init_hash_tests.c
 */


#include <cgreen/cgreen.h>
#include <assert.h>
#include "./init_hash.h"


#define SNAP_PATH "./snapshot/eagle_snap.%d.hdf5"
#define NFILE (16)


static int get(hid_t, char*, int);


Describe(init_hash);


BeforeEach(init_hash) {};
AfterEach(init_hash) {};


Ensure(init_hash, works_properly)
{
  eagle_hash_t hash;
  init_hash(SNAP_PATH, &hash);

  assert_that(hash.bits, is_equal_to(6));
  assert_that(hash.map_len, is_equal_to((1 << (3 * 6))));

  char path[128], FirstKey[128], LastKey[128], NumKeys[128], NumParticles[128];
  hid_t file_id;
  int num_keys;

  H5open();

  for(int ifile = 0; ifile < NFILE; ifile++)
    {
      sprintf(path, SNAP_PATH, ifile);
      file_id = H5Fopen(path, H5F_ACC_RDONLY, H5P_DEFAULT);
      assert(file_id >= 0);

      for(int ptype = 0; ptype < 6; ptype++)
        {
          if(ptype == 2 || ptype == 3) continue;

          sprintf(FirstKey, "/HashTable/PartType%d/FirstKeyInFile", ptype);
          sprintf(LastKey, "/HashTable/PartType%d/LastKeyInFile", ptype);
          sprintf(NumKeys, "/HashTable/PartType%d/NumKeysInFile", ptype);
          sprintf(NumParticles, "/HashTable/PartType%d/NumParticleInCell", ptype);

          for(int i = 0; i <= NFILE; i += 7)
            {
              assert_that(hash.table[ptype].FirstKeyInFile[i],
                          is_equal_to(get(file_id, FirstKey, i)));
              assert_that(hash.table[ptype].LastKeyInFile[i],
                          is_equal_to(get(file_id, LastKey, i)));
              assert_that(hash.table[ptype].NumKeysInFile[i],
                          is_equal_to(get(file_id, NumKeys, i)));
            }

          num_keys = hash.table[ptype].NumKeysInFile[ifile];

          for(int i = 0; i < num_keys; i += num_keys / 5 + 1)
            {
              assert_that(hash.table[ptype].NumParticleInCell[ifile][i],
                          is_equal_to(get(file_id, NumParticles, i)));
            }
        }

      H5Fclose(file_id);
    }
}


static int get(hid_t file_id, char *dset, int index)
{
  hid_t dset_id, dspace, mspace;
  hsize_t start[1] = {0}, count[1] = {1}, dimsm[1] = {NFILE};
  int value;

  dset_id = H5Dopen(file_id, dset, H5P_DEFAULT);

  dspace = H5Dget_space(dset_id);

  start[0] = index;
  H5Sselect_hyperslab(dspace, H5S_SELECT_SET, start , NULL, count, NULL);

  mspace = H5Screate_simple(1, dimsm, NULL);

  start[0] = 0;
  H5Sselect_hyperslab(mspace, H5S_SELECT_SET, start, NULL, count, NULL);

  H5Dread(dset_id, H5T_NATIVE_INT, mspace, dspace, H5P_DEFAULT, &value);

  H5Dclose(dset_id);

  return value;
}
