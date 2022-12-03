#include "ImageCV.h"

void ImageCV::readImage(std::string path)
{
	cv::Mat m;
	if (isRGB)
		m = cv::imread(path.c_str(), cv::IMREAD_COLOR);
	else 
		m = cv::imread(path.c_str(), cv::IMREAD_GRAYSCALE);
	
	this->imageSize = m.total() * m.channels();
	this->imgArray = new std::byte[imageSize];
	this->imageHeight = m.rows;
	this->imageWidth = m.cols;
	for (int i = 0; i < this->imageSize; i++)
		imgArray[i] = (std::byte)m.data[i];
}

ImageCV::ImageCV(std::string path, bool rgb): isRGB(rgb)
{
	if (isRGB)
		this->numberOfChannels = 3;
	else
		this->numberOfChannels = 1;
	readImage(path);
}

ImageCV::ImageCV(const ImageCV& i)
{
	this->imageHeight = i.getHeight();
	this->imageWidth = i.getWidth();
	this->imageSize = i.getSize();
	this->imgArray = new std::byte[i.getSize()];
	this->numberOfChannels = i.numberOfChannels;
	this->isRGB = i.isRGB;
	for (int it = 0; it < this->getSize(); it++) 
		this->imgArray[it] = i.getArray()[it];
}

ImageCV::ImageCV(int imgSize, int imgWidth, int imgHeight, bool rgb)
	:imageSize(imgSize), imageWidth(imgWidth), imageHeight(imgHeight), isRGB(rgb)
{
	if (isRGB)
		this->numberOfChannels = 3;
	else
		this->numberOfChannels = 1;
	imgArray = new std::byte[imgSize];
}

void ImageCV::saveImage(std::string path)
{
	cv::Mat I; 
	if(!isRGB)
		I = cv::Mat(this->imageHeight, this->imageWidth, CV_8UC1);
	else
		I = cv::Mat(this->imageHeight, this->imageWidth, CV_8UC3);

	std::memcpy(I.data, this->imgArray, this->imageSize * sizeof(std::byte));
	
	if(isRGB)
		cv::cvtColor(I,I, cv::COLOR_BGR2GRAY,1);
	cv::imwrite(path.c_str(), I);
}

void ImageCV::setImage(cv::Mat m, bool RGB)
{
	isRGB = RGB;
	if (isRGB)
		this->numberOfChannels = 3;
	else
		this->numberOfChannels = 1;

	if (imgArray != nullptr) 
		delete[] imgArray;
	
	this->imageSize = m.total() * m.channels();
	this->imageHeight = m.rows;
	this->imageWidth = m.cols;
	this->imgArray = new std::byte[imageSize];
	for (int i = 0; i < this->imageSize; i++)
	{
		imgArray[i] = (std::byte)m.data[i];
	}
}

ImageCV::~ImageCV()
{
	delete[] imgArray;
}
