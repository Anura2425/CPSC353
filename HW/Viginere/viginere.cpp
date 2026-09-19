#include "viginere.hpp"

const double ENGLISH_FREQS[27] = {
    0.1800, // ' ' <- thats a space btw
    0.0817, 0.0149, 0.0278, 0.0425, 0.1270, 0.0223, 0.0202, // a-g
    0.0609, 0.0697, 0.0015, 0.0077, 0.0403, 0.0241, 0.0675, // h-n
    0.0751, 0.0193, 0.0009, 0.0599, 0.0633, 0.0906, 0.0276, // o-u
    0.0098, 0.0236, 0.0015, 0.0197, 0.0007                  // v-z
};

// global dict for english words
std::unordered_set<std::string> dictionary;
bool dictionary_loaded = false;

void load_dictionary() {
    if (dictionary_loaded) return;

    // attempt to load from system file wordlist (if on linux this works but might not on other os not fully sure if they have this aswell)
    std::ifstream dict_file("/usr/share/dict/words");
    if (dict_file.is_open()) {
        std::string word;
        while (dict_file >> word) {
            // smash to lowercase
            std::transform(word.begin(), word.end(), word.begin(), [](unsigned char c){ return std::tolower(c); });
            dictionary.insert(word);
        }
        dict_file.close();
    } else {
        // alternatively this is just common words i found a list of, if the system file route didnt work
        std::vector<std::string> common_words = {
            "the", "be", "to", "of", "and", "a", "in", "that", "have", "i",
            "it", "for", "not", "on", "with", "he", "as", "you", "do", "at",
            "this", "but", "his", "by", "from", "they", "we", "say", "her",
            "she", "or", "an", "will", "my", "one", "all", "would", "there",
            "their", "what", "so", "up", "out", "if", "about", "who", "get",
            "which", "go", "me", "when", "make", "can", "like", "time", "no",
            "just", "him", "know", "take", "people", "into", "year", "your",
            "good", "some", "could", "them", "see", "other", "than", "then",
            "now", "look", "only", "come", "its", "over", "think", "also",
            "back", "after", "use", "two", "how", "our", "work", "first",
            "well", "way", "even", "new", "want", "because", "any", "these",
            "give", "day", "most", "us", "is", "test", "name", "gavin", "cipher"
        };
        for (const auto& w : common_words) {
            dictionary.insert(w);
        }
    }
    dictionary_loaded = true;
}

int get_index(char c) {
    if (c == ' ') return 0;
    c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    if (c >= 'a' && c <= 'z') return (c - 'a') + 1;
    return -1;
}

// letter frequency scoring, ended up opting for making score_text after anyways (much more reliable to use words then just letters for the most part)
int score(char c){
    int idx = get_index(c);
    if (idx != -1) {
        return static_cast<int>(ENGLISH_FREQS[idx] * 1000);
    }
    return 0;
}

// full word/text scoring (mainly implemented this because I was able to decode longer cipher texts but was failing to auto decode smaller ones, this seems to help give more value to words so smaller texts work too)
int score_text(const std::string& text) {
    load_dictionary();

    std::stringstream ss(text);
    std::string word;
    int valid_word_count = 0;
    int total_words = 0;

    while (ss >> word) {
        // strip non-alphabet chars
        std::string cleaned_word = "";
        for (char c : word) {
            if (std::isalpha(static_cast<unsigned char>(c))) {
                cleaned_word += static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
            }
        }

        if (!cleaned_word.empty()) {
            total_words++;
            if (dictionary.count(cleaned_word)) {
                valid_word_count++;
            }
        }
    }

    return (total_words == 0) ? 0 : (valid_word_count * 100 / total_words); 
}

std::string vigenere_generate_key(std::string alphabet, int key_length){
    // generates random key based on given alphabet and key length
    std::string key = "";
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> dist(0, alphabet.length() - 1);

    for (int i = 0; i < key_length; ++i) {
        key += alphabet[dist(gen)];
    }
    return key;
}

std::string vigenere_encode(std::string key, std::string plain_text, std::string alphabet){
    std::string cipher_text = "";
    int alpha_len = static_cast<int>(alphabet.length());
    int key_len = static_cast<int>(key.length());

    for (size_t i = 0; i < plain_text.length(); ++i) {
        int plaintext_idx = get_index(plain_text[i]);
        if (plaintext_idx == -1) {
            cipher_text += plain_text[i];
            continue;
        }

        int key_idx = get_index(key[i % key_len]);
        if (key_idx == -1) key_idx = 0;

        int ciphertext_idx = (plaintext_idx + key_idx) % alpha_len;
        cipher_text += alphabet[ciphertext_idx];
    }
    return cipher_text;
}

std::string vigenere_decode(std::string key, std::string cipher_text, std::string alphabet){
    std::string plain_text = "";
    int alpha_len = static_cast<int>(alphabet.length());
    int key_len = static_cast<int>(key.length());

    for (size_t i = 0; i < cipher_text.length(); ++i) {
        int c_idx = get_index(cipher_text[i]);
        if (c_idx == -1) {
            plain_text += cipher_text[i];
            continue;
        }

        int k_idx = get_index(key[i % key_len]);
        if (k_idx == -1) k_idx = 0;

        int p_idx = (c_idx - k_idx + alpha_len) % alpha_len;
        plain_text += alphabet[p_idx];
    }
    return plain_text;
}

std::string viginere_auto_decode(std::string cipher_text, std::string alphabet){
    int N = static_cast<int>(alphabet.length());
    int max_key_len = 20;

    std::string best_decoded_text = "";
    std::string best_overall_key = "";
    int max_dict_score = -1;

    // search across possible key lengths
    for (int k = 1; k <= max_key_len; ++k) {
        std::string possible_key = "";

        // recover key characters for length 'k' using letter frequencies
        for (int i = 0; i < k; ++i) {
            char best_char = alphabet[0];
            double max_freq_score = -1.0;

            for (char k_possible : alphabet) {
                int k_idx = get_index(k_possible);
                double current_score = 0.0;

                for (size_t j = i; j < cipher_text.length(); j += k) {
                    int c_idx = get_index(cipher_text[j]);
                    if (c_idx != -1) {
                        int p_idx = (c_idx - k_idx + N) % N;
                        current_score += ENGLISH_FREQS[p_idx];
                    }
                }

                if (current_score > max_freq_score) {
                    max_freq_score = current_score;
                    best_char = k_possible;
                }
            }
            possible_key += best_char;
        }

        // test decoded output against english dict
        std::string decoded_possible = vigenere_decode(possible_key, cipher_text, alphabet);
        int dict_score = score_text(decoded_possible);

        if (dict_score > max_dict_score) {
            max_dict_score = dict_score;
            best_overall_key = possible_key;
            best_decoded_text = decoded_possible;
        }

        // early exit if a text with > 70% dictionary word matches is found cuz thats like pretty much gaurenteed to be it (would be insane if it accidentally happened)
        if (dict_score > 70) {
            break;
        }
    }

    std::cout << "  Found Key: \"" << best_overall_key << "\"\n";
    std::cout << "  Dictionary Match Score: " << max_dict_score << "%\n";

    return best_decoded_text;
}