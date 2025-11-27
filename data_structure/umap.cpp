#include <unordered_map>
#include <iostream>

void printUmap(const std::unordered_map<int, std::string>& m) {
    std::cout << "{\n";
    for (const auto& p : m) {
        const auto& key = p.first;
        const auto& val = p.second;
        std::cout << "\t" << key << ": " << val << std::endl;
    }
    std::cout << "}\n";
}

int main() {

    std::unordered_map<int, std::string> map;
    map[1] = "hello";
    map[2] = "world";
    map[3] = "!";

    printUmap(map);

    return 0;
}
