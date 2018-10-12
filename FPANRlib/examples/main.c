#include <config.h>
#include <stdio.h>

// FIXME : trouver comment linker dynamiquement le chemin
#include "../src/libfpanrio.h"

int
main (void)
{
  puts ("Hello World!");
  puts ("This is " PACKAGE_STRING ".");

  float f = 1.0/3.0;
  printf("\nbefore conversion : %e, after conversion : %e, after conversion of the conversion : %e\n",f,floatToFpanr(f),fpanrToFloat(floatToFpanr(f)));

  return 0;
}
