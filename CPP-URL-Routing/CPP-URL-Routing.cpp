// CPP-URL-Routing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"

#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <regex>
#include<list>

template <class Container>
void split(const std::string& str, Container& cont, const char delimiter = ' ')
{
	std::size_t previous = 0;
	auto current = str.find(delimiter);
	while (current != std::string::npos)
	{
		cont.emplace_back(str.substr(previous, current - previous));
		previous = current + 1;
		current = str.find(delimiter, previous);
	}
	cont.emplace_back(str.substr(previous, current - previous));
}

struct Node
{
	bool isParameter = false;
	std::string name = "";
	std::string parameter = "";
	std::string value = "";
	std::map<std::string, Node&> children{};
};

enum Operation
{
	GET,
	POST,
	PUT,
	DELETE
};

class RoutersTree
{
	Node root{};
	std::list<Node*> allCreatedNodes{};

public:
	RoutersTree() = default;

	void add(Operation operation, const std::string& path)
	{
		auto* current_node = &root;
		std::vector<std::string> keys{};
		split(path, keys, '/');
		for (const auto& key : keys)
		{
			if (current_node->children.find(key) != current_node->children.end())
			{
				current_node = &current_node->children.at(key);
			}
			else
			{
				auto newNode = new Node{false, key, "", path};
				allCreatedNodes.emplace_back(newNode);
				std::cout << key << std::endl;
				if (std::regex_match(key, std::regex(":\\w+")))
				{
					auto param = key.substr(1, key.length());
					std::cout << param << "\n";
					newNode->isParameter = true;
					newNode->parameter = param;
				}
				current_node->children.emplace(key, *newNode);
				current_node = newNode;
			}
		}
	}

	Node& match(const std::string& path)
	{
		auto* current_node = &root;
		std::vector<std::string> keys{};
		split(path, keys, '/');
		for (const auto& key : keys)
		{
			if (current_node->children.find(key) != current_node->children.end())
			{
				current_node = &current_node->children.at(key);
			}
			else
			{
				//Page404(path);
			}
		}
		return *current_node;
	}
};

int main()
{
	////tree node addition and matching test
	const std::string test = "/users/add";
	RoutersTree tree;
	tree.add(GET, test);
	auto& node = tree.match(test);

	////regex test
	std::string param = ":aasdf_sada";
	if (std::regex_match(param, std::regex(":\\w+")))
	{
		param = param.substr(1, param.length());
		std::cout << param << "\n";
	}

	////string split test
	//	std::vector<std::string> words;
	//	split(test, words, '/');
	//	std::cout << node.value << std::endl;

	////map stuff
	/*std::map<std::string, int> m;
	m.emplace("1",1);
	auto a = m.at("1");
	auto b = m.find("1");*/


	auto a = 3;
	auto& b = a;
	b=5;
	std::cout<<a;

	return 0;
}
