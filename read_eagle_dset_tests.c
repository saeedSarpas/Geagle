/*
 * read_eagle_dset_tests.c
 */


#include <cgreen/cgreen.h>
#include "./read_eagle_dset.h"
#include "./open_eagle.h"


#define EAGLE_PATH "./snapshot/eagle_snap.0.hdf5"
#define EAGLE_1D_DSET "PartType4/ElementAbundance/Hydrogen"
#define EAGLE_1D_DSET_LEN 1197
#define EAGLE_3D_DSET "PartType4/Coordinates"
#define EAGLE_3D_DSET_LEN (1197 * 3)


hid_t file_id;


Describe(read_eagle_dset);


BeforeEach(read_eagle_dset)
{
  herr_t h5err;

  h5err = H5open();
  if (h5err < 0)
    printf("[FATAL ERROR] Unable to initialize HDF5");

  file_id = H5Fopen(EAGLE_PATH, H5F_ACC_RDONLY, H5P_DEFAULT);
  if (file_id < 0)
    printf("[FATAL ERROR] Unable to open EAGLE snapshot: %s", EAGLE_PATH);
};


AfterEach(read_eagle_dset)
{
  herr_t h5err;

  h5err = H5Fclose(file_id);
  if (h5err < 0)
    printf("[FATAL ERROR] Unable to close EAGLE snapshot: %s", EAGLE_PATH);

  h5err = H5close();
  if (h5err < 0)
    printf("[FATAL ERROR] Unable to close HDF5");
};


Ensure(read_eagle_dset, reads_eagle_1d_dataset)
{
  eagle_dset_info_t dset_info;
  float buf[EAGLE_1D_DSET_LEN];
  dset_info.aexp_scale_exponent = 1.23456789;
  dset_info.h_scale_exponent = 1.23456789;

  assert_that(
    read_eagle_dset(file_id, EAGLE_1D_DSET, H5T_NATIVE_FLOAT, buf, &dset_info),
    is_equal_to(EXIT_SUCCESS));

  hid_t dset_id, dspace, mspace;
  hsize_t start[1] = {0}, count[1] = {1}, dimsm[1] = {EAGLE_1D_DSET_LEN};
  float value[0];

  for (int i = 0; i < EAGLE_1D_DSET_LEN; i += 17)
    {
      start[0] = i; /* Offset from the begining of the dataset */

      dset_id = H5Dopen(file_id, EAGLE_1D_DSET, H5P_DEFAULT);

      dspace = H5Dget_space(dset_id);
      H5Sselect_hyperslab(dspace, H5S_SELECT_SET, start , NULL, count, NULL);

      mspace = H5Screate_simple(1, dimsm, NULL);

      start[0] = 0; /* Offset from dspace */
      H5Sselect_hyperslab(mspace, H5S_SELECT_SET, start, NULL, count, NULL);

      H5Dread(dset_id, H5T_NATIVE_FLOAT, mspace, dspace, H5P_DEFAULT, value);

      assert_that_double(buf[i], is_equal_to_double(value[0]));

      H5Sselect_none(mspace);
      H5Sselect_none(dspace);

      H5Dclose(dset_id);
    }

  assert_that_double(dset_info.CGSConversionFactor, is_equal_to_double(1.0));

  assert_that(
    dset_info.VarDescription,
    is_equal_to_string("Mass fractions of chemical elements"));

  assert_that_double(dset_info.aexp_scale_exponent, is_equal_to_double(0.0));
  assert_that_double(dset_info.h_scale_exponent, is_equal_to_double(0.0));
}


Ensure(read_eagle_dset, reads_eagle_3d_dataset)
{
  eagle_dset_info_t dset_info;
  double buf[EAGLE_3D_DSET_LEN];
  dset_info.aexp_scale_exponent = 1.23456789;
  dset_info.h_scale_exponent = 1.23456789;

  assert_that(
    read_eagle_dset(file_id, EAGLE_3D_DSET, H5T_NATIVE_DOUBLE, buf, &dset_info),
    is_equal_to(EXIT_SUCCESS));

  assert_that_double(buf[0], is_equal_to_double(0.1309898));
  assert_that_double(buf[1], is_equal_to_double(0.2445513));
  assert_that_double(buf[2], is_equal_to_double(0.7794424));
  assert_that_double(
    buf[(EAGLE_1D_DSET_LEN - 1) * 3],
    is_equal_to_double(0.01394812));
  assert_that_double(
    buf[(EAGLE_1D_DSET_LEN - 1) * 3 + 1],
    is_equal_to_double(6.1587688));
  assert_that_double(
    buf[(EAGLE_1D_DSET_LEN - 1) *3 + 2],
    is_equal_to_double(0.73207015));

  assert_that_double(
    dset_info.CGSConversionFactor,
    is_equal_to_double(3.085678E24));

  assert_that(
    dset_info.VarDescription,
    is_equal_to_string("Co-moving coordinates. Physical: r = a x = Coordinates h^-1 a U_L [cm]"));

  assert_that_double(dset_info.aexp_scale_exponent, is_equal_to_double(1.0));
  assert_that_double(dset_info.h_scale_exponent, is_equal_to_double(-1.0));
}
