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
    int* values;
    
    PGMImage() {width=0; height=0; max=0;};
    size_t getSize() {return width*height;}
    
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
            values = new int[size];
            
        } else if (n == 2) {
            // Max Value
            cout << "Max Value " << line << endl;
            iss >> max;
            
        } else {
            // Image Values
//            cout << '.';
            int val = 0;
            while (iss >> val && i < size) {
                values[i] = val;
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
        outFile << values[i] << "  ";
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

bool PGMImage::saveBinary(const char *file)
{
//    FILE * pFile;
//    char buffer[] = { 65 , 66 , 67 };
//    pFile = fopen ("myfile.bin", "wb");
//    fwrite (buffer , sizeof(char), sizeof(buffer), pFile);
//    fclose (pFile);
//    return 0;
    
    FILE * pFile;
    pFile = fopen (file, "wb");
    
    char w1 = width%256;
    char w2 = (width-w1)/256;
    char h1 = height%256;
    char h2 = (height-w1)/256;
    char bufferHeader[5] = { w1, w2, h1, h2 , static_cast<char>(max) };
    fwrite (bufferHeader , sizeof(char), sizeof(bufferHeader), pFile);
    
    char bufferValues[getSize()];
    for (int i=0; i < getSize(); ++i) {
        bufferValues[i] = values[i];
    }
    fwrite (bufferValues , sizeof(char), sizeof(bufferValues), pFile);
    
    fclose (pFile);
    return true;
}

#endif /* PGMImage_h */
