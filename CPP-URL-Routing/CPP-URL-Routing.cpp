// CPP-URL-Routing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"

#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <regex>
#include <list>

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
enum Operation
{
	GET,
	POST,
	PUT,
	DELETE
};
static const std::string operationToString[] = { "GET", "POST", "PUT", "DELETE" };
struct Node
{
	bool isParameter = false;
	std::string name = "";
	std::string parameter = "";
	std::string value = "";
	std::map<std::string, Node&> children{};
    std::map<Operation, Node&> operations{};
};

class RoutersTree
{
	Node root{};
	std::list<Node*> allCreatedNodes{};

public:
	RoutersTree() = default;

	void add(Operation operation, const std::string& path)
	{
		auto* currentNode = &root;
		std::vector<std::string> keys{};
		split(path, keys, '/');
		std::string value{};
		for (const auto& key : keys)
		{
			value += key + '/';
			if (currentNode->children.find(key) != currentNode->children.end())
			{
				currentNode = &currentNode->children.at(key);
			}
			else
			{
				auto newNode = new Node{false, key, "", value};
				std::string mapKey = key;
				allCreatedNodes.emplace_back(newNode);
				if (std::regex_match(key, std::regex(":\\w+")))
				{
					auto param = key.substr(1, key.length());
					newNode->isParameter = true;
					newNode->parameter = param;
					mapKey = ":";
				}
				currentNode->children.emplace(mapKey, *newNode);
				currentNode = newNode;
			}
		}
        auto operationNode = new Node{false, operationToString[operation], "", operationToString[operation] + " " +currentNode->value};
		operationNode->isParameter = currentNode->isParameter;
		operationNode->parameter = currentNode->parameter;
		currentNode->operations.emplace(operation, *operationNode);
	}

	Node& match(const std::string& path)
	{
		auto* currentNode = &root;
		std::vector<std::string> keys{};
		split(path, keys, '/');
		for (const auto& key : keys)
		{
			if (currentNode->children.find(key) != currentNode->children.end())
			{
				currentNode = &currentNode->children.at(key);
			}
			else if (currentNode->children.find(":") != currentNode->children.end())
			{
			    currentNode = &currentNode->children.at(":");
			}
			else
            {
                //return Page404(path);

			}
		}
		return *currentNode;
	}
};

int main()
{
	////tree node addition and matching test
	const std::string test = "/users/add";
	const std::string test1 = "/users/:id";
	RoutersTree tree;
	tree.add(GET, test1);
	tree.add(POST, test);
	auto& node = tree.match("/users/1234");

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
    std::cout << node.operations.at(Operation::GET).value << std::endl;
    std::cout << node.value << std::endl;
//    std::cout << node.operations.at(Operation::GET).parameter << std::endl;

	////map stuff
	/*std::map<std::string, int> m;
	m.emplace("1",1);
	auto a = m.at("1");
	auto b = m.find("1");*/


	return 0;
}
