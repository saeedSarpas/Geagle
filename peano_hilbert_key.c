/*
 * peano_hilbert_key.c
 * tests_file: peano_hilbert_key_tests.c
 *
 * Generating Peano key based on cell numbers
 *
 * @param: i, j, k: Cell coordinate
 * @param: hashbits:
 *
 * @return: peanokey
 *
 * @Copyright: 2005 Volker Springel (From Gadget2/peano.c)
 */


#include "./peano_hilbert_key.h"


static int quadrants[24][2][2][2] = {
  /* rotx=0, roty=0-3 */
  {{{0, 7}, {1, 6}}, {{3, 4}, {2, 5}}},
  {{{7, 4}, {6, 5}}, {{0, 3}, {1, 2}}},
  {{{4, 3}, {5, 2}}, {{7, 0}, {6, 1}}},
  {{{3, 0}, {2, 1}}, {{4, 7}, {5, 6}}},
  /* rotx=1, roty=0-3 */
  {{{1, 0}, {6, 7}}, {{2, 3}, {5, 4}}},
  {{{0, 3}, {7, 4}}, {{1, 2}, {6, 5}}},
  {{{3, 2}, {4, 5}}, {{0, 1}, {7, 6}}},
  {{{2, 1}, {5, 6}}, {{3, 0}, {4, 7}}},
  /* rotx=2, roty=0-3 */
  {{{6, 1}, {7, 0}}, {{5, 2}, {4, 3}}},
  {{{1, 2}, {0, 3}}, {{6, 5}, {7, 4}}},
  {{{2, 5}, {3, 4}}, {{1, 6}, {0, 7}}},
  {{{5, 6}, {4, 7}}, {{2, 1}, {3, 0}}},
  /* rotx=3, roty=0-3 */
  {{{7, 6}, {0, 1}}, {{4, 5}, {3, 2}}},
  {{{6, 5}, {1, 2}}, {{7, 4}, {0, 3}}},
  {{{5, 4}, {2, 3}}, {{6, 7}, {1, 0}}},
  {{{4, 7}, {3, 0}}, {{5, 6}, {2, 1}}},
  /* rotx=4, roty=0-3 */
  {{{6, 7}, {5, 4}}, {{1, 0}, {2, 3}}},
  {{{7, 0}, {4, 3}}, {{6, 1}, {5, 2}}},
  {{{0, 1}, {3, 2}}, {{7, 6}, {4, 5}}},
  {{{1, 6}, {2, 5}}, {{0, 7}, {3, 4}}},
  /* rotx=5, roty=0-3 */
  {{{2, 3}, {1, 0}}, {{5, 4}, {6, 7}}},
  {{{3, 4}, {0, 7}}, {{2, 5}, {1, 6}}},
  {{{4, 5}, {7, 6}}, {{3, 2}, {0, 1}}},
  {{{5, 2}, {6, 1}}, {{4, 3}, {7, 0}}}
};


static char rotx_table[8] = {3, 0, 0, 2, 2, 0, 0, 1};
static char roty_table[8] = {0, 1, 1, 2, 2, 3, 3, 0};


static char sense_table[8] = {-1, -1, -1, +1, +1, -1, -1, -1};

static char rotxmap_table[24] = {
  4, 5, 6, 7, 8, 9, 10, 11,
  12, 13, 14, 15, 0, 1, 2, 3,
  17, 18, 19, 16, 23, 20, 21, 22
};

static char rotymap_table[24] = {
  1, 2, 3, 0, 16, 17, 18, 19,
  11, 8, 9, 10, 22, 23, 20, 21,
  14, 15, 12, 13, 4, 5, 6, 7
};


peanokey peano_hilbert_key(int i, int j, int k, int bits)
{
  int mask, key, rotation, sense;
  int ibit, jbit, kbit;
  int rotx, roty;
  int quad;

  mask = 1 << (bits - 1);
  rotation = 0;
  sense = 1;
  key = 0;

  for(int b = 0; b < bits; b++, mask >>= 1)
    {
      ibit = (i & mask) ? 1 : 0;
      jbit = (j & mask) ? 1 : 0;
      kbit = (k & mask) ? 1 : 0;

      quad = quadrants[rotation][ibit][jbit][kbit];

      key <<= 3;
      key += (sense == 1) ? quad : 7 - quad;

      rotx = rotx_table[quad];
      roty = roty_table[quad];

      sense *= sense_table[quad];

      while(rotx > 0)
        {
          rotation = rotxmap_table[rotation];
          rotx--;
        }

      while(roty > 0)
        {
          rotation = rotymap_table[rotation];
          roty--;
        }
    }

  return key;
}
