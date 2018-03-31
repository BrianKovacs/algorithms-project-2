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

void option1(const char* file);

int main(int argc, const char * argv[]) {
    
    if (argc >= 3 && strncmp (argv[1], "1", 2) == 0) {
        cout << "Option 1...\n";
        option1(argv[2]);
    }
    else if (argc >= 3 && strncmp (argv[1], "2", 2) == 0) {
        cout << "Option 2...\n";
    }
    else if (argc >= 3 && strncmp (argv[1], "3", 2) == 0) {
        cout << "Option 3...\n";
    }
    else if (argc >= 3 && strncmp (argv[1], "4", 2) == 0) {
        cout << "Option 4...\n";
    }
    else {
        cout << "Invalid arguments\n";
    }
    
    return 0;
}

void option1(const char* file) {
    cout << file << endl;
    PGMImage i;
    i.loadASCII(file);
    string newFile = "test.pgm";
    i.saveASCII(newFile.c_str());
}
