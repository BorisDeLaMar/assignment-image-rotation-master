#include "util.h"

struct pixel** mass_terraforming(struct image* img, struct pixel** perfect_array){
    
    size_t counter = 0;
    for(size_t i = 0; i < img->height; i++){
        for(size_t j = 0; j < img->width; j++){
            perfect_array[i][j] = img->data[counter];
            counter++;
        }
    }
    
    return perfect_array;
}

void back_from_the_future(struct image* img, struct pixel** perfect_array){

    size_t counter = 0;
    for(size_t i = 0; i < img->width; i++){
        for(size_t j = img->height; j > 0; j--){
            img->data[counter] = perfect_array[i][j];
            counter++;
        }
    }

}

