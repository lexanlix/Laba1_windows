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

// ��������� �������
int RandNum(int min, int max); // ��������� ���������� ����� � �������� ���������
int Hash(int num1, int num2); // ���-�������
int GPSCh(int n); // ��������� ��������������� �����

// ����� �� ������������� � ����
void Search_simple(char I[16], char IDS_simple[151][17], int R_Chisla[151], int Data[2]);

// ����� �� ������������� ������� �������
void Search_hard(char I[16], Identificator* Hash_table[151], int Data[2]);

// C������� ������� ���������������
void CreateIDS(char IDS[120][17]);

// ���������� �����-�� � ������� ����� ���-������� � �������������� � �������������� ��������������� �����
unsigned int PlaceIwithGPSCH(char IDS[120][17], char IDS_simple[151][17], int R_Chisla[151]);

// ���������� �����-�� � ������������ ������ ����� ���-������� � �������������� ������� �������
unsigned int PlaceIwithChains(char IDS[120][17], Identificator* Hash_table[151]);

std::string& Convert_String_to_string(String^ s, std::string& os); // ������������ System::string ^ � std::string

String^ Convert_string_to_String(std::string& os, String^ s); // ������������ std::string � System::string ^

std::string& Convert_String_to_string(String^ s); // ������������ System::string ^ � std::string

String^ Convert_string_to_String(std::string& os); // ������������ std::string � System::string ^

System::String^ Convert_char_to_String(char* ch); // ������������ char* � System::String^

char* Convert_String_to_char(System::String^ string); // ������������ System::String^ � char*

std::string IntTostring(int a); // ������������ Int � std::string

float RoundDva(float a); // ���������� float �� 2� ������ ����� �������

void ReadingFile(int& Count, int& NumsHard, int& NumsSimple); // ������ ������ �� �����

void WritingFile(int Count, int NumsHard, int NumsSimple); // ������ ������ � ����