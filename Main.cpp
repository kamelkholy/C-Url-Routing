#include <string>
#include <map>
#include <iostream>
#include <vector>

template <class Container>
void split(const std::string& str, Container& cont, char delim = ' ')
{
    std::size_t current, previous = 0;
    current = str.find(delim);
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
    std::map<std::string, Node> children{};
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
    RoutersTree(){
        root = Node();
    }
    Node root;
    void add(Operation operation, std::string path)
    {
    }
    std::string match(std::string path){

    }
};

int main(){
    auto test = "/users/add";
    std::vector<std::string> words;
    split(test, words, '/');
    std::cout<<words[2]<<std::endl;
    return 0;
}
