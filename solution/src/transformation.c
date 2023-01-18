#include "transformation.h"

struct image* rotate( struct image* source, struct pixel** result, struct pixel** replica ){

    size_t height = 0; size_t width = 0;
    for(size_t i = 0; i < source->height; i++){
        height = 0;
        for(size_t j = 0; j < source->width; j++){
            result[height][width] = replica[i][j];
            height++;
        }
        width++;
    }
    back_from_the_future(source, result);

    return source;
}

