#ifndef EDGE
#define EDGE
#include <string>
#include <windows.h>
#include <vector>
#include <thread>
#include <chrono>
#include <cstddef>
#include <fstream>
#include "ImageCV.h"

//===================================================
// File: EdgeManager.h
// Contents: Declaration file for EdgeManager class. Servers as main model layer executive. Provides all methods to run filtering algorithms
// Loads and uses dll libraries: CppLib and AsmLib
// Author: Adrian Zarêba
//===================================================

//Servers as main model layer executive. Provides all methods to run filtering algorithms
class EdgeManager 
{
private:
	ImageCV* sourceImage = nullptr;
	ImageCV* outputImage = nullptr;
	std::string sourcePath;
	std::string outputPath;

	long timeTaken = 0;

public:
	//Default constructor
	EdgeManager() {}

	//Getters and setters
	inline long getTimeTaken() const { return timeTaken; }
	void setSourceImage(std::string path, bool isToBeRbg);
	void setSourceImage(ImageCV* img);
	ImageCV* getSourceImage() const;
	ImageCV* getOutputImage() const;
	std::string getOutputImagePath() const;

	//runs an edge filtering algorithm. Input data is taken from field sourceImage, output is stored in outputImage
	//Params: libtype - pass 0 if an CppLib is to be used or 1 if AsmLib is to be used
	//	threads - specify number of threads to be used while proccessing the image
	//Returns: True if operation was succesful, Time taken to run the algorithm is stored in timeTaken field
	bool runEdgeFilter(int libType, int threads);

	//Analyses sourceImage and calculates percentage values of red,green and blue in this image.
	//Image must be in color format, which means that ImageCV.isRBG = True
	//Returns: nothing, results are held in passed references to R, B ang G integers
	bool runHistogram(int& R, int& B, int& G);

	//Passes and verifies arguments to ImageCV, to save an image
	//Use boolean param to specify if output or source image is to be saved (see fields in this class)
	void saveImage(bool saveOutputImage, std::string path);

	//Destructor, safely deletes instances of ImageCV 
	~EdgeManager();
};


#endif//EDGE
