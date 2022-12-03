#ifndef EDGE
#define EDGE
#include <string>
#include <windows.h>
#include <vector>
#include <thread>
#include <chrono>
#include <cstddef>
#include "ImageCV.h"

//MAX IMAGE SIZE IS 30.000 x 30.000 or 1.000.000.000 px ???
class EdgeManager 
{
private:
	ImageCV* sourceImage = nullptr;
	ImageCV* outputImage = nullptr;
	std::string sourcePath;
	std::string outputPath;

	long timeTaken = 0;
	//HistogramCreator hC;

public:
	EdgeManager() {}

	inline long getTimeTaken() const { return timeTaken; }
	void setSourceImage(std::string path, bool isToBeRbg);
	void setSourceImage(ImageCV* img);
	ImageCV* getSourceImage() const;
	ImageCV* getOutputImage() const;
	std::string getOutputImagePath() const;
	bool runEdgeFilter(int libType, int threads);
	bool runHistogram(int& R, int& B, int& G);
	void saveImage(bool saveOutputImage, std::string path);

	~EdgeManager();
};


#endif//EDGE
