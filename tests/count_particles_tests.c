/*
 * count_particles_tests.c
 */


#include <stdlib.h>
#include <cgreen/cgreen.h>
#include "./../src/count_particles.h"
#include "./../src/init_hash.h"
#include "./../src/init_eagle.h"
#include "./../src/eagle_types.h"


#define SNAP_PATH "./snapshot/eagle_snap.%d.hdf5"


eagle_hash_t hash;
eagle_t snap;
long long nparts[6] = {0, 0, 0, 0, 0, 0};


Describe(count_particles);


BeforeEach(count_particles)
{
  init_eagle(SNAP_PATH, &snap);
  init_hash(SNAP_PATH, &hash);
}


AfterEach(count_particles) {}


Ensure(count_particles, counts_all_particles)
{
  for(int i = 0; i < hash.map_len; i++)
    hash.map[i] = 1;

  int err = count_particles(SNAP_PATH, &hash, nparts);

  assert_that(err, is_equal_to(EXIT_SUCCESS));

  for(int i = 0; i < 6; i++)
    assert_that(nparts[i], is_equal_to(snap.header.NumPart_Total[i]));
}


Ensure(count_particles, counts_none_of_the_particles)
{
  for(int i = 0; i < hash.map_len; i++)
    hash.map[i] = 0;

  int err = count_particles(SNAP_PATH, &hash, nparts);

  assert_that(err, is_equal_to(EXIT_SUCCESS));
  for(int i = 0; i < 6; i++)
    assert_that(nparts[i], is_equal_to(0));
}


Ensure(count_particles, always_returns_in_sensable_range)
{
  for(int i = 0; i < hash.map_len; i++)
    hash.map[i] = 0;

  int err, old_nparts[6] = {0, 0, 0, 0, 0, 0},
    new_nparts[6] = {0, 0, 0, 0, 0, 0};

  for(int i = 0; i < hash.map_len; i += hash.map_len / 20)
    {
      hash.map[i] = 1;
      err = count_particles(SNAP_PATH, &hash, nparts);

      assert_that(err, is_equal_to(EXIT_SUCCESS));

      for(int i = 0; i < 6; i++)
        {
          new_nparts[i] += nparts[i];
          assert_true(new_nparts[i] <= snap.header.NumPart_Total[i]);
          assert_true(new_nparts[i] >= old_nparts[i]);
          old_nparts[i] = new_nparts[i];
        }

    }
}
