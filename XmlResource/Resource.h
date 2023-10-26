#pragma once
#include "Tree.h"

class Resource
{
private:
    std::unique_ptr<Tree> tree;

	Resource() = default;
	~Resource() = default;
public:
	static Resource& create();
	void load(const std::string& path);
	void save(const std::string& path);	

	Resource(const Resource&) = delete;
	Resource(Resource&&) = delete;
	Resource& operator = (const Resource&) = delete;
	Resource& operator = (Resource&&) = delete;

	class Iterator : public std::iterator<std::forward_iterator_tag, Node>
	{
		friend class Tree;
	private:
		pointer ptr;
	public:
		using iterator_category = std::forward_iterator_tag;
		using value_type = std::ptrdiff_t;
		using difference_type = Node;
		using pointer = Node*;
		using reference = Node&;

		Iterator(pointer ptr_) : ptr(ptr_) {};
		reference operator*();
		pointer operator ->();
		Iterator operator++ ();
		Iterator& operator++(int i);
		friend bool operator== (const Iterator& a, const Iterator& b) { return a.tree == b.m_ptr; };
		friend bool operator!= (const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; };
	};
};