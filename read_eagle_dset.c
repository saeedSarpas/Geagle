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
  hid_t file_id = open_h5(path, H5F_ACC_RDONLY, H5P_DEFAULT);
  read_h5attr(file_id, "Header", "NumFilesPerSnapshot", H5T_NATIVE_INT, &num_files);
  close_h5(file_id);

  hsize_t dims[MAXDIM];
  int ndims, buf_offset = 0;

  hsize_t start[MAXDIM], count[MAXDIM];

  for(int ifile = 0; ifile < num_files; ifile++)
    {
      sprintf(path, fmt_path, ifile);
      file_id = open_h5(path, H5F_ACC_RDONLY, H5P_DEFAULT);

      buf = (char*)buf + H5Tget_size(dtype_id) * buf_offset;

      if(hash == NULL)
        {
          get_h5dset_dims(file_id, dset_path, &ndims, dims);

          buf_offset = 1;
          for(int j = 0; j < ndims; j++)
            buf_offset *= (int)dims[j];

          read_h5dset(file_id, dset_path, dtype_id, buf);
        }
      else
        {
          get_h5dset_dims(file_id, dset_path, &ndims, dims);

          count[0] = 0;
          start[0] = 0;

          for(int key = hash->table[ptype].FirstKeyInFile[ifile];
              key <= hash->table[ptype].LastKeyInFile[ifile]; key++)
            {
              if(!hash->map[key])
                {
                  start[0] += hash->table[ptype].NumParticleInCell[ifile][
                    key - hash->table[ptype].FirstKeyInFile[ifile]
                  ];
                  continue;
                }

              while(key <= hash->table[ptype].LastKeyInFile[ifile] && hash->map[key] == 1)
                {
                  count[0] += hash->table[ptype].NumParticleInCell[ifile][
                    key - hash->table[ptype].FirstKeyInFile[ifile]
                  ];
                  key++;
                }
            }

          buf_offset = count[0];
          for(int j = 1; j < ndims; j++)
            {
              buf_offset *= dims[j];
              start[j] = 0;
              count[j] = dims[j];
            }

          read_h5dset_part(file_id, dset_path, start, count, dtype_id, buf);
        }

      if(ifile == (num_files - 1) && dset_info != NULL)
        read_h5dattrs(
          file_id, dset_path,
          "CGSConversionFactor", H5T_NATIVE_DOUBLE, &(dset_info->CGSConversionFactor), optional_attr,
          "VarDescription", H5T_STRING, dset_info->VarDescription, optional_attr,
          "aexp-scale-exponent", H5T_NATIVE_FLOAT, &(dset_info->aexp_scale_exponent), optional_attr,
          "h-scale-exponent", H5T_NATIVE_FLOAT, &(dset_info->h_scale_exponent), optional_attr,
          NULL
        );

      close_h5(file_id);
    }

  return EXIT_SUCCESS;
}
