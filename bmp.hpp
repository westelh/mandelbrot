#pragma once

#include <vector>
#include <string>
#include <iostream>

class header {
private:
public:
	unsigned short bftype;
	unsigned int bfsize;
	unsigned short bfreserved1;
	unsigned short bfreserved2;
	unsigned int bfoffbits;

	unsigned int bisize;
	unsigned int biwidth;
	unsigned int biheight;
	unsigned short biplanes;
	unsigned short bibitcount;
	unsigned int bicompression;
	unsigned int bisizeimage;
	unsigned int bixpelspermeter;
	unsigned int biypelspermeter;
	unsigned int biclrused;
	unsigned int biclrimportant;
	header(
		unsigned short ftype,
		unsigned int fsize,
		unsigned short freserved1,
		unsigned short freserved2,
		unsigned short foffbits,
		unsigned int isize,
		unsigned int iwidth,
		unsigned int iheight,
		unsigned short iplanes,
		unsigned short ibitcount,
		unsigned int icompression,
		unsigned int isizeimage,
		unsigned int ixpelspermeter,
		unsigned int iypelspermeter,
		unsigned int iclrused,
		unsigned int iclrimportant
	) {
		bftype = ftype;
		bfsize = fsize;
		bfreserved1 = freserved1;
		bfreserved2 = freserved2;
		bfoffbits = foffbits;
		bisize = isize;
		biwidth = iwidth;
		biheight = iheight;
		biplanes = iplanes;
		bibitcount = ibitcount;
		bicompression = icompression;
		bisizeimage = isizeimage;
		bixpelspermeter = ixpelspermeter;
		biypelspermeter = iypelspermeter;
		biclrused = iclrused;
		biclrimportant = iclrimportant;
	}
	header() {
		bftype = 0;
		bfsize = 0;
		bfreserved1 = 0;
		bfreserved2 = 0;
		bfoffbits = 0;
		bisize = 0;
		biwidth = 0;
		biheight = 0;
		biplanes = 0;
		bibitcount = 0;
		bicompression = 0;
		bisizeimage = 0;
		bixpelspermeter = 0;
		biypelspermeter = 0;
		biclrused = 0;
		biclrimportant = 0;
	}
	void show() {
		std::cout << "bftype: " << bftype << '\n';
		std::cout << "bfsize: " << bfsize << '\n';
		std::cout << "bfreserved1: " << bfreserved1 << '\n';
		std::cout << "bfreserved2: " << bfreserved2 << '\n';
		std::cout << "bfoffbits: " << bfoffbits << '\n';
		std::cout << "bisize: " << bisize << '\n';
		std::cout << "biwidth: " << biwidth << '\n';
		std::cout << "biheight:" << biheight << '\n';
		std::cout << "biplanes: " << biplanes << '\n';
		std::cout << "bibitcount: " << bibitcount << '\n';
		std::cout << "bicompression: " << bicompression << '\n';
		std::cout << "bisizeimage: " << bisizeimage << '\n';
		std::cout << "bixpelspermeter: " << bixpelspermeter << '\n';
		std::cout << "biypelspermeter: " << biypelspermeter << '\n';
		std::cout << "biclrused: " << biclrused << '\n';
		std::cout << "biclrimportant: " << biclrimportant << '\n';
	}
};

class pixel {
private:
public:
	unsigned char r;
	unsigned char g;
	unsigned char b;
	pixel(unsigned char red, unsigned char gleen, unsigned blue): r(red), g(gleen), b(blue) {};
	pixel(){};
};

using grid = std::vector<std::vector<pixel>>;

class bmp_image {
protected:
	std::string filename;
	header hd;
	grid data;
public:
	bmp_image(std::string name):filename(name){};
};

class bmp_write : public bmp_image{
private:
public:
	bmp_write(std::string name): bmp_image(name) {
		set_constants();
	};
	void set_header(header hd) {
		this->hd = hd;
	}
	void set_data(grid data);

	void set_constants();
	void set_size(unsigned int height, unsigned int width);

	void write();
};

class bmp_read : public bmp_image{
private:
public:
	bmp_read(std::string name): bmp_image(name) {
	};
	void read();
	header get_header() {
		return hd;
	};
	grid get_data() {
		return data;
	};
};
