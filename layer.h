/* 
 * Copyright (C) 2011 Andreas Bertheussen.
 * All rigts reserved, although later versions might be open-source licensed.
 */

#ifndef LAYER_H
#define LAYER_H

#include <string>

class Layer {
public:
	enum Type { Conductor=0, ResistMask, PasteMask, Notation };
	enum Side { Top=0, Bottom, Internal, Meta };
	Layer();
	~Layer();
	static std::string typeToString(Layer::Type _type);
	static std::string sideToString(Layer::Side _side);
	std::string name;
	enum Type type;
	enum Side side;
        bool visible;
};

#endif
