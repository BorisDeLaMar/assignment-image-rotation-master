#ifndef BMPSTRUCT_H_
#define BMPSTRUCT_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imgStruct.h"

struct __attribute__((packed)) bmp_header
{
        uint16_t bfType;
        uint32_t  bfileSize;
        uint32_t bfReserved;
        uint32_t bOffBits;
        uint32_t biSize;
        uint32_t biWidth;
        uint32_t  biHeight;
        uint16_t  biPlanes;
        uint16_t biBitCount;
        uint32_t biCompression;
        uint32_t biSizeImage;
        uint32_t biXPelsPerMeter;
        uint32_t biYPelsPerMeter;
        uint32_t biClrUsed;
        uint32_t  biClrImportant;
};

struct pixel { uint8_t b, g, r; };

enum read_status  {
  READ_OK = 0,
  READ_INVALID_SIGNATURE,
  READ_INVALID_BITS,
  READ_INVALID_HEADER,
  READ_INVALID_HEADER_SIGNATURE
  /* коды других ошибок  */
};

enum  write_status  {
  WRITE_OK = 0,
  WRITE_ERROR
  /* коды других ошибок  */
};

enum read_status from_bmp_header(FILE* in, struct bmp_header* header);
enum read_status from_bmp_image( FILE* in, struct image* img , struct bmp_header header);
enum write_status to_bmp( FILE* out, struct image const* img, struct bmp_header* header );
enum read_status bmp_header_check(struct bmp_header* header);
struct bmp_header header_creator(struct image* img);
#endif /* BMPSTRUCT_H_ */


