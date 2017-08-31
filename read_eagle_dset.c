/*
 * read_eagle_dset.c
 * tests_file: read_eagle_dset_tests.c
 *
 * Read an EAGLE dataset
 *
 * @param: file_id: File identifier (should be opened beforehand)
 * @param: dset_name: Path to the dataset
 * @param: dtype_id: Data type identifier
 * @param: buf: Pointer to the allocated space for loading the dataset
 * @param: dset_info: Pointer to the argument of type eagle_dset_info
 *
 * @return: EXIT_FAILURE or EXIT_SUCCESS
 */


#include <stdlib.h>
#include <string.h>
#include <High5/High5.h>
#include "./read_eagle_dset.h"


#ifndef PRINT
#define PRINT printf
#endif


int read_eagle_dset(char* file_path_fmt, enum _PTypes p_type, char *dset_name,
                    hid_t dtype_id, void *buf, eagle_dset_info_t *dset_info)
{
  if(strstr(file_path_fmt, "%d") == NULL) {
    printf("[Warning] Please use a formatted file path.\n");
    printf("          e.g. /path/to/eagle/snap.%%d.h5\n");
    return EXIT_FAILURE;
  }

  char file_path[1024], dset_path[1024];
  sprintf(file_path, file_path_fmt, 0);
  sprintf(dset_path, "PartType%d/%s", p_type, dset_name);

  hsize_t dims[32]; /* 32: Current limit for datasets dimension*/
  int num_files;

  hid_t file_id = open_h5(file_path, H5F_ACC_RDONLY, H5P_DEFAULT);
  read_h5attr(file_id, "Header", "NumFilesPerSnapshot", H5T_NATIVE_INT, &num_files);
  close_h5(file_id);

  int ndims, offset = 0;

  for(int i = 0; i < num_files; i++)
    {
      sprintf(file_path, file_path_fmt, i);
      file_id = open_h5(file_path, H5F_ACC_RDONLY, H5P_DEFAULT);

      buf = (char*)buf + H5Tget_size(dtype_id) * offset;

      get_h5dset_dims(file_id, dset_path, &ndims, dims);
      offset = 1;
      for(int j = 0; j < ndims; j++)
        offset *= (int)dims[j];

      if(read_h5dset(file_id, dset_path, dtype_id, buf) == EXIT_FAILURE)
        {
          PRINT("[ERROR] Unable to read EAGLE dataset: %s\n", dset_path);
          close_h5(file_id);
          return EXIT_FAILURE;
        }

      if(dset_info != NULL && i == (num_files - 1))
        {
          if(
            read_h5dattrs(
              file_id, dset_path,
              "CGSConversionFactor", H5T_NATIVE_DOUBLE, &(dset_info->CGSConversionFactor),
              "VarDescription", H5T_STRING, dset_info->VarDescription,
              "aexp-scale-exponent", H5T_NATIVE_FLOAT, &(dset_info->aexp_scale_exponent),
              "h-scale-exponent", H5T_NATIVE_FLOAT, &(dset_info->h_scale_exponent),
              NULL
            ) == EXIT_FAILURE)
            {
              PRINT("[ERROR] Unable to read attributes of EAGLE datasaet: %s\n",
                    dset_path);
              close_h5(file_id);
              return EXIT_FAILURE;
            }
        }

      if(close_h5(file_id) < 0)
        {
          PRINT("[ERROR] Unable to close EAGLE snap: %s\n", file_path);
          close_h5(file_id);
          return EXIT_FAILURE;
        }
    }

  return EXIT_SUCCESS;
}
