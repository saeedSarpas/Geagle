/*
 * read_eagle_dset_tests.c
 */


#include <cgreen/cgreen.h>
#include "./read_eagle_dset.h"
#include "./open_eagle.h"


#define EAGLE_PATH "./sample_eagle_output.hdf5"
#define EAGLE_1D_DSET "PartType4/SmoothedElementAbundance/Hydrogen"
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

  assert_that_double(buf[0], is_equal_to_double(0.7514407));
  assert_that_double(buf[99], is_equal_to_double(0.7449196));
  assert_that_double(buf[199], is_equal_to_double(0.752));
  assert_that_double(buf[299], is_equal_to_double(0.7489501));
  assert_that_double(buf[399], is_equal_to_double(0.74998695));
  assert_that_double(buf[499], is_equal_to_double(0.7513988));
  assert_that_double(buf[599], is_equal_to_double(0.7493566));
  assert_that_double(buf[699], is_equal_to_double(0.75077426));
  assert_that_double(buf[799], is_equal_to_double(0.7518974));
  assert_that_double(buf[899], is_equal_to_double(0.7498404));
  assert_that_double(buf[999], is_equal_to_double(0.7496314));
  assert_that_double(buf[1099], is_equal_to_double(0.7489508));
  assert_that_double(buf[1196], is_equal_to_double(0.75185496));

  assert_that_double(dset_info.CGSConversionFactor, is_equal_to_double(1.0));

  assert_that(
    dset_info.VarDescription,
    is_equal_to_string("Smoothed mass fractions of chemical elements"));

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
