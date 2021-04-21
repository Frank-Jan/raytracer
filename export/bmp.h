//
// Created by FJ on 26-2-2021.
//

#ifndef RAYTRACER_BMP_H
#define RAYTRACER_BMP_H

#include <stdio.h>


const int BYTES_PER_PIXEL = 3; /// red, green, & blue
const int FILE_HEADER_SIZE = 14;
const int INFO_HEADER_SIZE = 40;

void generateBitmapImage(unsigned char* image, int height, int width, char* imageFileName);
unsigned char* createBitmapFileHeader(int height, int stride);
unsigned char* createBitmapInfoHeader(int height, int width);


#endif //RAYTRACER_BMP_H
