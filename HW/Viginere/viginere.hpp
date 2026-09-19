#pragma once

#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <ctime>
#include <fstream>
#include <unordered_set>
#include <sstream>

int get_index(char c);
int score(char c);

std::string vigenere_generate_key(std::string alphabet, int key_length);
std::string vigenere_encode(std::string key, std::string plain_text, std::string alphabet);
std::string vigenere_decode(std::string key, std::string cipher_text, std::string alphabet);
std::string viginere_auto_decode(std::string cipher_text, std::string alphabet);
