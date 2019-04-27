// CPP-URL-Routing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"


#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <csignal>

template <class Container>
void split(const std::string& str, Container& cont, const char delim = ' ')
{
	std::size_t previous = 0;
	auto current = str.find(delim);
	while (current != std::string::npos) {
		cont.push_back(str.substr(previous, current - previous));
		previous = current + 1;
		current = str.find(delim, previous);
	}
	cont.push_back(str.substr(previous, current - previous));
}
struct Node
{
	bool isParameter = false;
	std::string name = "";
	std::string parameter = "";
	std::string value = "";
	std::map<std::string, Node&> children{};
};

enum Operation {
	GET,
	POST,
	PUT,
	DELETE
};
class RoutersTree
{
public:
	RoutersTree() = default;
	void add(Operation operation, std::string path) const
	{
	}
	Node& match(const std::string& path) {
		auto& current_node = root;
		std::vector<std::string&> keys{};
		split(path, keys, '/');
		for (auto& key : keys)
		{
			if (search(current_node, key))
			{
				current_node = current_node.children.at(key);
			}
			else
			{
				//Page404(path);
			}
		}
		return current_node;
	}

	static bool search(Node& node, const std::string& key)
	{
		for (const auto& child : node.children)
		{
			if (child.first == key)
				return true;
		}
		return false;
	}

private:
	Node root{};
};

int main() {
	const auto test = "/users/add";
	std::vector<std::string> words;
	split(test, words, '/');
	std::cout << words[2] << std::endl;
	return 0;
}
