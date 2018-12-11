#ifndef BTREE_H
#define BTREE_H

#include <list>
#include <iostream>
#include <algorithm>

namespace btree {

template <typename T>
struct b_node {
	~b_node () {
		if (!pointers.empty()) {
			std::list<b_node<T> *>::iterator it;
			for (it = pointers.begin(); it != pointers.end(); ++it) {
				delete *it;
			}
		}
	}
	b_node<T> *parent;
	std::list<T> keys;
	std::list<b_node<T> *> pointers;
};

template <typename T, int _MIN_KEY>
class b_tree {
public:
	b_tree () : min_key(_MIN_KEY),
				max_key(_MIN_KEY * 2) {
		root = new b_node<T>;
		root->parent = NULL;
	};
	~b_tree () {
		delete root;
	}
	bool insert (T key);
	bool remove (T key);
	T find (T key);
protected:
	const int min_key;
	const int max_key;
	b_node<T>* root;
	void insert_to_node (T key, b_node<T>* node, b_node<T>* left=NULL, b_node<T>* right=NULL);
	void delete_from_node (T key, b_node<T>* node);
	void split_node (b_node<T>* node);
	void joining (b_node<T>* node);
	void get_neighbours (b_node<T>* node, b_node<T>* parent, b_node<T>** left, b_node<T>** right);
	void ensure_tree_conformance (b_node<T>* node);
	b_node<T>* find_key (T key, b_node<T>* node = NULL);
};

template <typename T, int _MIN_KEY>
b_node<T>* b_tree<T,_MIN_KEY>::find_key(T key, b_node<T>* node = NULL) {
	if (node == NULL) {
		node = root;
	}
	if (node->pointers.empty()) {
		return node;
	}
	std::list<T>::size_type listsize = node->keys.size();
	if (listsize != 0) {
		int i;
		std::list<T>::iterator it = node->keys.begin();
		for (i=0; i < listsize; ++i) {
			if (*it > key) {
				std::list<b_node<T> *>::iterator it1 = node->pointers.begin();
				int k;
				for (k=0; k<i; ++k) {
					++it1;
				}
				return find_key(key, *it1);
			} else if (*it == key) {
				return node;
			}
			++it;
		}
		if (!node->pointers.empty()) {
			std::list<b_node<T> *>::iterator itlast = node->pointers.end();
			--itlast;
			return find_key(key, *itlast);
		} else {
			return node;
		}
	} else {
		return node;
	}
}

template <typename T, int _MIN_KEY>
T b_tree<T,_MIN_KEY>::find(T key) {
    b_node<T>* nod = find_key(key);
	std::list<T>::iterator it = std::find(nod->keys.begin(), nod->keys.end(), key);
	if (it == nod->keys.end()) {
		return NULL;
	} else {
		return *it;
	}	
}

template <typename T, int _MIN_KEY>
bool b_tree<T,_MIN_KEY>::insert(T key) {
	b_node<T>* nod = find_key(key);
	std::list<T>::iterator it = std::find(nod->keys.begin(), nod->keys.end(), key);
	if (it != nod->keys.end()) {
		return false;
	} else {
		insert_to_node(key, nod);
		return true;
	}
}

template <typename T, int _MIN_KEY>
void b_tree<T,_MIN_KEY>::insert_to_node(T key, b_node<T>* node, 
							   b_node<T>* left=NULL, b_node<T>* right=NULL) {
	int i;
	int j=0;
	std::list<T>::iterator it = node->keys.begin();
	for (i=0;i<node->keys.size(); ++i) {
		if (*it > key) {
			break;
		}
		++it;
		++j;
	}
	node->keys.insert(it,key);
	if (left!=NULL) {
		std::list<b_node<T> *>::iterator it1 = node->pointers.begin();
		if (it1==node->pointers.end()) {
			b_node<T>* temp = NULL;
			node->pointers.push_front(temp);
			it1 = node->pointers.begin();
		}
		for (i=0;i<j; ++i) {
			++it1;
		}
		*it1 = left;
		b_node<T>* n1 = right;
		++it1;
		node->pointers.insert(it1,n1);
	}
	if (node->keys.size() > max_key) {
		split_node(node);
	}
}

template <typename T, int _MIN_KEY>
void b_tree<T,_MIN_KEY>::split_node(b_node<T>* node) {
    int i;
	std::list<T>::iterator midkey = node->keys.begin();
	std::list<b_node<T> *>::iterator midpkey;
	if (node->pointers.empty()) {
		midpkey = NULL;
	} else {
		midpkey = node->pointers.begin();
	}	
	for (i=0;i < min_key ; ++i) {
		++midkey;
		if (midpkey != NULL) ++midpkey;
	}
	std::list<T>::iterator leftkey = midkey; 
	std::list<T>::iterator rightkey = midkey; 
	std::list<T>::iterator endkey = node->keys.end(); 
	//--leftkey; 
	++rightkey; 
	//--endkey;
	std::list<b_node<T> *>::iterator leftpkey = NULL; 
	std::list<b_node<T> *>::iterator rightpkey = NULL; 
	std::list<b_node<T> *>::iterator endpkey = NULL; 
	if (midpkey != NULL) {
		leftpkey = midpkey; 
		rightpkey = midpkey; 
		endpkey = node->pointers.end(); 
		++leftpkey;
		++rightpkey; 
		//--endpkey;
	}
	b_node<T>* lspl = new b_node<T>;
	b_node<T>* rspl = new b_node<T>;
	lspl->keys.splice(lspl->keys.begin(), node->keys, node->keys.begin(), leftkey);
	rspl->keys.splice(rspl->keys.begin(), node->keys, rightkey, endkey);
	if (midpkey != NULL) {
		lspl->pointers.splice(lspl->pointers.begin(), node->pointers, node->pointers.begin(), leftpkey);
		rspl->pointers.splice(rspl->pointers.begin(), node->pointers, rightpkey, endpkey);
		std::list<b_node<T> *>::iterator spl;
		for (spl = lspl->pointers.begin(); spl!=lspl->pointers.end(); ++spl) {
			(*spl)->parent = lspl;
		}
		for (spl = rspl->pointers.begin(); spl!=rspl->pointers.end(); ++spl) {
			(*spl)->parent = rspl;
		}
	}
	if (node == root) {
		b_node<T>* newroot = new b_node<T>;
		node->parent = newroot;
		root = newroot;
		root->parent = NULL;
	}
	lspl->parent = node->parent;
	rspl->parent = node->parent;
	T key = *midkey;	
	delete node;
	insert_to_node(key, lspl->parent, lspl, rspl);
}

template <typename T, int _MIN_KEY>
bool b_tree<T,_MIN_KEY>::remove(T key) {
	b_node<T>* nod = find_key(key);
	std::list<T>::iterator it = std::find(nod->keys.begin(), nod->keys.end(), key);
	if (it == nod->keys.end()) {
		return false;
	} else {
		delete_from_node(key, nod);
		return true;
	}
}

template <typename T, int _MIN_KEY>
void b_tree<T,_MIN_KEY>::delete_from_node(T key, b_node<T>* node) {
	if (node->pointers.empty()) { //leaf
		node->keys.remove(key);
		if ((node->keys.size()>=min_key) || (node == root)) { //не менее n+1 элементов
			return;
		} else {
			joining(node);
		}
	} else { //inner node
		std::list<T>::iterator it = std::find(node->keys.begin(), 
											node->keys.end(), 
											key);
//		std::list<b_node<T> *>::iterator it1 = node->parent->pointers.begin();
//		std::list<T>::iterator it2 = node->parent->keys.begin();;
		std::list<b_node<T> *>::iterator it1 = node->pointers.begin();
		std::list<T>::iterator it2 = node->keys.begin();;
		while (it != it2) {
			++it2; 
			++it1;
		}
		++it1;
		b_node<T> *lfn = *it1;
		while (!lfn->pointers.empty()) {
			lfn = *(lfn->pointers.begin());
		}
		*it = *(lfn->keys.begin());
		delete_from_node(*it, lfn);
		return;
	}
}

template <typename T, int _MIN_KEY>
void b_tree<T,_MIN_KEY>::get_neighbours (b_node<T>* node, b_node<T>* parent, b_node<T>** left, b_node<T>** right) {
	std::list<b_node<T> *>::iterator it = std::find(parent->pointers.begin(), parent->pointers.end(), node);
	if (it == parent->pointers.begin()) {
		*left = NULL;
	} else {
		--it;
		*left = *it;
		++it;
	}
	++it;
	if (it == parent->pointers.end()) {
		*right = NULL;
	} else {
		*right = *it;
	}
}

template <typename T, int _MIN_KEY>
void b_tree<T,_MIN_KEY>::ensure_tree_conformance (b_node<T>* node) {
	if (node->keys.size() >= min_key) return;
	if ((node == root) && (node->keys.size() == 0)) {//
        root = *(node->pointers.begin());
		root->parent = NULL;
		node->pointers.clear();
		delete node;
		return;
	}    
	if (node == root) return;
	joining (node);
}

template <typename T, int _MIN_KEY>
void b_tree<T,_MIN_KEY>::joining (b_node<T>* node) {
	b_node<T> *leftn=NULL, *rightn=NULL;
	get_neighbours(node, node->parent, &leftn, &rightn);
	std::list<T>::iterator it = node->parent->keys.begin();
	std::list<b_node<T> *>::iterator it1 = node->parent->pointers.begin();
	std::list<b_node<T> *>::iterator it2 = std::find(node->parent->pointers.begin(), 
													node->parent->pointers.end(), 
													node);
	while (it1 != it2) {
		++it1; ++it;
	}
	if ((leftn) && (leftn->keys.size()>min_key)) {
		--it;
		node->keys.push_front(*it);
		std::list<T>::iterator it3 = leftn->keys.end(); --it3;
		*it = *it3;
		leftn->keys.pop_back();
		if (!(leftn->pointers.empty())) {
			std::list<b_node<T> *>::iterator it4 = leftn->pointers.end(); --it4;
			node->pointers.push_front(*it4);
			leftn->pointers.pop_back();
		}		
	} else if ((rightn) && (rightn->keys.size()>min_key)) {
		node->keys.push_back(*it);
		*it = *(rightn->keys.begin());
		rightn->keys.pop_front();
		if (!(rightn->pointers.empty())) {
			node->pointers.push_back(*(rightn->pointers.begin()));
			rightn->pointers.pop_front();
		}
	} else {
		if (leftn) {
			--it; --it1;
			node->keys.push_front(*it);
			node->keys.splice(node->keys.begin(),leftn->keys);
			node->parent->keys.remove(*it);
			node->parent->pointers.remove(*it1);
			if (!(leftn->pointers.empty())) {
				std::list<b_node<T> *>::iterator spl;
				for (spl = leftn->pointers.begin(); spl!=leftn->pointers.end(); ++spl) {
					(*spl)->parent = node;
				}
				node->pointers.splice(node->pointers.begin(),leftn->pointers);
			}
			delete leftn;
		} else {
			++it1;
			node->keys.push_back(*it);
			node->keys.splice(node->keys.end(),rightn->keys);
			node->parent->keys.remove(*it);
			node->parent->pointers.remove(*it1);
			if (!(rightn->pointers.empty())) {
				std::list<b_node<T> *>::iterator spl;
				for (spl = rightn->pointers.begin(); spl!=rightn->pointers.end(); ++spl) {
					(*spl)->parent = node;
				}
				node->pointers.splice(node->pointers.end(),rightn->pointers);
			}
			delete rightn;
		}
		ensure_tree_conformance(node->parent);
		return;
	}

}

}

#endif // BTREE_H