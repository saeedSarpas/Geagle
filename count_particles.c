/*
 * count_particles.c
 * tests_file: count_particles_tests.c
 *
 * Counting particles (usually after cropping the simulation box)
 *
 * @param: fmt_path: Formatted file path, e.g. /path/to/snap.%d.h5
 * @param: hash: The hash struct to be filled
 * @param: ptype: Particle type
 *
 * @return: Number of particles (<0 on errors)
 */


#include <stdlib.h>
#include <string.h>
#include <High5/High5.h>
#include "./count_particles.h"


int count_particles(char *fmt_path, eagle_hash_t *hash, enum _PTypes ptype)
{
  if(strstr(fmt_path, "%d") == NULL) {
    printf("[Warning] Please use a formatted file path.\n");
    printf("          e.g. /path/to/eagle/snap.%%d.h5\n");
    return -1;
  }

  eagle_hashtable_t table = hash->table[ptype];

  long long offset = 0;
  int nparts = 0;


  for(int i = 0; i < hash->num_files; i++)
    {
      if(table.NumKeysInFile[i] <= 0) continue;

      for(int key = table.FirstKeyInFile[i]; key <= table.LastKeyInFile[i]; key++)
        {
          if(!hash->map[key]) continue;

          offset = key - table.FirstKeyInFile[i];
          nparts += table.NumParticleInCell[i][offset];
        }
    }

  return nparts;
}
