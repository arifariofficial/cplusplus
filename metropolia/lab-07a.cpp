/*
Function objects

Modify and improve the random number generator from the lecture slides (lecture7, page 27) to create a lotto
number generator:
Constructor takes two parameters that determine the range of numbers that the generator produces.
Write a program that generates numbers for three different games:
1. Lotto: 7 numbers 1 – 40
2. Viking lotto: 6 numbers 1 – 48
3. Eurojackpot: 5 numbers 1 – 50

Use either generate or generate_n algorithm to generate the three sets of numbers.
Print each set of numbers using a suitable algorithm and output stream iterator.
Then find numbers that appear in all three sets and print them. Use set_intersection algorithm to find the
numbers that appear in all three sets:
• Find matching numbers from two sets and print them using for_each algorithm
• Find matching number from the third set and print them using for_each algorithm
To print the numbers with index numbering you need to use a function object (can also be implemented with a
lambda) to remember the index between calls.

Example:
Lotto: 1 12 24 36 11 15 32
Viking lotto: 24 7 11 18 35 1
Matching numbers:
#1: 1
#2: 11
#3: 24
Eurojackport: 47 1 40 24 4
Matching numbers in three sets:
#1: 1
#2: 24
After finding the matching numbers ask user if he/she wants to continue. If the answer is yes then generate
another three sets of lotto numbers.
 */

#include <algorithm>
#include <cstdlib>
#include <ostream>
#include <vector>
#include <iostream>
#include <set>
#include <iomanip>

// Function object
class RandGen_2 {
public:
    RandGen_2(const int min, const int max): min_(min), max_(max) {
        srand(static_cast<unsigned int>(time(nullptr)));
    }
    int operator()() {
        int number;
        do {
            number = rand() % (max_ - min_ + 1) + min_;
        } while (numbers_.contains(number)); // Ensure uniqueness
        numbers_.insert(number);
        return number;
    }
private:
    int min_, max_;
    std::set<int> numbers_; //Ensure uniqueness of numbers
};

std::vector<int> generate_lotto_numbers(int count, int min, int max);
std::vector<int> get_matching_numbers(std::vector<int> *numbers1, std::vector<int> *numbers2,
                                      std::vector<int> *numbers3 = nullptr);
void print(const std::vector<int> &numbers, const std::string &title);
void print_with_index(const std::vector<int> &numbers, const std::string &title);

// Main lotto program
int main() {
    do {
        // Generate numbers for Lotto (7 numbers from 1 to 40)
        std::vector<int> lotto_numbers = generate_lotto_numbers(7, 1, 40);
        print(lotto_numbers, "Lotto: ");

        // Generate numbers for Viking Lotto (6 numbers from 1 to 48)
        std::vector<int> viking_lotto_numbers = generate_lotto_numbers(6, 1, 48);
        print(viking_lotto_numbers, "Viking Lotto: ");

        // Print matching numbers in Lotto and Viking Lotto
        std::vector<int> matching_2_sets = get_matching_numbers(&lotto_numbers, &viking_lotto_numbers);
        print_with_index(matching_2_sets, "Matching numbers: ");

        // Generate numbers for Eurojackpot (5 numbers from 1 to 50)
        std::vector<int> eurojackpot_numbers = generate_lotto_numbers(5, 1, 50);
        print(eurojackpot_numbers, "Eurojackpot: ");

        // Print matching numbers in Lotto, Viking Lotto, and Eurojackpot
        std::vector<int> matching_3_sets = get_matching_numbers(&lotto_numbers, &viking_lotto_numbers,
                                                                &eurojackpot_numbers);
        print_with_index(matching_3_sets, "Matching numbers in three sets: ");

        // Ask the user if they want to continue
        char response;
        std::cout << "Do you want to generate another set of lotto numbers? (y/n): ";
        std::cin >> response;
        if (response != 'y') break;
    } while (true);

    return 0;
}

// Function to generate lotto numbers
std::vector<int> generate_lotto_numbers(const int count, const int min, const int max) {
    std::vector<int> numbers(count);
    const RandGen_2 rand_gen(min, max); // Create the random number generator
    std::ranges::generate(numbers, rand_gen); // Generate numbers using the random number generator

    return numbers;
}

// Function to print vector with title
void print(const std::vector<int> &numbers, const std::string &title) {
    std::cout << title;
    for (const auto &number: numbers) {
        std::cout << number << " ";
    }
    std::cout << std::endl;
}

// Function to print numbers with index
void print_with_index(const std::vector<int> &numbers, const std::string &title) {
    std::cout << title << std::endl;

    // Use std::for_each with a lambda function to print numbers with index
    int index = 1;
    std::for_each(numbers.begin(), numbers.end(), [&index](const int &number) {
        std::cout << "#" << std::setw(2) << index << ": " << number << std::endl;
        ++index;
    });
}
// Function to get matching numbers
std::vector<int> get_matching_numbers(std::vector<int> *numbers1, std::vector<int> *numbers2,
                                      std::vector<int> *numbers3) {
    // Dereference the pointers and sort the vectors to ensure correct behavior of set_intersection
    std::ranges::sort(*numbers1);
    std::ranges::sort(*numbers2);

    // If numbers3 is not nullptr, dereference and sort it
    if (numbers3) {
        std::ranges::sort(*numbers3);
    }

    // Find the intersection of the first two sets
    std::vector<int> matching_numbers;
    std::ranges::set_intersection(*numbers1, *numbers2,
                                  std::back_inserter(matching_numbers)); // Find matching numbers between 2 sets

    // If numbers3 is not nullptr, find the intersection with the third set
    if (numbers3) {
        std::vector<int> final_intersection;
        std::ranges::set_intersection(matching_numbers, *numbers3,
                                      std::back_inserter(final_intersection)); // Find intersection with the third set
        return final_intersection;
    }

    return matching_numbers;
}