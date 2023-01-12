#pragma once
#include <cstddef> //lib /w byte

//===================================================
// File: EdgeLib.h
// Contents: Declaration file for dynamic cpp library, contains edge filter algorithm 
// Author: Adrian Zarêba
//===================================================

#ifdef CPPLIB_EXPORTS
#define CPPLIB_API __declspec(dllexport)
#else
#define CPPLIB_API __declspec(dllimport)
#endif

//Edge filter algorithm. Takes two tables, image width, height, starting position and height(amount of picture to be converted)
//Images given in tables should be in grayscale, otherwise resoults might be wrong
//Returns: Nothing, all changes can be seen in output table
extern "C" CPPLIB_API void edgeFilterCpp(std::byte* input, std::byte* output, int imgWidth, int imgHeight, int startingRow, int height);