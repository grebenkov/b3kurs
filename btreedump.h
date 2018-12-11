#ifndef BTREEDUMP_H
#define BTREEDUMP_H

#include "btree.h"
#include <string>
#include "stdafx.h"
//#include <strstream>

namespace btreedump {

class b_treedump : public btree::b_tree<int, 2>  {
public:
	std::string dump (btree::b_node<int>* node = NULL);
};


}


#endif // BTREEDUMP_H
