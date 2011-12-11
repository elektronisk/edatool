/* 
 * Copyright (C) 2011 Andreas Bertheussen.
 * All rigts reserved, although later versions might be open-source licensed.
 */

#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <string>
#include "layer.h"

class Board {
public:
	Board();
	~Board();
	void addLayer(Layer::Side _side, Layer::Type _type, std::string _name, int index= 0);
	void printStack();
private:
	std::vector<Layer *> topStack;			// top silkscreen, masks, drawings
	std::vector<Layer *> internalStack;		// conductors, first element is top copper, last is bottom copper
	std::vector<Layer *> bottomStack;		// bottom silkscreen, masks, drawings
	std::vector<Layer *> metaStack;			// 
};

#endif
