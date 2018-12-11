#include "stdafx.h"
#include "btreedump.h"
#include <string>
#include <strstream>
#include <list>

namespace btreedump {

using std::string;
using std::strstream;

string b_treedump::dump (btree::b_node<int>* node) {
	strstream d;
	if (node == NULL) {
		node = root;
		d << "<html>\n<head>\n<style type=\"text/css\">\n";
		d << "p.c1 {text-align: center}\n</style>\n</head>\n\n";
		d << "<body>\n";
	}
	d << "<table border=\"2\" cellspacing=\"2\" cellpadding=\"2\" width=\"100%\">";
	d << "<tr>";
	std::list<int>::iterator it = node->keys.begin();
	for (; it != node->keys.end(); ++it) {
		d << "<td valign=\"top\"";
		//if (!node->pointers.empty()) {
		//	d << " colspan=\"" << node->pointers.size() << "\"";
		//}
		d << ">";
		d << "<p class=\"c1\">";
		d << *it;
		d << "</p>";
        d << "</td>";
	}
	d << "</tr></table>";
	if (!node->pointers.empty()) {
		d << "<table border=\"2\" cellspacing=\"2\" cellpadding=\"2\" width=\"100%\">";
		d << "<tr>";
		std::list<btree::b_node<int> *>::iterator it1 = node->pointers.begin();
		for (; it1 != node->pointers.end(); ++it1) {
			d << "<td valign=\"top\">";
	        d << dump(*it1);
			d << "</td>";
		}
		d << "</tr>";
		d << "</table>";
	}
	if (node == root) {
		d << "</body>";
		d << "</html>" << std::endl << '\0';
		d.flush();
	} else {
		d << std::endl << '\0';
		d.flush();
	}
	string d1 = d.str();
	return d1;
}

}
