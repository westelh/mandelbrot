#include "bmp.hpp"
#include <fstream>
#include <cassert>
#include <iostream>

void bmp_write::write() {
	std::ofstream ofs(filename, std::ios::out | std::ios::binary);
	if (!ofs.is_open()) {
		std::cerr << filename << " cannot open." << '\n';
		std::terminate();
	}

	ofs.write((char*)&hd.bftype, sizeof(hd.bftype));
	ofs.write((char*)&hd.bfsize, sizeof(hd.bfsize));
	ofs.write((char*)&hd.bfreserved1, sizeof(hd.bfreserved1));
	ofs.write((char*)&hd.bfreserved2, sizeof(hd.bfreserved2));
	ofs.write((char*)&hd.bfoffbits, sizeof(hd.bfoffbits));

	ofs.write((char*)&hd.bisize, sizeof(hd.bisize));
	ofs.write((char*)&hd.biwidth, sizeof(hd.biwidth));
	ofs.write((char*)&hd.biheight, sizeof(hd.biheight));
	ofs.write((char*)&hd.biplanes, sizeof(hd.biplanes));
	ofs.write((char*)&hd.bibitcount, sizeof(hd.bibitcount));
	ofs.write((char*)&hd.bicompression, sizeof(hd.bicompression));
	ofs.write((char*)&hd.bisizeimage, sizeof(hd.bisizeimage));
	ofs.write((char*)&hd.bixpelspermeter, sizeof(hd.bixpelspermeter));
	ofs.write((char*)&hd.biypelspermeter, sizeof(hd.biypelspermeter));
	ofs.write((char*)&hd.biclrused, sizeof(hd.biclrused));
	ofs.write((char*)&hd.biclrimportant, sizeof(hd.biclrimportant));

	assert(data.size() == hd.biheight);
	for (int i = 0; i < data.size(); i++) {
		assert(data[i].size() == hd.biwidth);
	}

	for (int i = 0; i < hd.biheight; i++) {
		for (int j = 0; j < hd.biwidth; j++) {
			ofs.write((char*)&data[i][j].b, sizeof(unsigned char));
			ofs.write((char*)&data[i][j].g, sizeof(unsigned char));
			ofs.write((char*)&data[i][j].r, sizeof(unsigned char));
		}
	}
}

void bmp_write::set_constants() {
	hd.bftype = 19778;
	hd.bfreserved1 = 0;
	hd.bfreserved2 = 0;
	hd.bfoffbits = 54;

	hd.bisize = 40;
	hd.biplanes = 1;
	hd.bibitcount = 24;
	hd.bicompression = 0;
	hd.bixpelspermeter = 0;
	hd.biypelspermeter = 0;
	hd.biclrused = 0;
	hd.biclrimportant = 0;
}

void bmp_write::set_size(unsigned int height, unsigned int width) {
	hd.biheight = height;
	hd.biwidth = width;
	hd.bisizeimage = height*width*hd.bibitcount/8;
	hd.bfsize = hd.bisizeimage + hd.bfoffbits;

	data.resize(hd.biheight);
	for (int i = 0; i < hd.biheight; i++) {
		data[i].resize(hd.biwidth);
	}
}

void bmp_write::set_data(grid data) {
	this->data = data;
	set_size(data.size(), data[0].size());
}

void bmp_read::read() {
	std::ifstream ifs(filename, std::ios::in | std::ios::binary);
	if (!ifs.is_open()) {
		std::cerr << filename << " cannot open." << '\n';
		abort();
	}
	ifs.read((char*)&hd.bftype, sizeof(hd.bftype));
	ifs.read((char*)&hd.bfsize, sizeof(hd.bfsize));
	ifs.read((char*)&hd.bfreserved1, sizeof(hd.bfreserved1));
	ifs.read((char*)&hd.bfreserved2, sizeof(hd.bfreserved2));
	ifs.read((char*)&hd.bfoffbits, sizeof(hd.bfoffbits));

	ifs.read((char*)&hd.bisize, sizeof(hd.bisize));
	ifs.read((char*)&hd.biwidth, sizeof(hd.biwidth));
	ifs.read((char*)&hd.biheight, sizeof(hd.biheight));
	ifs.read((char*)&hd.biplanes, sizeof(hd.biplanes));
	ifs.read((char*)&hd.bibitcount, sizeof(hd.bibitcount));
	ifs.read((char*)&hd.bicompression, sizeof(hd.bicompression));
	ifs.read((char*)&hd.bisizeimage, sizeof(hd.bisizeimage));
	ifs.read((char*)&hd.bixpelspermeter, sizeof(hd.bixpelspermeter));
	ifs.read((char*)&hd.biypelspermeter, sizeof(hd.biypelspermeter));
	ifs.read((char*)&hd.biclrused, sizeof(hd.biclrused));
	ifs.read((char*)&hd.biclrimportant, sizeof(hd.biclrimportant));

	data.resize(hd.biheight);
	for (int i = 0; i < hd.biheight; i++) {
		data[i].resize(hd.biwidth);
	}

	for (int i = 0; i < hd.biheight; i++) {
		for (int j = 0; j < hd.biwidth; j++) {
			ifs.read((char*)&data[i][j].b, sizeof(unsigned char));
			ifs.read((char*)&data[i][j].g, sizeof(unsigned char));
			ifs.read((char*)&data[i][j].r, sizeof(unsigned char));
		}
	}
	ifs.close();
}
