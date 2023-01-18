#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imgStruct.h"
#include "bmpStruct.h"
#include "util.h"
#include "transformation.h"

int main( int argc, char** argv ) {
    (void) argc; (void) argv; // supress 'unused parameters' warning
    if(argc != 3){
        fprintf(stderr, "There should be three args: ./image-transformer <source-image> <transformed-image>\n");
        return 1;
    }

    struct bmp_header header = {0}; 
    struct bmp_header* header_ptr = &header; 

    FILE* input; FILE* output;
    if((input = fopen(argv[1], "r")) == NULL){
        fprintf(stderr, "<source-image> file doesn't exist\n");
        return 2;
    } 
    if((output = fopen(argv[2], "w")) == NULL){
        fprintf(stderr, "Can't create <transformed-image> file\n");
        return 2;
    }

    const enum read_status header_st = from_bmp_header(input, header_ptr);
    if(header_st == READ_INVALID_HEADER){
        fprintf(stderr, "Header of <source-image> is invalid\n");
        return 3;
    }
    const enum read_status header_sign_st = bmp_header_check(header_ptr);
    if(header_sign_st == READ_INVALID_HEADER_SIGNATURE){
        fprintf(stderr, "Header signature of input file is invalid");
        return 3;
    }

    struct image img = {0};
    struct image* img_ptr = &img;
    img_ptr->data = malloc(sizeof(struct pixel)*header_ptr->biHeight*header_ptr->biWidth);
    const enum read_status img_st = from_bmp_image(input, img_ptr, header);
    if(img_st == READ_INVALID_BITS){
        fprintf(stderr, "Bits were read invalid in <source-image>\n");
        return 3;
    }
    uint64_t img_width = img.width;
    uint64_t img_height = img.height;
    
    struct pixel** matrix = (struct pixel**) malloc(sizeof(struct pixel*)*img_width);
    for(int i = 0; i < img_width; i++) {
        matrix[i] = (struct pixel*) malloc(sizeof(struct pixel)*img_height);
    }
    struct pixel** matrix2 = (struct pixel**) malloc(sizeof(struct pixel*)*img_height);
    for(int i = 0; i < img_height; i++) {
        matrix2[i] = (struct pixel*) malloc(sizeof(struct pixel)*img_width);
    }
    matrix2 = mass_terraforming(img_ptr, matrix2);

    img_ptr = rotate(img_ptr, matrix, matrix2);
    struct bmp_header new_header = header_creator(img_ptr);

    enum write_status write_st = to_bmp(output, img_ptr, &new_header);
    if(write_st == WRITE_ERROR){
        fprintf(stderr, "Error occured while writting to <transformed-image> file");
        return 4;
    }

    for(int i = 0; i < img_height; i++) {
        free(matrix2[i]);
    }
    for(int i = 0; i < img_width; i++) {
        free(matrix[i]);
    }
    free(matrix); free(matrix2); free(img_ptr->data);


    return 0;
}

