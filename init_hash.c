/*
 * init_hash.c
 * tests_file: init_hash_tests.c
 *
 * Loading hashtable into hash struct
 *
 * @param: file_path_fmt: Formatted file path, e.g. /path/to/snap.%d.h5
 * @param: nfiles: Number of hdf5 files per snapshot
 * @param: hash: The hash struct to be filled
 *
 * @return: Standard EXIT_SUCCESS (EXIT_FAILURE on errors)
 */


#include <stdlib.h>
#include <string.h>
#include <High5/High5.h>
#include "./init_hash.h"


int init_hash(char *fmt_path, eagle_hash_t *hash)
{
  if(strstr(fmt_path, "%d") == NULL) {
    printf("[Warning] Please use a formatted file path.\n");
    printf("          e.g. /path/to/eagle/snap.%%d.h5\n");
    return EXIT_FAILURE;
  }

  char path[1024], FirstKey[128], LastKey[128], NumKeys[128], NumParticles[128];
  int ndims, nfiles;
  hsize_t dims[32];


  sprintf(path, fmt_path, 0);
  hid_t file_id = open_h5(path, H5F_ACC_RDONLY, H5P_DEFAULT);

  read_h5attr(file_id, "HashTable", "HashBits", H5T_NATIVE_INT, &(hash->bits));
  read_h5attr(file_id, "Header", "NumFilesPerSnapshot", H5T_NATIVE_INT, &nfiles);
  hash->map_len = 1 << (3 * hash->bits);
  hash->map = calloc(hash->map_len, sizeof(int));

  for(int ptype = 0; ptype < 6; ptype++)
    {
      if(ptype == 2 || ptype == 3) continue;

      sprintf(FirstKey, "/HashTable/PartType%d/FirstKeyInFile", ptype);
      sprintf(LastKey, "/HashTable/PartType%d/LastKeyInFile", ptype);
      sprintf(NumKeys, "/HashTable/PartType%d/NumKeysInFile", ptype);

      hash->table[ptype].FirstKeyInFile = calloc(nfiles, sizeof(int));
      hash->table[ptype].LastKeyInFile = calloc(nfiles, sizeof(int));
      hash->table[ptype].NumKeysInFile = calloc(nfiles, sizeof(int));

      read_h5dset(file_id, FirstKey, H5T_NATIVE_INT, hash->table[ptype].FirstKeyInFile);
      read_h5dset(file_id, LastKey, H5T_NATIVE_INT, hash->table[ptype].LastKeyInFile);
      read_h5dset(file_id, NumKeys, H5T_NATIVE_INT, hash->table[ptype].NumKeysInFile);

      hash->table[ptype].NumParticleInCell = malloc(nfiles * sizeof(int*));
    }

  close_h5(file_id);


  for(int ifile = 0; ifile < nfiles; ifile++)
    {
      sprintf(path, fmt_path, ifile);
      file_id = open_h5(path, H5F_ACC_RDONLY, H5P_DEFAULT);

      for(int ptype = 0; ptype < 6; ptype++)
        {
          if(ptype == 2 || ptype == 3) continue;

          sprintf(NumParticles, "/HashTable/PartType%d/NumParticleInCell", ptype);

          get_h5dset_dims(file_id, NumParticles, &ndims, dims);
          hash->table[ptype].NumParticleInCell[ifile] = calloc(dims[0], sizeof(int));

          read_h5dset(file_id, NumParticles, H5T_NATIVE_INT,
                      hash->table[ptype].NumParticleInCell[ifile]);
        }

      close_h5(file_id);
    }

  return EXIT_SUCCESS;
}
