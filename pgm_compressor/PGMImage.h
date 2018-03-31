//
//  PGMImage.h
//  pgm_compressor
//
//  Created by Brian Kovacs on 3/31/18.
//  Copyright © 2018 Brian Kovacs. All rights reserved.
//

#ifndef PGMImage_h
#define PGMImage_h

class PGMImage {
public:
    int width;
    int height;
    int max;
    int* arr;
};

#endif /* PGMImage_h */
