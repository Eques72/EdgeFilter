#ifndef IMAGECV
#define IMAGECV

//===================================================
// File: ImageCV.h
// Contents: Declaration file for ImageCV class. This class is a representation of image data and has capabilities to store, write and read images
// Author: Adrian Zarêba
//===================================================


#include <string>
#include <cstddef> //lib /w byte
#include <opencv2/imgproc/imgproc.hpp> 
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

/** 
* Representation of an image
* Is capable of storing RGB and grayscale images in folowing formats: Bmp, Png, Tiff, Jpeg 
* Image data is stored in array. Each pixel takes one cell for grayscale, or three for rgb image
* Each cell has 8bits 
*/
class ImageCV
{
	int imageSize; // = imageWidth*imageHeight*numberOfChannels
	int imageWidth;
	int imageHeight;
	std::byte* imgArray;
	bool isRGB = false;
	int numberOfChannels = 1;

	//Read image from given path. File under this path must be in correct format.
	//Results are stored in imgArray
	void readImage(std::string path);
public:

	//Constructor, reads image data form given path, use boolean param to choose between grayscale(False) and RGB(true)
	ImageCV(std::string path, bool rgb);
	//Copy constructor
	ImageCV(const ImageCV& i);
	//Constructor, which initialises empty image, sets imgArray size so it can be safely accessed
	ImageCV(int imgSize, int imgWidth, int imgHeight, bool rgb);

	//Save image under given path. Image will be automaticly saved as rgb or gs depending on isRGB value.
	//File extensions depends on last three letters from path param
	void saveImage(std::string path);
	//Set new image data (override imgArray)
	void setImage(cv::Mat m, bool RGB);

	//Getters and setters
	inline int getNumOfChannels() const { return numberOfChannels; }
	inline bool getIfIsRGB() const { return isRGB; }
	inline int getSize() const { return imageSize; }
	inline int getWidth() const { return imageWidth; }
	inline int getHeight() const { return imageHeight; }
	inline std::byte* getArray() const { return imgArray; }
	inline void setValue(unsigned int index, std::byte value) { if (index < imageSize) imgArray[index] = value; }
	inline int getValue(unsigned int index) const { index < imageSize ? imgArray[index] : std::byte(0); }
	
	//Destructor, destroys imgArray
	~ImageCV();
};

#endif // !IMAGECV