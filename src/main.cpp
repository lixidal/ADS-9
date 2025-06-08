// Copyright 2022 NNTU-CS
#include <iostream>
#include <chrono>
#include <random>
#include <vector>
#include "tree.h"

int main() {
    std::vector<char> test_input = {'a', 'b', 'c', 'd'};
    PMTree tree(test_input);

    auto start_time = std::chrono::high_resolution_clock::now();
    auto all_permutations = tree.extract_all_permutations();
    auto stop_time = std::chrono::high_resolution_clock::now();
    double elapsed_time = std::chrono::duration<double, std::milli>(stop_time - start_time).count();
    std::cout << "Все перестановки извлечены за: " << elapsed_time << " миллисекунд\n";

    std::random_device device;
    std::mt19937 engine(device());
    std::uniform_int_distribution<int> distribution(1, static_cast<int>(all_permutations.size()));
    int random_position = distribution(engine);

    start_time = std::chrono::high_resolution_clock::now();
    auto specific_permutation = tree.obtain_permutation_at(random_position);
    stop_time = std::chrono::high_resolution_clock::now();
    elapsed_time = std::chrono::duration<double, std::milli>(stop_time - start_time).count();
    std::cout << "Перестановка по указанному индексу извлечена за: " << elapsed_time << " миллисекунд\n";

    return 0;
}
