/*
 * crop_eagle_tests.c
 */


#include <cgreen/cgreen.h>
#include "./../src/crop_eagle.h"
#include "./../src/init_hash.h"
#include "./../src/peano_hilbert_key.h"


#define SNAP_PATH "./snapshot/eagle_snap.%d.hdf5"


eagle_hash_t hash;


Describe(crop_eagle);


BeforeEach(crop_eagle)
{
  init_hash(SNAP_PATH, &hash);
}


AfterEach(crop_eagle) {}


Ensure(crop_eagle, selects_all_regions)
{
  crop_eagle(&hash, .0, .0, .0, hash.box_size, hash.box_size, hash.box_size);

  for(int i = 0; i < hash.map_len; i += hash.map_len / 75)
      assert_that(hash.map[i], is_equal_to(1));
}


Ensure(crop_eagle, selects_none)
{
  crop_eagle(&hash, .0, .0, .0, .01, .01, .01);

  assert_that(hash.map[0], is_equal_to(1));

  for(int i = 1; i < hash.map_len; i += hash.map_len / 17)
    assert_that(hash.map[i], is_equal_to(0));
}


Ensure(crop_eagle, should_also_work_with_out_of_box_boundary_selection)
{
  crop_eagle(&hash, -hash.box_size, -hash.box_size, -hash.box_size,
             hash.box_size, hash.box_size, hash.box_size);

  for(int i = 0; i < hash.map_len; i += hash.map_len / 21)
    assert_that(hash.map[i], is_equal_to(1));
}


Ensure(crop_eagle, fractional_selection)
{
  double len = 1.05 * hash.box_size / (1 << hash.bits);

  crop_eagle(&hash, .0, .0, .0, len, len, len);

  for(int i = 0; i < 2; i++)
    for(int j = 0; j < 2; j++)
      for(int k = 0; k < 2; k++)
        assert_that(hash.map[peano_hilbert_key(i, j, k, hash.bits)], is_equal_to(1));

  int ncells = 1 << hash.bits;

  for(int i = 2; i < ncells; i += ncells / 5)
    for(int j = 2; j < ncells; j += ncells / 5)
      for(int k = 2; k < ncells; k += ncells / 5)
        assert_that(hash.map[peano_hilbert_key(i, j, k, hash.bits)], is_equal_to(0));
}
