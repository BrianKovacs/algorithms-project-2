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
void option2(const char* file);
void option3(const char* header, const char* svd, int rank);
void option4(const char* file);
void exportMatrix(const char* file);

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
    else {
        cout << "Invalid arguments\n";
    }
    
    return 0;
}

void option1(const char* file)
{
    cout << file << endl;
    string newFile;
    string str(file);
    size_t found = str.find_last_of(".pgm");
    if (found != string::npos) {
        newFile = str.substr(0,found-3) + "_b.pgm";
    } else {
        newFile = str + "_b.pgm";
    }
    cout << newFile << endl;
    
    PGMImage i;
    i.loadASCII(file);
    i.saveBinary(newFile.c_str());
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
        cout << "Error: The file name sould end with \"_b.pgm\"\n";
        return;
    }
    cout << newFile << endl;
    
    PGMImage i;
    i.loadBinary(file);
    i.saveASCII(newFile.c_str());
}

void option3(const char* header, const char* svd, int rank)
{
    string newFile;
    string str(header);
    size_t found = str.find("_header.txt");
    std::cout << "found: " << found << endl;
    if (found != string::npos) {
        newFile = str.substr(0,found) + "_b.pgm.SVD";
    } else {
        newFile = "image_b.pgm.SVD";
    }
    cout << newFile << endl;
    
    PGMImage::saveSVD(header, svd, newFile, rank);
}

void option4(const char* file)
{
    cout << file << endl;
    string newFile;
    string str(file);
    size_t found = str.find("_b.pgm.SVD");
    if (found != string::npos) {
        newFile = str.substr(0,found) + "_k.pgm";
    } else {
        cout << "Error: The file name sould end with \"_b.pgm.SVD\"\n";
        return;
    }
    cout << newFile << endl;
    
    PGMImage i;
    i.loadSVD(file);
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
