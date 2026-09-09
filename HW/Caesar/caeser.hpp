#pragma once

#include <iostream>
#include <random>
#include <string>
#include <ctime>

int gen_key();
int get_index(char c);
std::string enc(std::string plain_text, int key);
std::string enc_file(std::string file_name);
std::string dec(std::string cipher_text, int key);
std::string dec_file(std::string file_name);
std::string auto_dec(std::string cipher_text);