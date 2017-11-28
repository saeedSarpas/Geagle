/*
 * count_particles_tests.c
 */


#include <stdlib.h>
#include <cgreen/cgreen.h>
#include "./count_particles.h"
#include "./init_hash.h"
#include "./init_eagle.h"
#include "./eagle_types.h"


#define SNAP_PATH "./snapshot/eagle_snap.%d.hdf5"


eagle_hash_t hash;
eagle_t snap;


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

  int nstars = count_particles(SNAP_PATH, &hash, star_particles);

  assert_true(nstars >= 0);
  assert_that(nstars, is_equal_to(snap.header.NumPart_Total[star_particles]));
}


Ensure(count_particles, counts_none_of_the_particles)
{
  for(int i = 0; i < hash.map_len; i++)
    hash.map[i] = 0;

  int ngas = count_particles(SNAP_PATH, &hash, gas_particles);

  assert_true(ngas >= 0);
  assert_that(ngas, is_equal_to(0));
}


Ensure(count_particles, always_returns_in_sensable_range)
{
  for(int i = 0; i < hash.map_len; i++)
    hash.map[i] = 0;

  int old_nparts = 0, new_nparts;

  for(int i = 0; i < hash.map_len; i += hash.map_len / 20)
    {
      hash.map[i] = 1;
      new_nparts = count_particles(SNAP_PATH, &hash, DM_particles);

      assert_true(new_nparts > old_nparts);
      assert_true(new_nparts < snap.header.NumPart_Total[DM_particles]);

      old_nparts = new_nparts;
    }
}
