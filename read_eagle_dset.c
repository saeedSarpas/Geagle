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
#include <High5/High5.h>
#include "./read_eagle_dset.h"


#ifndef PRINT
#define PRINT printf
#endif


int read_eagle_dset(hid_t file_id, char *dset_name, hid_t dtype_id,
                    void *buf, eagle_dset_info_t *dset_info)
{
  if (read_h5dset(file_id, dset_name, dtype_id, buf) == EXIT_FAILURE)
    {
      PRINT("[ERROR] Unable to read EAGLE dataset: %s\n", dset_name);
      return EXIT_FAILURE;
    }

  if (dset_info == NULL)
    return EXIT_SUCCESS;

  if (read_h5dattrs(
        file_id, dset_name,
        "CGSConversionFactor", H5T_NATIVE_DOUBLE, &(dset_info->CGSConversionFactor),
        "VarDescription", H5T_STRING, dset_info->VarDescription,
        "aexp-scale-exponent", H5T_NATIVE_FLOAT, &(dset_info->aexp_scale_exponent),
        "h-scale-exponent", H5T_NATIVE_FLOAT, &(dset_info->h_scale_exponent),
        NULL
      ) == EXIT_FAILURE)
    {
      PRINT("[ERROR] Unable to read attributes of EAGLE datasaet: %s\n",
            dset_name);
      return EXIT_FAILURE;
    }

  return EXIT_SUCCESS;
}
