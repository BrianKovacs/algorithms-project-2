//
//  main.cpp
//  pgm_compressor
//
//  Created by Brian Kovacs on 3/31/18.
//  Copyright © 2018 Brian Kovacs. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "PGMImage.h"
#include "half.h"

using namespace std;

void option1(const char* file);
void option2(const char* file);
void option3(const char* header, const char* svd, int rank);
void option4(const char* file);
void exportMatrix(const char* file);
void calculateFNorm(const char* file1, const char* file2);
void rotate(const char* file);
void chop(const char* file);

int main(int argc, const char * argv[])
{
    if (argc >= 3 && strncmp (argv[1], "1", 2) == 0) {
        cout << "Option 1...\n";
        option1(argv[2]);
    }
    else if (argc >= 3 && strncmp (argv[1], "2", 2) == 0) {
        cout << "Option 2...\n";
        option2(argv[2]);
    }
    else if (argc >= 5 && strncmp (argv[1], "3", 2) == 0) {
        cout << "Option 3...\n";
        std::istringstream iss(argv[4]);
        int rank;
        iss >> rank;
        option3(argv[2], argv[3], rank);
    }
    else if (argc >= 3 && strncmp (argv[1], "4", 2) == 0) {
        cout << "Option 4...\n";
        option4(argv[2]);
    }
    else if (argc >= 3 && strncmp (argv[1], "5", 2) == 0) {
        cout << "Export matrix...\n";
        exportMatrix(argv[2]);
    }
    else if (argc >= 4 && strncmp (argv[1], "6", 2) == 0) {
        calculateFNorm(argv[2], argv[3]);
    }
    else if (argc >= 3 && strncmp (argv[1], "7", 2) == 0) {
        cout << "Rotate matrix...\n";
        rotate(argv[2]);
    }
    else if (argc >= 3 && strncmp (argv[1], "8", 2) == 0) {
        cout << "Chop matrix...\n";
        chop(argv[2]);
    }
    else {
        cout << "Invalid arguments\n";
    }
    
    return 0;
}

void option1(const char* file)
{
//    cout << file << endl;
    string newFile;
    string str(file);
    size_t found = str.find_last_of(".pgm");
    if (found != string::npos) {
        newFile = str.substr(0,found-3) + "_b.pgm";
    } else {
        newFile = str + "_b.pgm";
    }
//    cout << newFile << endl;
    
    PGMImage i;
    i.loadASCII(file);
    i.saveBinary(newFile.c_str());
    
    streampos begin,end;
    
    ifstream original (file, ios::binary);
    begin = original.tellg();
    original.seekg (0, ios::end);
    end = original.tellg();
    original.close();
    streampos originalSize = end-begin;
    
    ifstream compressed (newFile, ios::binary);
    begin = compressed.tellg();
    compressed.seekg (0, ios::end);
    end = compressed.tellg();
    compressed.close();
    streampos compressedSize = end-begin;
    
    cout << file << ": " << (originalSize) << " bytes.\n";
    cout << newFile << ": " << (compressedSize) << " bytes.\n";
    cout << "Compression rate: " << 100*((originalSize - compressedSize) / (1.0 * originalSize)) << "%.\n\n";
}

void option2(const char* file)
{
    cout << file << endl;
    string newFile;
    string str(file);
    size_t found = str.find_last_of("_b.pgm");
    if (found != string::npos) {
        newFile = str.substr(0,found-5) + "2.pgm";
    } else {
        cout << "Error: The file name should end with \"_b.pgm\"\n";
        return;
    }
    cout << newFile << endl;
    
    PGMImage i;
    i.loadBinary(file);
    i.saveASCII(newFile.c_str());
}

void option3(const char* header, const char* svd, int rank)
{
    string oldFile = "";
    string newFile;
    string str(header);
    size_t found = str.find("_header.txt");
//    std::cout << "found: " << found << endl;
    if (found != string::npos) {
        oldFile = str.substr(0,found) + ".pgm";
        newFile = str.substr(0,found) + "_b.pgm.SVD";
    } else {
        newFile = "image_b.pgm.SVD";
    }
//    cout << newFile << endl;
    
    PGMImage::saveSVD(header, svd, newFile, rank);
    
    
    if (oldFile != "") {
        streampos begin,end;
        
        ifstream original (oldFile, ios::binary);
        begin = original.tellg();
        original.seekg (0, ios::end);
        end = original.tellg();
        original.close();
        streampos originalSize = end-begin;
        
        ifstream compressed (newFile, ios::binary);
        begin = compressed.tellg();
        compressed.seekg (0, ios::end);
        end = compressed.tellg();
        compressed.close();
        streampos compressedSize = end-begin;
        
        cout << oldFile << ": " << (originalSize) << " bytes.\n";
        cout << newFile << ": " << (compressedSize) << " bytes.\n";
        cout << "Compression rate: " << 100*((originalSize - compressedSize) / (1.0 * originalSize)) << "%.\n\n";
    }
}

void option4(const char* file)
{
//    cout << file << endl;
    string newFile;
    string str(file);
    size_t found = str.find("_b.pgm.SVD");
    if (found != string::npos) {
        newFile = str.substr(0,found) + "_";
    } else {
        cout << "Error: The file name sould end with \"_b.pgm.SVD\"\n";
        return;
    }
//    cout << newFile << endl;
    
    PGMImage i;
    int rank = i.loadSVD(file);
    
    if (rank < 0)
        return;
    
    newFile += to_string(rank) + ".pgm";
    i.saveASCII(newFile.c_str());
}

void exportMatrix(const char* file)
{
    cout << file << endl;
    string newFile;
    string str(file);
    size_t found = str.find_last_of(".pgm");
    if (found != string::npos) {
        newFile = str.substr(0,found-3);
    } else {
        newFile = str;
    }
    cout << newFile << endl;
    
    PGMImage i;
    i.loadASCII(file);
    i.exportMatrix(newFile);
}

void calculateFNorm(const char* file1, const char* file2)
{
    PGMImage a, b;
    a.loadASCII(file1);
    b.loadASCII(file2);
    
    double norm = a.fNorm(b);
    cout << "FNorm: ||" << file1 << " - " << file2 << "|| = " << norm << endl;
}

void rotate(const char* file)
{
    string newFile;
    string str(file);
    size_t found = str.find_last_of(".pgm");
    if (found != string::npos) {
        newFile = str.substr(0,found-3) + "_rotate.pgm";
    } else {
        newFile = str + "_rotate.pgm";
    }
    //    cout << newFile << endl;
    
    PGMImage img;
    img.loadASCII(file);
    PGMImage r;
    r.width = img.height;
    r.height = img.width;
    r.max = img.max;
    r.values = new int[img.getSize()];
    
    int n = 0;
    for (int i=0; i<img.width; ++i) {
        for (int j=0; j<img.height; ++j) {
            r.values[n] = img.values[i+j*img.width];
            ++n;
        }
    }
    
    r.saveASCII(newFile.c_str());
}

void chop(const char* file)
{
    string newFile;
    string str(file);
    size_t found = str.find_last_of(".pgm");
    if (found != string::npos) {
        newFile = str.substr(0,found-3) + "_chop.pgm";
    } else {
        newFile = str + "_chop.pgm";
    }
    
    PGMImage img;
    img.loadASCII(file);
    PGMImage chop;
    chop.width = img.width / 2;
    chop.height = img.height;
    chop.max = img.max;
    chop.values = new int[chop.getSize()];
    
    int n = 0;
    for (int i=0; i<chop.height; ++i) {
        for (int j=0; j<chop.width; ++j) {
            chop.values[chop.width*i + j] = img.values[img.width*i + j];
            ++n;
        }
    }
    
    chop.saveASCII(newFile.c_str());
}


