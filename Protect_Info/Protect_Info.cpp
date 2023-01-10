/* Вариант № 8.

//Реализовать возможность кодирования открытого текста и декодирования шифрограммы по правилам азбуки Морзе.Предусмотреть поддержку русского и английского алфавитов.

// Работу выполнил: студент группы ВМЗ-20

// Кузьменко А.А.

*/

#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <Windows.h>
#include <fcntl.h>
#include <io.h>
#include <stdio.h>
std::string CharToMorse(char c) {
	static const std::map<char, std::string> morseCode = {
	{'A',".-"},      {'А',".-"},          {'Щ',"--.-"},
	{'B',"-..."},    {'Б',"-..."},        {'Ъ',".--.-."},
	{'C',".-.-"},    {'В',".--"},         {'Ы',"-.--"},
	{'D',"-.."},     {'Г',"--."},         {'Ь',"-..-"},
	{'E',"."},       {'Д',"-.."},         {'Э',"...-..."},
	{'F',"..-."},    {'Е',"."},           {'Ю',"..--"},
	{'G',"--."},     {'Ё',"."},           {'Я',".-.-"},
	{'H',"...."},    {'Ж',"...-"},        {'0',"-----"},
	{'I',".."},      {'З',"--.."},        {'1',".----"},
	{'J',".---"},    {'И',".."},          {'2',"..---"},
	{'K',"-.-"},     {'Й',".---"},        {'3',"...--"},
	{'L',".-.."},    {'К',"-.-"},         {'4',"....-"},
	{'M',"--"},      {'Л',".-.."},        {'5',"....."},
	{'N',"-."},      {'М',"--"},          {'6',"-...."},
	{'O',"---"},     {'Н',"-."},          {'7',"--..."},
	{'P',".--."},    {'О',"---"},         {'8',"---.."},
	{'Q',"--.-"},    {'П',".--."},        {'9',"----."},
	{'R',".-."},     {'Р',".-."},
	{'S',"..."},     {'С',"..."},
	{'T',"-"},       {'Т',"-"},
	{'U',"..-"},     {'У',"..-"},
	{'V',"...-"},    {'Ф',"..-."},
	{'W',".--"},     {'Х',"...."},
	{'X',"-..-"},    {'Ц',"-.-."},
	{'Y',"-.--"},    {'Ч',"---."},
	{'Z',"--.."},    {'Ш',"----"},
	};

	auto morseString = morseCode.find(toupper(c));
	if (morseString != morseCode.end())
	{
		return morseString->second;
	}
	else
	{
		return "";
	}
}

const char* MorseToChar_Eng(std::string str) 
{
	static const std::map<std::string, const char*> morseCodeToEng = {
	{".-", "A"},
	{"-...", "B"},
	{".-.-", "C"},
	{"-..", "D"},
	{".", "E"},
	{"..-.", "F"},
	{"--.", "G"},
	{"....", "H"},		{"-----", "0"},
	{"..", "I"},		{".----", "1"},
	{".---", "J"},		{"..---", "2"},
	{"-.-", "K"},		{"...--", "3"},
	{".-..", "L"},		{"....-", "4"},
	{"--", "M"},		{".....", "5"},
	{"-.", "N"},		{"-....", "6"},
	{"---", "O"},		{"--...", "7"},
	{".--.", "P"},		{"---..", "8"},
	{"--.-", "Q"},		{"----.", "9"},
	{".-.", "R"},
	{"...", "S"},
	{"-", "T"},
	{"..-", "U"},
	{"...-", "V"},
	{".--", "W"},
	{"-..-", "X"},
	{"-.--", "Y"},
	{"--..", "Z"},
	};
	auto morseStringToEng = morseCodeToEng.find(str);
	if (morseStringToEng != morseCodeToEng.end())
	{
		return morseStringToEng->second;
	}
	else
	{
		return "";
	}
}
const char* MorseToChar_Rus(std::string str)
{
	static const std::map<std::string, const char*> morseCodeToRus = {
	{".-", "А"},          {".--.-.", "Ъ"},
	{"-...", "Б"},        {"-.--", "Ы"},
	{".--", "В"},         {"-..-", "Ь"},
	{"--.", "Г"},         {"...-...", "Э"},
	{"-..", "Д"},         {"..--", "Ю"},
	{".", "Е"},           {".-.-", "Я"},
	{"...-", "Ж"},		  {"-----", "0"},
	{"--..", "З"},		  {".----", "1"},
	{"..", "И"},          {"..---", "2"},
	{".---", "Й"},		  {"...--", "3"},			
	{"-.-", "К"},		  {"....-", "4"},
	{".-..", "Л"},		  {".....", "5"},
	{"--", "М"},		  {"-....", "6"},
	{"-.", "Н"},		  {"--...", "7"},
	{"---", "О"},		  {"---..", "8"},
	{".--.", "П"},		  {"----.", "9"},
	{".-.", "Р"},		  
	{"...", "С"},
	{"-", "Т"},
	{"..-", "У"},
	{"..-.", "Ф"},
	{"....", "Х"},
	{"-.-.", "Ц"},
	{"---.", "Ч"},
	{"----", "Ш"},
	{"--.-", "Щ"},
	};
	auto morseStringToRus = morseCodeToRus.find(str);
	if (morseStringToRus != morseCodeToRus.end())
	{
		return morseStringToRus->second;
	}
	else
	{
		return "";
	}
}

std::vector<std::string> split(std::string s, std::string delimiter)
{
	size_t pos_start = 0, pos_end, delim_len = delimiter.length();
	std::string token;
	std::vector<std::string> res;
	while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) 
	{
		token = s.substr(pos_start, pos_end - pos_start);
		pos_start = pos_end + delim_len;
		res.push_back(token);
	}
	res.push_back(s.substr(pos_start));
	return res;

}

int main()

{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	std::string delimiter = "   ";
	std::string delimiter_between_words = " ";
	std::stringstream ss;
	std::string sentence;
	std::cout << "Введите текст, для шифровки, используя азбуку Морзе: ";
	std::getline(std::cin, sentence);
	ss << std::noskipws << sentence;
	std::cout << "Morse code: " << std::endl;
	char c;
	while (ss >> c)
	{
		if (c == ' ')
		{
			std::cout << " ";
		}
		else
		{
			std::cout << CharToMorse(c) << " ";
		}
	}

	std::cout << "\nВведите шифр для английского языка: ";
	std::getline(std::cin, sentence);
	std::vector<std::string> v = split(sentence, delimiter);
	for (auto i : v)
	{
		std::string str(i.begin(), i.end());
		std::vector<std::string> w = split(str, delimiter_between_words);
		for (auto j : w)
		{
			std::cout << MorseToChar_Eng(j);
		}
		std::cout << " ";
	}
	std::cout << "\nEnd message" << std::endl;
	std::cout << "\nВведите шифр для русского языка: ";
	std::getline(std::cin, sentence);
	std::vector<std::string> r = split(sentence, delimiter);
	for (auto x : r)
	{
		std::string str(x.begin(), x.end());
		std::vector<std::string> b = split(str, delimiter_between_words);
		for (auto y : b)
		{
			std::cout << MorseToChar_Rus(y);
		}
		std::cout << " ";
	}
	std::cout << "\nEnd message" << std::endl;
	return 0;

}
