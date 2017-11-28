/*
 * count_particles.c
 * tests_file: count_particles_tests.c
 *
 * Counting particles (usually after cropping the simulation box)
 *
 * @param: fmt_path: Formatted file path, e.g. /path/to/snap.%d.h5
 * @param: hash: The hash struct to be filled
 * @param: nparts: An array of length 6 to be filled with the number of particles
 *
 * @return: Standard EXIT_SUCCESS/EXIT_FAILURE
 */


#include <stdlib.h>
#include <string.h>
#include <High5/High5.h>
#include "./count_particles.h"


int count_particles(char *fmt_path, eagle_hash_t *hash, long long *nparts)
{
  if(strstr(fmt_path, "%d") == NULL) {
    printf("[Warning] Please use a formatted file path.\n");
    printf("          e.g. /path/to/eagle/snap.%%d.h5\n");
    return -1;
  }

  long long offset = 0;

  for(int i = 0; i < 6; i++)
    nparts[i] = 0;

  for(int ptype = 0; ptype < 6; ptype++)
    {
      if(ptype == 2 || ptype == 3) continue;

      for(int ifile = 0; ifile < hash->num_files; ifile++)
        {
          for(int key = hash->table[ptype].FirstKeyInFile[ifile];
              key <= hash->table[ptype].LastKeyInFile[ifile]; key++)
            {
              if(!hash->map[key]) continue;

              offset = key - hash->table[ptype].FirstKeyInFile[ifile];
              nparts[ptype] += hash->table[ptype].NumParticleInCell[ifile][offset];
            }
        }
    }

  return EXIT_SUCCESS;
}
