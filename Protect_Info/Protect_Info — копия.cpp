/* Вариант № 8.
//Реализовать возможность кодирования открытого текста и декодирования шифрограммы по правилам азбуки Морзе.Предусмотреть поддержку русского и английского алфавитов.
// Работу выполнил: студент группы ВМЗ-20
//                   Кузьменко А.А.
*/
#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <Windows.h>
std::string CharToMorse(char c) {
    static const std::map<char, std::string> morseCode = {
      {'A',".-"},              {'А',".-"},         {'Щ',"--.-"},
      {'B',"-..."},            {'Б',"-..."},       {'Ъ',".--.-."},
      {'C',".-.-"},            {'В',".--"},        {'Ы',"-.--"},
      {'D',"-.."},             {'Г',"--."},        {'Ь',"-..-"},
      {'E',"."},               {'Д',"-.."},        {'Э',"...-..."},
      {'F',"..-."},            {'Е',"."},          {'Ю',"..--"},
      {'G',"--."},             {'Ё',"."},          {'Я',".-.-"},
      {'H',"...."},            {'Ж',"...-"},       {'0',"-----"},
      {'I',".."},              {'З',"--.."},       {'1',".----"},
      {'J',".---"},            {'И',".."},         {'2',"..---"},
      {'K',"-.-"},             {'Й',".---"},       {'3',"...--"},
      {'L',".-.."},            {'К',"-.-"},        {'4',"....-"},
      {'M',"--"},              {'Л',".-.."},       {'5',"....."},
      {'N',"-."},              {'М',"--"},         {'6',"-...."},
      {'O',"---"},             {'Н',"-."},         {'7',"--..."},
      {'P',".--."},            {'О',"---"},        {'8',"---.."},
      {'Q',"--.-"},            {'П',".--."},       {'9',"----."},
      {'R',".-."},             {'Р',".-."},        
      {'S',"..."},             {'С',"..."},
      {'T',"-"},               {'Т',"-"},
      {'U',"..-"},             {'У',"..-"},
      {'V',"...-"},            {'Ф',"..-."},
      {'W',".--"},             {'Х',"...."},
      {'X',"-..-"},            {'Ц',"-.-."},
      {'Y',"-.--"},            {'Ч',"---."},
      {'Z',"--.."},            {'Ш',"----"},
      
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
int main()
{
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    std::stringstream ss;
    std::string sentence;

    std::cout << "Enter a English word, number or punctuation: ";
    std::getline(std::cin, sentence);
    ss << std::noskipws << sentence;
    std::cout << "Morse code: " << std::endl;
    char c;
    while (ss >> c) {
        if (c == ' ')
        {
            std::cout << "   ";
        }
        else
        {
            std::cout << CharToMorse(c) << " ";
        }        
    }
    std::cout <<"\nEnd message"<< std::endl;

    return 0;
}



