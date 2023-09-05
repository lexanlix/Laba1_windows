#include "Functions.h"

using namespace System;
using namespace System::Windows::Forms;

int RandNum(int min, int max)
{	// Генерация рандомного числа в заданном диапазоне
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
	return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

int Hash(int num1, int num2)
{	// Хэш-функция
	double gg = (((num1 + num2) * 1.804 + num1 - 240.0) * (150.0 / 323.0));
	return static_cast<int>(gg);
}

int GPSCh(int n)
{	// Генератор псевдослучайных чисел
	unsigned long stepen = static_cast<unsigned long>(pow(n, 5));
	unsigned long one, one2, two, two2, three, y0;
	one = (stepen * 199) % 10;
	one2 = stepen * 199 - one;
	two = (one2 % 100) / 10;
	two2 = ((stepen * 199 - one) - (one2 % 100));
	three = (two2 % 1000) / 100;
	y0 = (one + two + three);
	double y = ((pow(y0, 4) - ((two + three) / (one + 1.0)) + 1.0) / 531401.0) * 150.0 + 1.0;
	return static_cast<int>(y);
}

void Search_simple(char I[16], char IDS_simple[151][17], int R_Chisla[151], int Data[2])
{	// Поиск по рехешированию с ГПСЧ
	int num1 = I[0]; int num2 = I[1];
	int val = Hash(num1, num2);
	//int Data[2] = { 1, 0 }; // Число сравнений и найден идент-ор или нет

	std::string id1, id2;

	for (int i = 0; i <= 15; i++)
	{
		id1 = id1 + I[i];
		id2 = id2 + IDS_simple[val][i];
	}

	if (id1 == id2)
	{
		Data[1] = 1;
		return;
	}
	else
	{
		for (int p = 1; p <= 150; p++)
		{
			id2.clear();
			int index = (val + R_Chisla[p]) % 150;
			for (int i = 0; i <= 15; i++)
				id2 = id2 + IDS_simple[index][i];

			Data[0]++;
			if (id1 == id2)
			{
				Data[1] = 1;
				return;
			}
			if (p == 150)
			{
				Data[1] = 0;
				Data[0]++;
				return;
			}
		}
	}
}

void Search_hard(char I[16], Identificator* Hash_table[151], int Data[2])
{	// Поиск по рехешированию методом цепочек
	int num1 = I[0]; int num2 = I[1];
	int val = Hash(num1, num2);
	//int Data[2] = { 1, 0 }; // Число сравнений и найден идент-ор или нет

	if (Hash_table[val] == nullptr)
	{
		Data[1] = 0;
		return;
	}
	else
	{
		std::string I1;
		for (int i = 0; i <= 15; i++)
			I1 = I1 + I[i];

		Identificator* Current = Hash_table[val];
		while (Current->GetNext() != nullptr)
		{
			Data[0]++;
			if (I1 == (Current->GetName()))
			{
				Data[1] = 1;
				return;
			}
			Current = Current->GetNext();
		}
		Data[0]++;
		if (I1 == (Current->GetName()))
		{
			Data[1] = 1;
			return;
		}
		else
		{
			Data[1] = 0;
			return;
		}
	}
}

void CreateIDS(char IDS[120][17])	// cоздание массива идентификаторов
{
	srand(static_cast<unsigned int>(time(0)));  // для более случайного распределения
	unsigned int gg = RandNum(40, 10000);		// в генерации идентификаторов
	for (int i = 0; i <= 119; i++)
	{
		unsigned int size = RandNum(1, 16);

		while (true)
		{
			IDS[i][0] = RandNum(65, 122);
			if ((IDS[i][0] == 95) || ((IDS[i][0] >= 65) && (IDS[i][0] <= 90)) || ((IDS[i][0] >= 97) && (IDS[i][0] <= 122)))
				break;
		}

		for (int j = size; j <= 16; j++)
		{
			IDS[i][j] = 32;
		}

		if (size == 1)
		{
			continue;
		}

		for (int j = 1; j <= (size - 1); j++)
		{
			while (true)
			{
				IDS[i][j] = RandNum(48, 122);
				if ((IDS[i][j] == 95) || ((IDS[i][j] >= 48) && (IDS[i][j] <= 57)) || ((IDS[i][j] >= 65) && (IDS[i][j] <= 90)) || ((IDS[i][j] >= 97) && (IDS[i][j] <= 122)))
					break;
			}
		}
	}
}

unsigned int PlaceIwithGPSCH(char IDS[120][17], char IDS_simple[151][17], int R_Chisla[151])
{	// Размещение идент-ов в массиве через хэш-функцию с рехешированием с использованием псевдослучайных чисел
	unsigned int c_simple = 0;

	for (int i = 0; i <= 150; i++)
		for (int j = 0; j <= 16; j++)
			IDS_simple[i][j] = 32;

	for (int i = 1; i <= 150; i++)
		R_Chisla[i] = GPSCh(i);

	for (int i = 0; i <= 119; i++)
	{
		int val = Hash(static_cast<int>(IDS[i][0]), static_cast<int>(IDS[i][1]));
		if (IDS_simple[val][0] == 32)
			for (int j = 0; j <= 16; j++)
				IDS_simple[val][j] = IDS[i][j];
		else
		{
			c_simple++;
			for (int p = 1; p <= 150; p++)
			{
				int index = (val + R_Chisla[p]) % 150;
				if (IDS_simple[index][0] == 32)
				{
					for (int j = 0; j <= 16; j++)
						IDS_simple[index][j] = IDS[i][j];
					break;
				}
				if (p == 150)
				{
					std::string Name;
					for (int j = 0; j <= 16; j++)
						if (IDS[i][j] != 32)
							Name = Name + IDS[i][j];
					String^ text = "Идентификатор '" + Convert_string_to_String(Name) + "' не был размещен способом (1).";
					MessageBox::Show(text);
				}
			}
		}
	}

	return c_simple;
}

unsigned int PlaceIwithChains(char IDS[120][17], Identificator* Hash_table[151])
{	// Размещение идент-ов в динамической памяти через хэш-функцию с рехешированием методом цепочек
	unsigned int c_hard = 0;

	for (int i = 0; i <= 150; i++)
		Hash_table[i] = nullptr;

	for (int i = 0; i <= 119; i++)
	{
		int val = Hash(static_cast<int>(IDS[i][0]), static_cast<int>(IDS[i][1]));
		std::string I;
		for (int j = 0; j <= 15; j++)
			I = I + IDS[i][j];
		if (Hash_table[val] == nullptr)
			Hash_table[val] = new Identificator(I);
		else
		{
			c_hard++;
			Identificator* Next = new Identificator(I);
			Identificator* Current = Hash_table[val]->GetNext();
			if (Current == nullptr)
				Hash_table[val]->SetNext(Next);
			else
			{
				while (Current->GetNext() != nullptr)
					Current = Current->GetNext();
				Current->SetNext(Next);
			}
		}
	}

	return c_hard;
}




// Конвертируем System::string ^ в std::string
std::string& Convert_String_to_string(String^ s, std::string& os)
{
	using namespace Runtime::InteropServices;
	const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
	os = chars;
	Marshal::FreeHGlobal(IntPtr((void*)chars));

	return os;
}

// Конвертируем std::string в System::string ^
String^ Convert_string_to_String(std::string& os, String^ s)
{
	s = gcnew System::String(os.c_str());

	return s;
}

// Конвертируем System::string ^ в std::string
std::string& Convert_String_to_string(String^ s)
{
	std::string os;
	using namespace Runtime::InteropServices;
	const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
	os = chars;
	Marshal::FreeHGlobal(IntPtr((void*)chars));

	return os;

}

// Конвертируем std::string в System::string ^
String^ Convert_string_to_String(std::string& os)
{
	System::String^ s = gcnew System::String(os.c_str());

	return s;
}

// Конвертируем char* в System::String^
System::String^ Convert_char_to_String(char* ch)
{
	char* chr = new char();
	chr = ch;
	System::String^ str;

	for (int i = 0; chr[i] != '\0'; i++)
		str += wchar_t(ch);

	return str;
}

//Конвертируем System::String^ в char*
char* Convert_String_to_char(System::String^ string)
{
	using namespace System::Runtime::InteropServices;
	return (char*)(void*)Marshal::StringToHGlobalAnsi(string);
}

//Конвертируем Int в std::string
std::string IntTostring(int a)
{
	char intStr[4];
	itoa(a, intStr, 10);
	std::string S = intStr;
	return S;
}

// Округление float до 2х знаков после запятой
float RoundDva(float a) 
{
	float b = a * 100; 
	b = roundf(b);
	b = b / 100; 
	return b;
}

// Чтение данных из файла
void ReadingFile(int& Count, int& NumsHard, int& NumsSimple)
{
	std::string line, sCount, sNumsHard, sNumsSimple;
	std::ifstream in("Data.txt");
	if (in.is_open())
		while (std::getline(in, line))
			std::cout << line << std::endl;
	int N = line.size();
	int c = 0;
	for (int i = 0; i < N; i++)
	{
		if (line[i] == 32)
			c++;
		switch (c)
		{
		case 0:
			sCount = sCount + line[i];
			break;
		case 1:
			sNumsSimple = sNumsSimple + line[i];
			break;
		case 2:
			sNumsHard = sNumsHard + line[i];
			break;
		}
	}
	Count = std::stoi(sCount);
	NumsSimple = std::stoi(sNumsSimple);
	NumsHard = std::stoi(sNumsHard);
}

// Запись данных в файл
void WritingFile(int Count, int NumsHard, int NumsSimple)
{
	std::ofstream out;
	out.open("Data.txt");
	if (out.is_open())
		out << Count << " " << NumsSimple << " " << NumsHard;
	return;
}