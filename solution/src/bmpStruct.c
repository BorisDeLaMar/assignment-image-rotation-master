#include "bmpStruct.h"

/*  deserializer   */
uint64_t static padding_count(uint64_t width){
  return 4 - 3*width%4;
}

enum read_status from_bmp_header( FILE* in, struct bmp_header* header ){
  uint16_t read_header_bytes = fread(header, sizeof(struct bmp_header), 1, in);  
  if(read_header_bytes){
    return READ_OK;
  }
  else{
    return READ_INVALID_HEADER;
  }
}

enum read_status bmp_header_check(struct bmp_header* header){
  if((header->bfType != 0x4D42) && (header->biBitCount != 24) && (header->biCompression != 0)){
    return READ_INVALID_HEADER_SIGNATURE;
  }
  else{
    return READ_OK;
  }
}

enum read_status from_bmp_image( FILE* in, struct image* img, struct bmp_header header ){

  img->height = header.biHeight;
  img->width = header.biWidth;
  const uint64_t padding = padding_count(img->width);
  uint64_t read_bytes = 0;

  for(size_t i = 0; i < img->height; i++){
    read_bytes += fread(img->data + img->width*i, sizeof(struct pixel), img->width, in);
    fseek(in, padding, SEEK_CUR);
  }

  if(read_bytes == img->height*img->width){
    return READ_OK;
  }
  else{
    return READ_INVALID_BITS;
  }
}

/*  serializer   */
struct bmp_header header_creator(struct image* img){
  struct bmp_header header = {0};
  header.bfType = 0x4D42;
  header.bfileSize = sizeof(struct bmp_header) + sizeof(struct pixel)*img->height*img->width;
  header.bfReserved = 0;
  header.bOffBits = sizeof(struct bmp_header);
  header.biWidth = img->height;
  header.biHeight = img->width;
  header.biSize = 40;
  header.biPlanes = 1;
  header.biBitCount = 24;
  header.biCompression = 0;
  header.biSizeImage = sizeof(struct pixel)*img->height*img->width;
  header.biXPelsPerMeter = 0;
  header.biYPelsPerMeter = 0;
  header.biClrImportant = 0;
  header.biClrUsed = 0;
  return header;
}

enum write_status to_bmp( FILE* out, struct image const* img, struct bmp_header* header ){
  fwrite(header, 1, sizeof(struct bmp_header), out);

  const uint64_t padding = padding_count(header->biWidth);
  const char mass[4] = {0};
  uint64_t written_data = 0;

  for(size_t i = 0; i < header->biHeight; i++){
    written_data += fwrite(img->data + header->biWidth*i, sizeof(struct pixel), header->biWidth, out);  
    fwrite(mass, 1, padding, out);
  }
  if(written_data == img->width*img->height){
    return WRITE_OK;
  }
  else{
    return WRITE_ERROR;
  }
}
