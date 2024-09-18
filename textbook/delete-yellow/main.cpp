#include <iostream>
#include <stack>
#include <string>

void removeYellowCandies(std::stack<std::string>& originalStack) {
    std::stack<std::string> tempStack;

    // Step 1: Process all candies from the original stack
    while (!originalStack.empty()) {
        std::string candy = originalStack.top();
        originalStack.pop();

        // Step 2: If the candy is not yellow, push it onto the temp stack
        if (candy != "yellow") {
            tempStack.push(candy);
        }
    }

    // Step 3: Move non-yellow candies back to the original stack
    while (!tempStack.empty()) {
        originalStack.push(tempStack.top());
        tempStack.pop();
    }
}

int main() {
    // Initialize a stack of Pez candies
    std::stack<std::string> pezContainer;

    // Push candies onto the stack (the order simulates the Pez container's random order)
    pezContainer.push("red");
    pezContainer.push("yellow");
    pezContainer.push("green");
    pezContainer.push("yellow");
    pezContainer.push("blue");
    pezContainer.push("yellow");

    std::cout << "Original Pez container contains (from top to bottom): " << std::endl;
    std::stack<std::string> displayStack = pezContainer; // Copy to display the content
    while (!displayStack.empty()) {
        std::cout << displayStack.top() << std::endl;
        displayStack.pop();
    }

    // Remove yellow candies
    removeYellowCandies(pezContainer);

    // Display the new Pez container contents
    std::cout << "\nPez container after removing yellow candies: " << std::endl;
    while (!pezContainer.empty()) {
        std::cout << pezContainer.top() << std::endl;
        pezContainer.pop();
    }

    std::cout << "\nPress Enter to exit...";
    std::cin.get();

    return 0;
}
