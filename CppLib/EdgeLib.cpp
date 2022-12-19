#include "pch.h" // use stdafx.h in Visual Studio 2017 and earlier
#include "EdgeLib.h"

void edgeFilterCpp(std::byte* input, std::byte* output, int imgWidth, int imgHeight, int startingRow, int height) {
	int matrix[9] = { 0,1,0,1,-4,1,0,1,0 };

	for (int y = startingRow; y < height + startingRow; y++)
		for (int x = 0; x < imgWidth; x++)
		{
			int center = y * imgWidth + x;
			int indexMatrix[9] = {
				center - imgWidth - 1,
				center - imgWidth ,
				center - imgWidth + 1,
				center - 1,
				center,
				center + 1,
				center + imgWidth - 1 ,
				center + imgWidth,
				center + imgWidth + 1 };

			int newPixel = (int)input[indexMatrix[0]] * matrix[0] + (int)input[indexMatrix[1]] * matrix[1] + (int)input[indexMatrix[2]] * matrix[2] +
				(int)input[indexMatrix[3]] * matrix[3] + (int)input[indexMatrix[4]] * matrix[4] + (int)input[indexMatrix[5]] * matrix[5] +
				(int)input[indexMatrix[6]] * matrix[6] + (int)input[indexMatrix[7]] * matrix[7] + (int)input[indexMatrix[8]] * matrix[8];
			if (newPixel > 200)
				newPixel = 255;
			else if (newPixel <= 0)
				newPixel = 0;
			output[indexMatrix[4]] = (std::byte)newPixel;
		}
}
