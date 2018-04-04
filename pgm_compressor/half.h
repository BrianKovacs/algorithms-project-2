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
using namespace std;

short floatToHalf(float num)
{
    int     full32;
    half   half16;
    memcpy( &full32, &num, sizeof( float ) );
    
    char exp;
    exp = full32 >> 23;
    unsigned int i = exp;
    
    if (i == 0) {
        half16 = (full32 >> 13); // only shift shift
        half16 = (half16 & 32767); // mask 0111111111111111
        half16 = (half16 & 32767) | ((full32 >> 16) & 32768); // shift and mask 1000000000000000
    } else if (i < 112) {
//        std::cout << "NO\n";
        
        unsigned int int1;
        memcpy(&int1, &num, sizeof(float));
        bitset<32> b1{int1};
        cout << b1 << endl;
        
        
        half16 = (full32 >> 13) & 33791; // subtract offset and shift
        half16 = (half16 & 32767); // mask 0111111111111111
        half16 = (half16 & 32767) | ((full32 >> 16) & 32768); // shift and mask 1000000000000000
    } else {
//        std::cout << "HELLO\n";
        half16 = ((full32 - (112<<23)) >> 13); // subtract offset and shift
        half16 = (half16 & 32767); // mask 0111111111111111
        half16 = (half16 & 32767) | ((full32 >> 16) & 32768); // shift and mask 1000000000000000
    }
    
//    half16 = ((full32 - (112<<23)) >> 13); // subtract offset and shift
//    half16 = (half16 & 32767); // mask 0111111111111111
//    half16 = (half16 & 32767) | ((full32 >> 16) & 32768); // shift and mask 1000000000000000
    


    if (i < 112) {
//        half16 = ((full32 << 9 ) >> 22); // subtract offset and shift
//        half16 = (half16 & 32767); // mask 0111111111111111
//        half16 |= ((full32 >> 16) & 32768); // shift and mask 1000000000000000
//        std::cout << "BAD" << std::endl;
//        half16 = 0;
//        half16 = half16 & 33791;
    } else {
//        half16 = ((full32 - (112<<23)) >> 13); // subtract offset and shift
//        half16 = (half16 & 32767); // mask 0111111111111111
//        half16 |= ((full32 >> 16) & 32768); // shift and mask 1000000000000000
    }
    
    return half16;
}

float halfToFloat(short half16)
{
    if (!half16) {
        std::cout << "HEYYYYYY\n";
        return 0;
    }
    int full32 = ((half16 & 32768) << 16) | // mask sign and shift 16
    (((half16 & 32767) << 13) + 939524096) ; // mask exponent and fraction, shift, and add offset.
    
    float num;
    memcpy(&num, &full32, sizeof(float));
    return num;
}

#endif