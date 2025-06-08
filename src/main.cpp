// Copyright 2022 NNTU-CS
#include <iostream>
#include <chrono>
#include <random>
#include <vector>
#include "tree.h"

int main() {
    std::vector<char> chars = {'a', 'b', 'c', 'd'};
    PMTree tree(chars);

    auto start_time = std::chrono::high_resolution_clock::now();
    auto all_permutations = getAllPerms(tree);
    auto finish_time = std::chrono::high_resolution_clock::now();
    double elapsed_ms = std::chrono::duration<double, std::milli>(
        finish_time - start_time).count();
    std::cout << "Время генерации всех перестановок: " 
              << elapsed_ms << " мс.\n";

    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> distribution(
        1, static_cast<int>(all_permutations.size()));
    int selected_number = distribution(generator);

    start_time = std::chrono::high_resolution_clock::now();
    auto permutation_from_list = getPerm1(tree, selected_number);
    finish_time = std::chrono::high_resolution_clock::now();
    elapsed_ms = std::chrono::duration<double, std::milli>(
        finish_time - start_time).count();
    std::cout << "Получение перестановки через общий список заняла: " 
              << elapsed_ms << " мс.\n";

    start_time = std::chrono::high_resolution_clock::now();
    auto direct_access = getPerm2(tree, selected_number);
    finish_time = std::chrono::high_resolution_clock::now();
    elapsed_ms = std::chrono::duration<double, std::milli>(
        finish_time - start_time).count();
    std::cout << "Прямой доступ к перестановке занял: " 
              << elapsed_ms << " мс.\n";

    return 0;
}
