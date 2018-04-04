//
//  main.cpp
//  pgm_compressor
//
//  Created by Brian Kovacs on 3/31/18.
//  Copyright © 2018 Brian Kovacs. All rights reserved.
//

#include <iostream>
#include <bitset>
#include "PGMImage.h"

using namespace std;

void option1(const char* file);
void option2(const char* file);
void option3(const char* header, const char* svd, int rank);
void option4(const char* file);
void exportMatrix(const char* file);

int main(int argc, const char * argv[])
{
    
//    ifstream file;
//    file.open("myFile.txt");
//    string line;
//    getline(file, line);
//    cout << line << endl;
//    istringstream iss(line);
//    half num;
//    iss >> num;
//    cout << "Number: " << num << endl;
//    return 0;

//    float num = 3.14159265359;
//    cout << "Number: " << num << endl;
//
//    // Binary file to write into
//    string myFile = "binTest.bin";
//    FILE * binFile = fopen(myFile.c_str(), "wb");
//
//    fwrite (&num , sizeof(float), sizeof(num), binFile);
//
//    // Close binary file
//    fclose (binFile);
//
//    FILE* binFile2 = fopen(myFile.c_str(), "rb" );
//    if (!binFile2) {
//        printf("Error: could not open file %s\n", myFile.c_str());
//        return -1;
//    }
//
//    float* numBuff = new float;
//    fread(numBuff, sizeof(double), sizeof(numBuff), binFile);
//
//    cout << "Number: " << *numBuff << endl;
//
//    return 0;
    
    if (false) {

        float num = 3.1415926535914159265359141592653591415926535914159265359;
        cout << "Size: " << sizeof(__INT16_TYPE__) << endl;
        cout << "Size: " << sizeof(float) << endl;
        cout << "Number: " << num << endl;
        
        // Binary file to write into
        string myFile = "binTest.bin";
        FILE * binFile = fopen(myFile.c_str(), "wb");
        
        fwrite (&num , sizeof(float), 1, binFile);
        
        // Close binary file
        fclose (binFile);
        
        FILE* binFile2 = fopen(myFile.c_str(), "rb" );
        if (!binFile2) {
            printf("Error: could not open file %s\n", myFile.c_str());
            return -1;
        }
        
        float* numBuff = new float;
        fread(numBuff, sizeof(double), 1, binFile);
        
        cout << "Number: " << *numBuff << endl;
        
        unsigned short short1 = 4;
        bitset<16> bitset1{short1};   // the bitset representation of 4
        cout << bitset1 << endl;  // 0000000000000100
        
    //    memcpy(<#void *__dst#>, num, <#size_t __n#>)
        cout << "A float is " << sizeof(float) << " bytes." << endl;
        cout << "An int is " << sizeof(int) << " bytes." << endl;
        
        unsigned int n;
        memcpy(&n, &num, sizeof(float));
        bitset<32> b1{n};
        cout << b1 << endl;
        
        float test1;
        memcpy(&test1, &n, sizeof(float));
        cout << "test1: " << test1 << endl;
        
        n = n >> 10;
        n = n << 10;
        bitset<32> b2{n};
        cout << b2 << endl;
        
        float test2;
        memcpy(&test2, &n, sizeof(float));
        cout << "test2: " << test2 << endl;
        
        
        
        float flt = num;
        int     fltInt32;
        short   fltInt16;
        memcpy( &fltInt32, &flt, sizeof( float ) );
        
        fltInt16    =  ((fltInt32 & 0x7fffffff) >> 13) - (0x38000000 >> 13);
        fltInt16    |= ((fltInt32 & 0x80000000) >> 16);
        
        unsigned short nnn;
        memcpy(&nnn, &fltInt16, sizeof(short));
        bitset<16> b3{nnn};
        cout << b3 << endl;
        cout << "===========================" << endl;
    }
    
    if (0) {
        float num = 314.15926535914159265359141592653591415926535914159265359;
        cout << "Number: " << num << endl;
        
        unsigned int n;
        memcpy(&n, &num, sizeof(float));
        bitset<32> b1{n};
        cout << b1 << endl;
        
        // mask it off
        n = (n & 4236238848);
        
        float test1;
        memcpy(&test1, &n, sizeof(float));
        cout << "test1: " << test1 << endl;
        bitset<32> b2{n};
        cout << b2 << endl;
        cout << "===========================" << endl;
    }
    if (0) {
        float num = 31.415926535914159265359141592653591415926535914159265359;
        cout << "Number: " << num << endl;
        
        unsigned int n;
        memcpy(&n, &num, sizeof(float));
        bitset<32> b1{n};
        cout << b1 << endl;
        
        // mask it off
        //        n = (n + (1<<23));
        n = (n & 4236238848);
        n = (n + (7<<23));
        
        float test1;
        memcpy(&test1, &n, sizeof(float));
        cout << "test1: " << test1 << endl;
        bitset<32> b2{n};
        cout << b2 << endl;
        cout << "===========================" << endl;
    }
    if (0) {
        float num = 31.415926535914159265359141592653591415926535914159265359;
        cout << "Number: " << num << endl;
        
        unsigned int n;
        memcpy(&n, &num, sizeof(float));
        bitset<32> b1{n};
        cout << b1 << endl;
        
        
        int     fltInt32;
        short   fltInt16;
        memcpy( &fltInt32, &num, sizeof( float ) );
        
        fltInt16    =  ((fltInt32 & 0x7fffffff) >> 13) - (0x38000000 >> 13);
        fltInt16    |= ((fltInt32 & 0x80000000) >> 16);
        
        unsigned short nnn;
        memcpy(&nnn, &fltInt16, sizeof(short));
        bitset<16> b3{nnn};
        cout << b3 << endl;
        
        n = 194838528;
        n = 167460864;
        n += (112<<23);
        bitset<32> b2{n};
        cout << b2 << endl;
        
        float newNum;
        memcpy(&newNum, &n, sizeof(float));
        cout << newNum << endl;
        
        
        
        
//        // mask it off
//        //        n = (n + (1<<23));
//        n = (n & 4236238848);
//        n = (n + (7<<23));
//
//        float test1;
//        memcpy(&test1, &n, sizeof(float));
//        cout << "test1: " << test1 << endl;
//        bitset<32> b2{n};
//        cout << b2 << endl;
//        cout << "===========================" << endl;
    }
    if (true) {
        float num = 3141.5926535914159265359141592653591415926535914159265359;
        cout << "Number: " << num << endl;
        
        unsigned int n;
        memcpy(&n, &num, sizeof(float));
        bitset<32> b1{n};
        cout << b1 << endl;
        
        
        int     fltInt32;
        short   fltInt16;
        memcpy( &fltInt32, &num, sizeof( float ) );
        
        fltInt16 = ((fltInt32 - 939524096) >> 13); // subtract offset and shift
        fltInt16 = (fltInt16 & 32767); // mask 0111111111111111
        fltInt16 |= ((fltInt32 >> 16) & 32768); // shift and mask 1000000000000000
        
        unsigned short nnn;
        memcpy(&nnn, &fltInt16, sizeof(short));
        bitset<16> b3{nnn};
        cout << b3 << endl;
        
//        n = 194838528;
//        n = 167460864;
//        n += (112<<23);
//        bitset<32> b2{n};
//        cout << b2 << endl;
        int getItBack;
        
        getItBack =
        ((fltInt16 & 32768) << 16) | // mask sign and shift 16
        (((fltInt16 & 32767) << 13) + 939524096) ; // mask exponent and fraction, shift, and add offset.
        
        float recover;
        
        unsigned int fn;
        memcpy(&fn, &getItBack, sizeof(float));
        memcpy(&recover, &getItBack, sizeof(float));
        cout << recover << endl;
        bitset<32> b4{fn};
        cout << b4 << endl;
        
        
        
        
        //        // mask it off
        //        //        n = (n + (1<<23));
        //        n = (n & 4236238848);
        //        n = (n + (7<<23));
        //
        //        float test1;
        //        memcpy(&test1, &n, sizeof(float));
        //        cout << "test1: " << test1 << endl;
        //        bitset<32> b2{n};
        //        cout << b2 << endl;
        //        cout << "===========================" << endl;
    }
    
    

    return 0;
    
    
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
        newFile = str.substr(0,found) + "_";
    } else {
        cout << "Error: The file name sould end with \"_b.pgm.SVD\"\n";
        return;
    }
    cout << newFile << endl;
    
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
