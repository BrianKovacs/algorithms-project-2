README.txt


### HOW TO COMPILE ###

# Navigate into the build folder
cd pgm_compressor/build/

# Run cmake and make
cmake ..
make


### HOW TO RUN ###

# Convert ASCII image.pgm to binary image_b.pgm 
./pgm-compressor 1 image.pgm

# Convert a binary image_b.pgm to ASCII image2.pgm
./pgm-compressor 2 image_b.pgm 

# Compress image with SVD to rank k
# Replace k with your choice of rank
./pgm-compressor 3 image_header.txt image_SVD.txt k

# Recover image that was compressed with SVD
./pgm-compressor 4 image_b.pgm.SVD 
