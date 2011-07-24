/* 
 * Copyright (C) 2011 Andreas Bertheussen.
 * All rigts reserved, although later versions might be open-source licensed.
 */

#include "layer.h"

Layer::Layer() {
	this->visible = true;
	this->name = "Unnamed layer";
	this->itemTree = new quadtree::Quadtree();
	this->side = Layer::Top;
	this->type = Layer::Conductor;
}
Layer::~Layer() {
	delete this->itemTree;
}

std::string Layer::typeToString(Layer::Type _type) {
	std::string s;
	switch(_type) {
		case Layer::Conductor:	s = "Conductor"; break;
		case Layer::ResistMask:	s = "Resist mask"; break;
		case Layer::PasteMask:	s = "Paste mask"; break;
		case Layer::Notation:	s = "Notation"; break;
		default:
			s = "Unknown";
	}
	return s;
}
std::string Layer::sideToString(Layer::Side _side) {
	std::string s;
	switch(_side) {
		case Layer::Top:	s = "Top"; break;
		case Layer::Bottom:	s = "Bottom"; break;
		case Layer::Internal:	s = "Internal"; break;
		case Layer::Meta:	s = "Meta"; break;
		default:
			s = "Unknown";
	}
	return s;
}