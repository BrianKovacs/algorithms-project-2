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
#include <cstdio>
#include <algorithm>
#include <math.h>
#include "half.h"

using std::string;
using std::ifstream;
using std::ofstream;
using std::getline;
using std::cout;
using std::endl;

const int BUFFERSIZE = 4096;

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
    static void saveSVD(const string headerName, const string svdName, const string outFileName, int rank);
    int loadSVD(const char* file);
    void exportMatrix(const string file);
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
    
    outFile << "P2\n";
    outFile << "# Created for Algorithms Project 2.\n";
    outFile << width << ' ' << height << endl;
    outFile << max << endl;
    
    for (int i=0; i < getSize(); ++i) {
        outFile << values[i];
        if ((i+1)%10==0)
            outFile << endl;
        else
            outFile << ' ';
    }
    
    outFile.close();
    return true;
}

bool PGMImage::loadBinary(const char *file)
{
    FILE* binFile = fopen(file, "rb" );
    if (!binFile) {
        printf("Error: could not open file %s\n", file);
        return false;
    }
    
    unsigned char * buffer = new unsigned char[BUFFERSIZE];
    int n = 0;

    for (size_t bytesRead = fread(buffer, sizeof(char), BUFFERSIZE, binFile); bytesRead > 0; bytesRead = fread(buffer, sizeof(char), BUFFERSIZE, binFile)) {

        cout << "Bytes read: " << bytesRead << endl;
        for (int i=0; i < bytesRead; ++i) {
//            cout << static_cast<int>(buffer[i]) << "  ";
            
            if (n == 0) {
                // lower half of width
                width = static_cast<int>(buffer[i]);
            } else if (n == 1) {
                // upper half of width
                width += 256*static_cast<int>(buffer[i]);
            } else if (n == 2) {
                // lower half of height
                height = static_cast<int>(buffer[i]);
            } else if (n == 3) {
                // upper half of height
                height += 256*static_cast<int>(buffer[i]);
                values = new int[getSize()];
            } else if (n == 4) {
                // max value
                max = static_cast<int>(buffer[i]);
            } else if (n-5 < getSize()) {
                // image values
                values[n-5] = static_cast<int>(buffer[i]);
            }
            ++n;
        }
    }
    cout << endl;
    
    // Done and close.
    fclose(binFile);
    
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
    
    FILE * binFile = fopen (file, "wb");
    
    char w1 = width%256;
    char w2 = (width-w1)/256;
    char h1 = height%256;
    char h2 = (height-w1)/256;
    char bufferHeader[5] = {w1, w2, h1, h2 , static_cast<char>(max)};
    fwrite (bufferHeader , sizeof(char), sizeof(bufferHeader), binFile);
    
    char bufferValues[getSize()];
    for (int i=0; i < getSize(); ++i) {
        bufferValues[i] = values[i];
    }
    fwrite (bufferValues , sizeof(char), sizeof(bufferValues), binFile);
    
    fclose (binFile);
    return true;
}

void PGMImage::saveSVD(const string headerName, const string svdName, const string outFileName, int rank)
{
    // Create input file streams
    ifstream header;
    ifstream svd;
    
    // Open all file streams
    header.open(headerName);
    svd.open(svdName);
    
    // Make sure files are open for reading
    if (!header.is_open()) {
        cout << "Error: Could not open " << headerName << " for reading.\n";
        return;
    }
    if (!svd.is_open()) {
        cout << "Error: Could not open " << svdName << " for reading.\n";
        return;
    }
    
    // Binary file to write into
    FILE * binFile = fopen(outFileName.c_str(), "wb");
    
    // Get the width, height, and max values
    int w, h, m;
    string line;
    getline(header, line);
    std::istringstream iss(line);
    iss >> w >> h >> m;
    
    // Write header info to binary file
    char w1 = w%256;
    char w2 = (w-w1)/256;
    char h1 = h%256;
    char h2 = (h-w1)/256;
    char bufferHeader[5] = {w1, w2, h1, h2 , static_cast<char>(m)};
    fwrite (bufferHeader , sizeof(char), sizeof(bufferHeader), binFile);
    
    // Get the U, S, and V matrices
    half *U, *S, *V;
    
    if (w > h) {
        cout << "ERROR HERE!!!";
        return;
        U = new half[h*h];
        S = new half[h*h];
        V = new half[w*h];
        
        // print the U matrix
        cout << "U Matrix:\n";
        string line;
        int count = 0;
        while (count < h && getline(svd, line)) {
            std::istringstream iss(line);
            float v;
            while (iss >> v) {
                cout << v << ' ';
            }
            cout << endl;
            ++count;
        }
        cout << endl;
        
        // print the S matrix
        cout << "S Matrix:\n";
        count = 0;
        while (count < h && getline(svd, line)) {
            std::istringstream iss(line);
            float v;
            int t=0;
            while (t<h && iss >> v) {
                cout << v << ' ';
                ++t;
            }
            cout << endl;
            ++count;
        }
        cout << endl;
        
        // print the V' matrix
        cout << "V' Matrix:\n";
        count = 0;
        while (count < h && getline(svd, line)) {
            std::istringstream iss(line);
            half v;
            while (iss >> v) {
                cout << v << ' ';
            }
            cout << endl;
            ++count;
        }
        cout << endl;
        return;
    } else {
        U = new half[h*w];
        S = new half[w*w];
        V = new half[w*w];
        
        // print the U matrix
        cout << "U Matrix:\n";
        string line;
        int row = 0;
        while (row < h && getline(svd, line)) {
            std::istringstream iss(line);
            float v;
            int col = 0;
            while (col < w && iss >> v) {
                cout << v << ' ';
                U[row*w + col] = floatToHalf(v);
                ++col;
            }
            cout << endl;
            ++row;
        }
        cout << endl;
        
        // print the S matrix
        cout << "S Matrix:\n";
        row = 0;
        while (row < w && getline(svd, line)) {
            std::istringstream iss(line);
            float v;
            int col = 0;
            while (col < w && iss >> v) {
                cout << v << ' ';
                S[row*w + col] = floatToHalf(v);
                ++col;
            }
            cout << endl;
            ++row;
        }
        cout << endl;
        
        // print the V' matrix
        cout << "V' Matrix:\n";
        row = 0;
        while (row < w && getline(svd, line)) {
            std::istringstream iss(line);
            float v;
            int col = 0;
            while (col < w && iss >> v) {
                cout << v << ' ';
                V[row*w + col] = floatToHalf(v);
                ++col;
            }
            cout << endl;
            ++row;
        }
        cout << endl;
        
        // Make sure K is less than or equal to maximum rank
        int k = std::min(rank,w);
        
        // Write the rank to the binary file
        char bufferRank[1] = {static_cast<char>(k)};
        fwrite (bufferRank , sizeof(char), sizeof(bufferRank), binFile);
        
        cout << "K is " << k << endl;
//        return;
        
//        half* uBuff = new half[k*h];
        cout << "// write " << k << " column(s) of U" << endl;
        for (int j=0; j<k; ++j) {
            for (int i=0; i<h; ++i) {
                cout << U[i*w+j] << endl;
                fwrite(&U[i*w+j], sizeof(half), 1, binFile);
//                uBuff[j*k+i] = U[i*w+j]
            }
            cout << "----\n";
        }
        
//        half* sBuff = new half[k];
        cout << "// write " << k << " value(s) of S" << endl;
        for (int i=0; i<k; ++i) {
            cout << S[i*w+i] << " | ";
            fwrite(&S[i*w+i], sizeof(half), 1, binFile);
        }
        cout << endl;
        
//        half* vBuff = new half[k*w];
        cout << "// write " << k << " row(s) of V'" << endl;
        for (int j=0; j<k; ++j) {
            for (int i=0; i<w; ++i) {
                cout << V[j*w+i] << ' ';
                fwrite(&V[j*w+i], sizeof(half), 1, binFile);
            }
            cout << endl;
        }
        cout << endl;
    }

    // Close binary file
    fclose (binFile);
    
    // Close all file streams
    header.close();
    svd.close();
    return;
}

int PGMImage::loadSVD(const char *file)
{
    FILE* binFile = fopen(file, "rb" );
    if (!binFile) {
        printf("Error: could not open file %s\n", file);
        return -1;
    }
    
    // Read the width, height, maxValue, and rank from the header buffer
    unsigned char * headerBuffer = new unsigned char[6];
    fread(headerBuffer, sizeof(char), 6, binFile);
    
    // lower half of width
    width = static_cast<int>(headerBuffer[0]);
    // upper half of width
    width += 256*static_cast<int>(headerBuffer[1]);
    // lower half of height
    height = static_cast<int>(headerBuffer[2]);
    // upper half of height
    height += 256*static_cast<int>(headerBuffer[3]);
    values = new int[getSize()];
    // max value
    max = static_cast<int>(headerBuffer[4]);
    // Rank
    int k = static_cast<int>(headerBuffer[5]);
    
    cout << "Width: " << width << "\nHeight: " << height << "\nMax: " << max << "\nRank: " << k << endl;
    
    
    half* uBuffer = new half[k*height];
    fread(uBuffer, sizeof(half), k*height, binFile);
    
    half* sBuffer = new half[k];
    fread(sBuffer, sizeof(half), k, binFile);
    
    half* vBuffer = new half[k*width];
    fread(vBuffer, sizeof(half), k*width, binFile);
    
    /*
    cout << "U Vector:";
    for (int i=0; i<k*height; ++i) {
        cout << "  " << uBuffer[i] << endl;
    }
    cout << "\n\nU Vector:";
    for (int i=0; i<k; ++i) {
        cout << "  " << sBuffer[i] << endl;
    }
    cout << "\n\nU Vector:";
    for (int i=0; i<k*width; ++i) {
        cout << "  " << vBuffer[i] << endl;
    }
     */
    
    double *U, *S, *V;
    U = new double[height*width] (); // all elements 0
    S = new double[width*width] (); // all elements 0
    V = new double[width*width] (); // all elements 0
    
    for (int i=0; i<k; ++i) {
        for (int j=0; j<height; ++j) {
            U[j*width+i] = halfToFloat(uBuffer[i*height+j]);
        }
    }
    
    for (int i=0; i<k; ++i) {
        S[i*width+i] = halfToFloat(sBuffer[i]);
    }
    
    for (int i=0; i<k; ++i) {
        for (int j=0; j<width; ++j) {
            V[i*width+j] = halfToFloat(vBuffer[i*width+j]);
        }
    }

//    U [ height * width ]
//    S [ width * width ]
//    V [ width * width ]
    
    cout << "U Matrix:\n";
    for (int i=0; i<height; ++i) {
        for (int j=0; j<width; ++j) {
            cout << "\t" << U[i*width+j];
        }
        cout << endl;
    }
    
//    for (int i=0; i<height*width; ++i) {
//        cout << U[i] << ' ';
//    }
//    cout << endl;

    cout << "\nS Matrix:\n";
    for (int i=0; i<width; ++i) {
        for (int j=0; j<width; ++j) {
            cout << "\t" << S[i*width+j];
        }
        cout << endl;
    }
    
//    for (int i=0; i<width*width; ++i) {
//        cout << S[i] << ' ';
//    }
//    cout << endl;
    
    cout << "\nV' Matrix:\n";
    for (int i=0; i<width; ++i) {
        for (int j=0; j<width; ++j) {
            cout << "\t" << V[i*width+j];
        }
        cout << endl;
    }
    
    //    U [ height * width ]
    //    S [ width * width ]
    //    V [ width * width ]
    
    // B [ height * width ] = US;
    double * B = new double[height*width] ();
    
    for (int bR=0; bR<height; ++bR) {
        for (int bC=0; bC<width; ++bC) {
            
            for (int uC=0; uC < width; ++uC) {
                B[bR*width+bC] += U[bR*width+uC] * S[uC*width+bC];
            }
        }
    }
    
    cout << "\nB Matrix:\n";
    for (int i=0; i<height; ++i) {
        for (int j=0; j<width; ++j) {
            cout << "\t" << B[i*width+j];
        }
        cout << endl;
    }
    
    // X [ height * width ] = BV;
    double * X = new double[height*width] ();
    
    for (int bR=0; bR<height; ++bR) {
        for (int bC=0; bC<width; ++bC) {
            
            for (int uC=0; uC < width; ++uC) {
                X[bR*width+bC] += B[bR*width+uC] * V[uC*width+bC];
            }
        }
    }
    
    cout << "\nX Matrix:\n";
    for (int i=0; i<height; ++i) {
        for (int j=0; j<width; ++j) {
            cout << "\t" << X[i*width+j];
        }
        cout << endl;
    }
    
    for (int i=0; i<getSize(); ++i) {
        values[i] = round(X[i]);
    }
    
//    for (int i=0; i<width*width; ++i) {
//        cout << V[i] << ' ';
//    }
//    cout << endl;
    
    
    /*
    int headerBufferSize = 5;
    unsigned char * headerBuffer = new unsigned char[headerBufferSize];
    int n = 0;
    
    for (size_t bytesRead = fread(headerBuffer, sizeof(char), headerBufferSize, binFile); bytesRead > 0; bytesRead = fread(headerBuffer, sizeof(char), headerBufferSize, binFile)) {
        
        cout << "Bytes read: " << bytesRead << endl;
        for (int i=0; i < bytesRead; ++i) {
            //            cout << static_cast<int>(buffer[i]) << "  ";
            
            if (n == 0) {
                // lower half of width
                width = static_cast<int>(headerBuffer[i]);
            } else if (n == 1) {
                // upper half of width
                width += 256*static_cast<int>(headerBuffer[i]);
            } else if (n == 2) {
                // lower half of height
                height = static_cast<int>(headerBuffer[i]);
            } else if (n == 3) {
                // upper half of height
                height += 256*static_cast<int>(headerBuffer[i]);
                values = new int[getSize()];
            } else if (n == 4) {
                // max value
                max = static_cast<int>(headerBuffer[i]);
            }
            ++n;
        }
    }
    cout << endl;
     */
    
    // Done and close.
    fclose(binFile);
    return k;
}

void PGMImage::exportMatrix(const string fileName)
{
    ofstream headerFile;
    headerFile.open(fileName+"_header.txt");
    headerFile << width << ' ' << height << ' ' << max << endl;
    headerFile.close();
    
    ofstream aFile;
    aFile.open(fileName+"_matlab.m");
    
    aFile << "function generateSVD()" << endl;;
    aFile << "A = [";
    
    for (int i=0; i<height; ++i) {
        for (int j=0; j<width; ++j) {
            aFile << ' ' << values[width*i+j];
        }
        aFile << ';';
    }
    
    aFile << "];" << endl;;
    aFile << "[U,S,V] = svd(A,'econ');" << endl;
    aFile << "W = transpose(V);" << endl;
    aFile << "save('" << fileName << "_SVD.txt','U','S','W','-ascii');" << endl;
    aFile << "end" << endl;
    aFile.close();
}





#endif /* PGMImage_h */




