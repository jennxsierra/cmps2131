#include <iostream>
#include <stack>
#include <cctype>
#include <string>

bool isPalindrome(std::string input);

int main() {
    std::string testWord;
    std::cout << "Enter a string (end with '.'): ";
    std::getline(std::cin, testWord, '.');

    if (isPalindrome(testWord)) {
        std::cout << "The string is a palindrome." << std::endl;
    } else {
        std::cout << "The string is not a palindrome." << std::endl;
    }

    return 0;
}

bool isPalindrome(std::string input) {
    std::stack<char> stack;
    int length = input.length();
    int mid = length / 2;

    // Push the first half of the string to the stack (ignoring spaces and punctuation)
    for (int i = 0; i < mid; ++i) {
        if (std::isalpha(input[i])) {  // Only consider alphabetic characters
            stack.push(std::toupper(input[i])); // Push the uppercase version for case insensitivity
        }
    }

    // Adjust if the length of the string is odd
    if (length % 2 != 0) {
        mid++;
    }

    // Compare the second half of the string with the stack
    for (int i = mid; i < length; ++i) {
        if (std::isalpha(input[i])) {
            char currentChar = std::toupper(input[i]);
            if (currentChar != stack.top()) {
                return false;
            }
            stack.pop();
        }
    }
    return true;
}