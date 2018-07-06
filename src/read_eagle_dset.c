/*
 * read_eagle_dset.c
 * tests_file: read_eagle_dset_tests.c
 *
 * Read an EAGLE dataset
 *
 * @param: fmt_path: Formatted snapshot path
 * @param: ptype: Particle type
 * @param: dset_name:
 * @param: dtype_id: Data type identifier
 * @param: buf: Pointer to the allocated space for loading the dataset
 * @param: dset_info: Pointer to the argument of type eagle_dset_info
 * @param: hash: Pointer to a hash object (NULL to ignore)
 *
 * @return: EXIT_FAILURE or EXIT_SUCCESS
 *
 * TODO: to be refactored
 */


#include <stdlib.h>
#include <string.h>
#include <High5/High5.h>
#include "./read_eagle_dset.h"
#include "./init_hash.h"


#define MAXDIM (2)  /* Maximum availabl: 32 */

#ifndef PRINT
#define PRINT printf
#endif


int read_eagle_dset(char* fmt_path, enum _PTypes ptype, char *dset_name,
                    hid_t dtype_id, void *buf, eagle_dset_info_t *dset_info,
                    eagle_hash_t *hash)
{
  if(strstr(fmt_path, "%d") == NULL) {
    printf("[Warning] Please use a formatted file path.\n");
    printf("          e.g. /path/to/eagle/snap.%%d.h5\n");
    return EXIT_FAILURE;
  }

  char path[1024], dset_path[1024];
  sprintf(path, fmt_path, 0);
  sprintf(dset_path, "PartType%d/%s", ptype, dset_name);

  int num_files;
  hid_t fid = open_h5(path, H5F_ACC_RDONLY, H5P_DEFAULT);
  read_h5attr(fid, "Header", "NumFilesPerSnapshot", H5T_NATIVE_INT, &num_files);
  close_h5(fid);

  hsize_t dims[MAXDIM];
  int ndims, buf_offset = 0;

  hsize_t start[MAXDIM], count[MAXDIM];

  for(int ifile = 0; ifile < num_files; ifile++)
    {
      sprintf(path, fmt_path, ifile);
      fid = open_h5(path, H5F_ACC_RDONLY, H5P_DEFAULT);

      get_h5dset_dims(fid, dset_path, &ndims, dims);

      for(int i = 1; i < ndims; i++)
        {
          count[i] = dims[i];
          start[i] = 0;
        }

      if(hash == NULL)
        {
          buf = (char*)buf + H5Tget_size(dtype_id) * buf_offset;

          read_h5dset(fid, dset_path, dtype_id, buf);

          buf_offset = 1;
          for(int j = 0; j < ndims; j++)
            buf_offset *= (int)dims[j];
        }
      else
        {
          count[0] = 0;
          start[0] = 0;

          for(long long key = hash->table[ptype].FirstKeyInFile[ifile];
              key <= hash->table[ptype].LastKeyInFile[ifile]; key++)
            {
              buf = (char*)buf + H5Tget_size(dtype_id) * buf_offset;

              while(key <= hash->table[ptype].LastKeyInFile[ifile] && !hash->map[key])
                  key++;

              start[0] = hash->table[ptype].FirstParticleInCell[ifile][
                key - hash->table[ptype].FirstKeyInFile[ifile]
              ];

              while(key <= hash->table[ptype].LastKeyInFile[ifile] && hash->map[key])
                {
                  count[0] += hash->table[ptype].NumParticleInCell[ifile][
                    key - hash->table[ptype].FirstKeyInFile[ifile]
                  ];
                  key++;
                }
              key--; /* for loop will increment key */

              buf_offset = count[0];
              for(int i = 1; i < ndims; i++)
                buf_offset *= (int)dims[i];

              if(count[0] > 0)
                read_h5dset_part(fid, dset_path, dtype_id, start, count, buf);

              start[0] += count[0];
              count[0] = 0;
            }
        }

      if(ifile == (num_files - 1) && dset_info != NULL)
        read_h5dattrs(
          fid, dset_path,
          "CGSConversionFactor", H5T_NATIVE_DOUBLE, &(dset_info->CGSConversionFactor), optional_attr,
          "VarDescription", H5T_STRING, dset_info->VarDescription, optional_attr,
          "aexp-scale-exponent", H5T_NATIVE_FLOAT, &(dset_info->aexp_scale_exponent), optional_attr,
          "h-scale-exponent", H5T_NATIVE_FLOAT, &(dset_info->h_scale_exponent), optional_attr,
          NULL
        );

      close_h5(fid);
    }

  return EXIT_SUCCESS;
}
