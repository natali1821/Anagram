#include <algorithm>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <string>
#include <map>

int main(int argc, char** argv) {
	if (argc != 3) {
		std::cout << "Invalid arguments" << std::endl;
	}

	// работа со словарем
	std::ifstream file(argv[1]);
	std::vector<std::pair<std::string, int>> dict;
	std::string str;
	std::string w;
	int value;
	if (file.is_open()) {
		while (std::getline(file, str)) {
			if (str[str.size() - 1] == '\r') {
				str.erase(str.size() - 1);
			}
			if (!str.empty()) {
				w = str.substr(0, str.find(','));
				value = std::stoi(str.substr(str.find(' ') + 1));
				dict.push_back(std::pair<std::string, int>(w, value));
			}
		}
	}
	else {
		throw std::invalid_argument("Failed to load file");
	}
	
	// работа с исходным файлом
	std::ifstream input(argv[2]);
	if (!input.is_open()) {
		throw std::invalid_argument("Failed to load file");
	}
	std::vector<std::string> sentence;
	while (std::getline(input, str)) {
		sentence.clear();
		str.push_back(' ');
		std::cout << "The string - " << str << std::endl;
		if (str[str.size() - 1] == '\r') {
			str.erase(str.size() - 1);
		}
		if (str.empty()) {
			continue;
		}
		size_t pos = 0;
		std::string word; //слово
		std::string delimiter = " ";
		std::string original_word{}; // для сохранения слова с максимальным весом

		while ((pos = str.find(delimiter)) != std::string::npos) {  // разделение строки на слова
			word = str.substr(0, pos);
			str.erase(0, pos + delimiter.length());
			// расшифровка слова
			int max = -999999; // для сохранения максимального веса
			for (auto val : dict) {
				// если значение из вектора - перестановка слова
				if (std::is_permutation(word.begin(), word.end(), val.first.begin(), val.first.end())) {
					if (val.second > max) {
						max = val.second;
						original_word = val.first;
					}
				}
			}
			sentence.push_back(original_word);
		}

		// вывод всех возможных вариантов для строки
		std::sort(sentence.begin(), sentence.end());
		// крутим цикл, пока не закончатся перестановки
		do {
			for (auto word : sentence)
				std::cout << word << " ";
			std::cout << std::endl;
		} while ( // получаем следующую перестановку для предложения
			std::next_permutation(sentence.begin(), sentence.end())
		);
	}
	input.close();
	
}