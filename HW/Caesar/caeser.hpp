#pragma once

#include <iostream>
#include <random>
#include <string>
#include <ctime>
#include <fstream>

int gen_key();
int get_index(char c);
std::string enc(std::string plain_text, int key);
std::string enc_file(std::string file_name, int key);
std::string dec(std::string cipher_text, int key);
std::string dec_file(std::string file_name, int key);
std::string auto_dec(std::string cipher_text);
std::string auto_dec_file(std::string cipher_text);