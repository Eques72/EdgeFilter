// EdgeLib.h
#pragma once
#include <cstddef> //lib /w byte

#ifdef CPPLIB_EXPORTS
#define CPPLIB_API __declspec(dllexport)
#else
#define CPPLIB_API __declspec(dllimport)
#endif

extern "C" CPPLIB_API void edgeFilterCpp(std::byte* input, std::byte* output, int imgWidth, int imgHeight, int startingRow, int height);