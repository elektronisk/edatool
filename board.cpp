/* 
 * Copyright (C) 2011 Andreas Bertheussen.
 * All rigts reserved, although later versions might be open-source licensed.
 */

#include <iostream>
#include "board.h"

Board::Board() {
	//initialize layers
	addLayer(Layer::Top, Layer::Notation, std::string("Top notation"));
	addLayer(Layer::Internal, Layer::Conductor, std::string("Top copper"), 0);
	addLayer(Layer::Internal, Layer::Conductor, std::string("Top copper"), 1);
	addLayer(Layer::Bottom, Layer::Notation, std::string("Bottom notation"));
}

Board::~Board() {

}

/*
void Board::addExternalLayer(Layer::Type _type, std::string _name) {
	
}

void Board::addInternalLayer(std::string _name, int index) {
	Layer *l = new Layer();
	l->side = Layer::Internal;
	l->type = Layer::Conductor;
	l->name = _name;
}

*/
void Board::addLayer(Layer::Side _side, Layer::Type _type, std::string _name, int index) {
	
	if (_side == Layer::Internal ) {
		if (_type != Layer::Conductor) {
			std::cout << "Tried adding non-conductor layer to internal stack" << std::endl;
			return;
		}
		//layer is internal, conductor. sanity check index.
		if (index < 0 || index > 127) {
			std::cout << "Tried adding internal conductor layer with bogus index: " << index << std::endl;
			return;
		}
	} else {
		if (_type == Layer::Conductor) { // can't have this on outer stacks
			std::cout << "Tried adding external conductor layer. Conductor can only be internal." << std::endl;
			return;
		}
		// layer is not internal conductor, but is pastemask, soldermask, silkscreen etc. Must be unique for each side.
		if (_side == Layer::Top) { // TOP LAYER CHECK
			for (int i = 0; i < this->topStack.size(); i++) {
				if (this->topStack[i]->type == _type) {
					std::cout << "Removing top stack item " << i << std::endl;
					delete this->topStack[i];
					topStack.erase(topStack.begin() + i); 
					break;
				}
			}
		} else { // BOTTOM LAYER CHECK
			for (int i = 0; i < this->bottomStack.size(); i++) {
				if (this->bottomStack[i]->type == _type) {
					std::cout << "Removing top stack item " << i << std::endl;
					delete this->bottomStack[i];
					bottomStack.erase(bottomStack.begin() + i); 
					break;
				}
			}
		}
	}

	Layer *l = new Layer();
	l->side = _side;
	l->type = _type;
	l->name = _name;
	
	switch (_side) {
		case Layer::Internal:	this->internalStack.push_back(l); break;
		case Layer::Top:		this->topStack.push_back(l); break;
		case Layer::Bottom:		this->bottomStack.push_back(l); break;
		default:
			delete l;
			std::cout << "Unrecognized side for layer: " << (int)_side << std::endl;
			return;
	}
	std::cout << "Added layer '" << _name << "' of type " << Layer::typeToString(_type) << " on side " << Layer::sideToString(_side) << std::endl;
}
