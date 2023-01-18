#ifndef TRANSFORMATION_H_
#define TRANSFORMATION_H_

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imgStruct.h" 
#include "bmpStruct.h"
#include "util.h"

struct image* rotate( struct image* source, struct pixel** result, struct pixel** replica );

#endif /* TRANSFORMATION_H */


