//
//  PGMImage.h
//  pgm_compressor
//
//  Created by Brian Kovacs on 3/31/18.
//  Copyright © 2018 Brian Kovacs. All rights reserved.
//

#ifndef PGMImage_h
#define PGMImage_h

#include <sstream>
#include <string>
#include <iostream>
#include <fstream>

using std::string;
using std::ifstream;
using std::ofstream;
using std::getline;
using std::cout;
using std::endl;

class PGMImage
{
public:
    int width;
    int height;
    int max;
    int* arr;
    
    PGMImage() {width=0; height=0; max=0;};
    int getSize() {return width*height;}
    
    bool loadASCII(const char* file);
    bool saveASCII(const char* file);
    bool loadBinary(const char* file);
    bool saveBinary(const char* file);
};

bool PGMImage::loadASCII(const char* file)
{
    string line;
    ifstream infile(file);
    
    if (!infile) {
        cout << "File does not exist!\n";
        return false;
    }
    
    int n = 0;
    int i = 0;
    int size = 0;
    while (getline(infile, line))
    {
        std::istringstream iss(line);
        
        if (line[0] == '#') {
            // eat all the comment lines
            cout << line << endl;
            continue;
        }
        
        if (n == 0) {
            // Magic Number
            cout << "Magic Number " << line << endl;
            
        } else if (n == 1) {
            // Width and Height
            cout << "Width and Height " << line << endl;
            iss >> width >> height;
            size = width*height;
            arr = new int[size];
            
        } else if (n == 2) {
            // Max Value
            cout << "Max Value " << line << endl;
            iss >> max;
            
        } else {
            // Image Values
//            cout << '.';
            int val = 0;
            while (iss >> val && i < size) {
                arr[i] = val;
                ++i;
            }
        }
        
        ++n;
    }
    cout << endl;
    
    return true;
}

bool PGMImage::saveASCII(const char *file)
{
    ofstream outFile;
    outFile.open(file);
//    outFile << "Hello\n";
    
    outFile << "P2\n";
    outFile << "# Created for Algorithms Project 2.\n";
    outFile << width << ' ' << height << endl;
    outFile << max << endl;
    
    for (int i=0; i < getSize(); ++i) {
        outFile << arr[i] << "  ";
        if ((i+1)%12==0)
            outFile << endl;
    }
    
    outFile.close();
    return true;
}

bool PGMImage::loadBinary(const char *file)
{
    return true;
}

bool PGMImage::saveBinary(<#const char *file#>)
{
    return true;
}

#endif /* PGMImage_h */
