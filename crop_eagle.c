/*
 * crop_eagle.c
 * tests_file: crop_eagle_tests.c
 *
 * Croping the simulation box
 *
 * @param: snap: snapshot object
 * @param: x, y, z: top-left-back orogin of the sub region
 * @param: dx, dy, dz: sides of the sub region
 *
 * @return: Always EXIT_SUCCESS!!
 */


#include <stdlib.h>
#include <math.h>
#include "./crop_eagle.h"
#include "./peano_hilbert_key.h"


#define IMIN 0
#define IMAX 1
#define JMIN 2
#define JMAX 3
#define KMIN 4
#define KMAX 5


int crop_eagle(eagle_hash_t *hash, double x, double y, double z,
               double dx, double dy, double dz)
{
  int ncells = 1 << hash->bits;
  int box[6] = {0, 0, 0, 0, 0, 0};

  box[IMIN] = (int)floor(x / hash->box_size * ncells);
  box[IMAX] = (int)floor((x + dx) / hash->box_size * ncells);
  box[JMIN] = (int)floor(y / hash->box_size * ncells);
  box[JMAX] = (int)floor((y + dy) / hash->box_size * ncells);
  box[KMIN] = (int)floor(z / hash->box_size * ncells);
  box[KMAX] = (int)floor((z + dz) / hash->box_size * ncells);

  for(int i = box[IMIN]; i <= box[IMAX]; i++)
    for(int j = box[JMIN]; j <= box[JMAX]; j++)
      for(int k = box[KMIN]; k <= box[KMAX]; k++)
        hash->map[peano_hilbert_key(i, j, k, hash->bits)] = 1;

  return EXIT_SUCCESS;
}
