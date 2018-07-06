/*
 * read_eagle_dset_tests.c
 */


#include <cgreen/cgreen.h>
#include <assert.h>
#include "./../src/read_eagle_dset.h"
#include "./../src/init_hash.h"
#include "./../src/crop_eagle.h"
#include "./../src/count_particles.h"


#define DSET_1D_NAME "ElementAbundance/Hydrogen"
#define DSET_3D_NAME "Coordinates"
#define NUM_FILES 16


#define SNAP_1ST_PATH "./snapshot/eagle_snap.0.hdf5"
#define SNAP_FMT_PATH "./snapshot/eagle_snap.%d.hdf5"

int tot_num_part[6];


Describe(read_eagle_dset);


BeforeEach(read_eagle_dset)
{
  hid_t file_id, group_id, attr_id;
  herr_t h5err;

  assert(H5open() >= 0);

  file_id = H5Fopen(SNAP_1ST_PATH, H5F_ACC_RDONLY, H5P_DEFAULT);
  assert(file_id >= 0);

  group_id = H5Gopen(file_id, "Header", H5P_DEFAULT);
  assert(group_id >= 0);

  attr_id = H5Aopen_name(group_id, "NumPart_Total");
  assert(attr_id >= 0);

  h5err = H5Aread(attr_id, H5T_NATIVE_INT, tot_num_part);
  assert(h5err >= 0);

  H5Aclose(attr_id);
  H5Gclose(group_id);

  h5err = H5Fclose(file_id);
  if (h5err < 0)
    printf("[ERROR] Unable to close EAGLE snapshot: %s",
           SNAP_1ST_PATH);
}


AfterEach(read_eagle_dset)
{
  assert(H5close() >= 0);
}


Ensure(read_eagle_dset, reads_eagle_1d_dataset)
{
  double *buf = malloc(tot_num_part[star_particles] * sizeof(double));

  eagle_dset_info_t dset_info;
  dset_info.aexp_scale_exponent = 1.23456789;
  dset_info.h_scale_exponent = 1.23456789;

  assert_that(read_eagle_dset(SNAP_FMT_PATH, star_particles,
                              DSET_1D_NAME, H5T_NATIVE_DOUBLE, buf,
                              &dset_info, NULL),
              is_equal_to(EXIT_SUCCESS));

  herr_t h5err;
  hid_t file_id, dset_id, group_id, attr_id, dspace, mspace;
  hsize_t start[1] = {0}, count[1] = {1}, dimsm[1] = {1};
  int tot_offset = 0, num_parts[6];
  char file_path[1024], dset_path[1024];
  double value[1];

  sprintf(dset_path, "PartType%d/%s", star_particles, DSET_1D_NAME);

  for(int ifile = 0; ifile < NUM_FILES; ifile++)
    {
      sprintf(file_path, SNAP_FMT_PATH, ifile);

      file_id = H5Fopen(file_path, H5F_ACC_RDONLY, H5P_DEFAULT);
      assert(file_id >= 0);

      group_id = H5Gopen(file_id, "Header", H5P_DEFAULT);
      assert(group_id >= 0);

      attr_id = H5Aopen_name(group_id, "NumPart_ThisFile");
      assert(attr_id >= 0);

      h5err = H5Aread(attr_id, H5T_NATIVE_INT, num_parts);
      assert(h5err >= 0);

      for (int i = 0; i < num_parts[star_particles]; i += 97)
        {
          dset_id = H5Dopen(file_id, dset_path, H5P_DEFAULT);

          dspace = H5Dget_space(dset_id);

          /* Offset from the begining of the dataset */
          start[0] = i;
          H5Sselect_hyperslab(dspace, H5S_SELECT_SET, start , NULL, count, NULL);

          mspace = H5Screate_simple(1, dimsm, NULL);

          /* Offset from memspace */
          start[0] = 0;
          H5Sselect_hyperslab(mspace, H5S_SELECT_SET, start, NULL, count, NULL);

          H5Dread(dset_id, H5T_NATIVE_DOUBLE, mspace, dspace, H5P_DEFAULT, value);

          assert_that_double(buf[i+tot_offset], is_equal_to_double(value[0]));

          H5Sselect_none(mspace);
          H5Sselect_none(dspace);

          H5Dclose(dset_id);
        }

      tot_offset += num_parts[star_particles];

      H5Fclose(file_id);
    }

  assert_that_double(dset_info.CGSConversionFactor, is_equal_to_double(1.0));

  assert_that(dset_info.VarDescription,
              is_equal_to_string("Mass fractions of chemical elements"));

  assert_that_double(dset_info.aexp_scale_exponent, is_equal_to_double(0.0));
  assert_that_double(dset_info.h_scale_exponent, is_equal_to_double(0.0));
}


Ensure(read_eagle_dset, reads_eagle_3d_dataset)
{
  double *buf = malloc(tot_num_part[star_particles] * 3 * sizeof(double));

  eagle_dset_info_t dset_info;
  dset_info.aexp_scale_exponent = 1.23456789;
  dset_info.h_scale_exponent = 1.23456789;

  assert_that(read_eagle_dset(SNAP_FMT_PATH, star_particles,
                              DSET_3D_NAME, H5T_NATIVE_DOUBLE, buf,
                              &dset_info, NULL),
              is_equal_to(EXIT_SUCCESS));

  herr_t h5err;
  hid_t file_id, dset_id, group_id, attr_id, dspace, mspace;
  hsize_t start[2] = {0, 0}, count[2] = {1, 3}, dimsm[2] = {1, 3};
  int tot_offset = 0, num_parts[6];
  char file_path[1024], dset_path[1024];
  double value[3];

  sprintf(dset_path, "PartType%d/%s", star_particles, DSET_3D_NAME);

  for(int ifile = 0; ifile < NUM_FILES; ifile++)
    {
      sprintf(file_path, SNAP_FMT_PATH, ifile);

      file_id = H5Fopen(file_path, H5F_ACC_RDONLY, H5P_DEFAULT);
      assert(file_id >= 0);

      group_id = H5Gopen(file_id, "Header", H5P_DEFAULT);
      assert(group_id >= 0);

      attr_id = H5Aopen_name(group_id, "NumPart_ThisFile");
      assert(attr_id >= 0);

      h5err = H5Aread(attr_id, H5T_NATIVE_INT, num_parts);
      assert(h5err >= 0);

      for(int i = 0; i < num_parts[star_particles]; i += 199)
        {
          dset_id = H5Dopen(file_id, dset_path, H5P_DEFAULT);

          dspace = H5Dget_space(dset_id);

          /* Offset from the begining of the dataset */
          start[0] = i;
          H5Sselect_hyperslab(dspace, H5S_SELECT_SET, start , NULL, count, NULL);

          mspace = H5Screate_simple(2, dimsm, NULL);

          /* Offset from memspace */
          start[0] = 0;
          H5Sselect_hyperslab(mspace, H5S_SELECT_SET, start, NULL, count, NULL);

          H5Dread(dset_id, H5T_NATIVE_DOUBLE, mspace, dspace, H5P_DEFAULT, value);

          int index = (i+tot_offset) * 3;
          assert_that_double(buf[index], is_equal_to_double(value[0]));
          assert_that_double(buf[index+1], is_equal_to_double(value[1]));
          assert_that_double(buf[index+2], is_equal_to_double(value[2]));

          H5Sselect_none(mspace);
          H5Sselect_none(dspace);

          H5Dclose(dset_id);
        }

      tot_offset += num_parts[star_particles];

      H5Fclose(file_id);
    }

  assert_that_double(dset_info.CGSConversionFactor,
                     is_equal_to_double(3.085678E24));

  assert_that(dset_info.VarDescription,
              is_equal_to_string("Co-moving coordinates. Physical: r = a x = Coordinates h^-1 a U_L [cm]"));

  assert_that_double(dset_info.aexp_scale_exponent, is_equal_to_double(1.0));
  assert_that_double(dset_info.h_scale_exponent, is_equal_to_double(-1.0));
}


Ensure(read_eagle_dset, should_be_able_to_work_with_cropped_box)
{
  eagle_hash_t hash;
  init_hash(SNAP_FMT_PATH, &hash);

  long long nparts[6];

  char dset_path[1024];
  sprintf(dset_path, "PartType%d/%s", star_particles, DSET_3D_NAME);

  double half_box = hash.box_size/2.0;
  crop_eagle(&hash, half_box, half_box, half_box, half_box/2.0, half_box/2.0, half_box/2.0);

  count_particles(SNAP_FMT_PATH, &hash, nparts);

  double *buf = malloc(nparts[star_particles] * 3 * sizeof(double));

  assert_that(read_eagle_dset(SNAP_FMT_PATH, star_particles,
                              DSET_3D_NAME, H5T_NATIVE_DOUBLE, buf,
                              NULL, &hash),
              is_equal_to(EXIT_SUCCESS));

  for(int i = 0; i < 3 * nparts[star_particles]; i++)
    {
      assert_true(buf[i] >= half_box);
      assert_true(buf[i] <= half_box + half_box / 2);
    }
}
