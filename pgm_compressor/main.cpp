//
//  main.cpp
//  pgm_compressor
//
//  Created by Brian Kovacs on 3/31/18.
//  Copyright © 2018 Brian Kovacs. All rights reserved.
//

#include <iostream>
#include "PGMImage.h"

using namespace std;

int main(int argc, const char * argv[]) {
    
    if (argc >= 3 && strncmp (argv[1], "1", 2) == 0)
        cout << "Option 1...\n";
    else if (argc >= 3 && strncmp (argv[1], "1", 2) == 0)
        cout << "Option 2...\n";
    else if (argc >= 3 && strncmp (argv[1], "1", 2) == 0)
        cout << "Option 3...\n";
    else if (argc >= 3 && strncmp (argv[1], "1", 2) == 0)
        cout << "Option 4...\n";
    
    return 0;
}
