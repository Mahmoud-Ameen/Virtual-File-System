
#include <iostream>

#include "UserInterface.h"
#include "ErrorHandling.h"

using namespace std;

int main() {

    ErrorHandling::initialize();
    UserInterface userInterface;

    userInterface.run();
}