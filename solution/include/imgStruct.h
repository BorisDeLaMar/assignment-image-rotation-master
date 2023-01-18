#ifndef IMGSTRUCT_H_
#define IMGSTRUCT_H_

#include  <stdint.h>

struct image {
  uint64_t width, height;
  struct pixel* data;
};

#endif /* IMGSTRUCT_H_ */



