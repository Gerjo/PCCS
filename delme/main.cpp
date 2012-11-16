#include <iostream>
#include <string>

class Blaat {
public:
    std::string foo = "awesome";
};


int main(int argc, char** argv) {
    Blaat blaat;
    std::cout << blaat.foo << std::endl;
}

