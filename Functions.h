#pragma once
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cstring>
#include "Identificator.h"
#include "MyForm.h"

using namespace System;

// Прототипы функций
int RandNum(int min, int max); // Генерация рандомного числа в заданном диапазоне
int Hash(int num1, int num2); // Хэш-функция
int GPSCh(int n); // Генератор псевдослучайных чисел

// Поиск по рехешированию с ГПСЧ
void Search_simple(char I[16], char IDS_simple[151][17], int R_Chisla[151], int Data[2]);

// Поиск по рехешированию методом цепочек
void Search_hard(char I[16], Identificator* Hash_table[151], int Data[2]);

// Cоздание массива идентификаторов
void CreateIDS(char IDS[120][17]);

// Размещение идент-ов в массиве через хэш-функцию с рехешированием с использованием псевдослучайных чисел
unsigned int PlaceIwithGPSCH(char IDS[120][17], char IDS_simple[151][17], int R_Chisla[151]);

// Размещение идент-ов в динамической памяти через хэш-функцию с рехешированием методом цепочек
unsigned int PlaceIwithChains(char IDS[120][17], Identificator* Hash_table[151]);

std::string& Convert_String_to_string(String^ s, std::string& os); // Конвертируем System::string ^ в std::string

String^ Convert_string_to_String(std::string& os, String^ s); // Конвертируем std::string в System::string ^

std::string& Convert_String_to_string(String^ s); // Конвертируем System::string ^ в std::string

String^ Convert_string_to_String(std::string& os); // Конвертируем std::string в System::string ^

System::String^ Convert_char_to_String(char* ch); // Конвертируем char* в System::String^

char* Convert_String_to_char(System::String^ string); // Конвертируем System::String^ в char*

std::string IntTostring(int a); // Конвертируем Int в std::string

float RoundDva(float a); // Округление float до 2х знаков после запятой

void ReadingFile(int& Count, int& NumsHard, int& NumsSimple); // Чтение данных из файла

void WritingFile(int Count, int NumsHard, int NumsSimple); // Запись данных в файл