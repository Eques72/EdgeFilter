#ifndef IMAGECV
#define IMAGECV

#include <string>
#include <cstddef> //lib /w byte
#include <opencv2/imgproc/imgproc.hpp> 
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

/** OBSOLETE DESCRIPTION
* Note that image data is stored in array of ints.
* Colors are stored next to each other so one pixel is stored in three next cells
* Eq: Pixel no.3 is stored in imgArray[6],imgArray[7],imgArray[8] as B,G and R
* Images always have 3 channels, there can not be an image with 1 channel(greyscale) or 4(with alpha)
*/
class ImageCV
{
	int imageSize; // = imageWidth*imageHeight*numberOfChannels
	int imageWidth;
	int imageHeight;
	std::byte* imgArray;
	bool isRGB = false;
	int numberOfChannels = 1;

	void readImage(std::string path);
public:

	ImageCV(std::string path, bool rgb);
	ImageCV(const ImageCV& i);
	ImageCV(int imgSize, int imgWidth, int imgHeight, bool rgb);

	void saveImage(std::string path);
	void setImage(cv::Mat m, bool RGB);

	inline int getNumOfChannels() const { return numberOfChannels; }
	inline bool getIfIsRGB() const { return isRGB; }
	inline int getSize() const { return imageSize; }
	inline int getWidth() const { return imageWidth; }
	inline int getHeight() const { return imageHeight; }
	inline std::byte* getArray() const { return imgArray; }
	inline void setValue(unsigned int index, std::byte value) { if (index < imageSize) imgArray[index] = value; }
	inline int getValue(unsigned int index) const { index < imageSize ? imgArray[index] : std::byte(0); }
	
	~ImageCV();
};

#endif // !IMAGECV