//
//  half.h
//  pgm_compressor
//
//  Created by Brian Kovacs on 4/4/18.
//  Copyright © 2018 Brian Kovacs. All rights reserved.
//

#ifndef half_h
#define half_h

#include <iostream>
#include <bitset>

typedef short half;

short floatToHalf(float num)
{
    int     full32;
    half   half16;
    memcpy( &full32, &num, sizeof( float ) );
    
    half16 = ((full32 - (112<<23)) >> 13); // subtract offset and shift
    half16 = (half16 & 32767); // mask 0111111111111111
    half16 |= ((full32 >> 16) & 32768); // shift and mask 1000000000000000
    
    return half16;
}

float halfToFloat(short half16)
{
    int full32 = ((half16 & 32768) << 16) | // mask sign and shift 16
    (((half16 & 32767) << 13) + 939524096) ; // mask exponent and fraction, shift, and add offset.
    
    float num;
    memcpy(&num, &full32, sizeof(float));
    return num;
}

#endif
