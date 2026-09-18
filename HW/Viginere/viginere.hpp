#pragma once

#include <iostream>
#include <random>
#include <string>
#include <ctime>
#include <fstream>

int gen_key();
int get_index(char c);
std::string vigenere_generate_key(std::string alphabet, int key_length);
std::string vigenere_encode(std::string key, std::string plain_text);
std::string vigenere_decode(std::string key, std::string cipher_text);
std::string viginere_auto_decode(std::string cipher_text);
