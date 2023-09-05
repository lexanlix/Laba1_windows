#include <iostream>
#include "MyForm.h"
#include "Functions.h"
#include "Identificator.h"
#include "math.h"

using namespace System;
using namespace System::Windows::Forms;

char IDS[120][17];				// Изначальная таблица идентификаторов

char IDS_simple[151][17];		// Таблица идентификаторов, в которую они размещаются по рехешированию с ГПСЧ
int R_Chisla[151];				// Таблица ПСЧ
unsigned int c_simple = 0;		// число коллизий для метода с ПСЧ

Identificator* Hash_table[151];
unsigned int c_hard = 0;		// число коллизий для метода цепочек

int CompareNumsHard = 0, CompareNumsSimple = 0; // Общее число сравнений для обоих поисков
float AverageCompareHard = 0, AverageCompareSimple = 0; // Среднее число сравнений для обоих поисков
int S_count = 0; // Число поисков

[STAThreadAttribute]
void main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	
	Laba1windows::MyForm form;
	Application::Run(% form);
}

System::Void Laba1windows::MyForm::button2_Click(System::Object^ sender, System::EventArgs^ e) //кнопка Завершить
{
	WritingFile(S_count, CompareNumsHard, CompareNumsSimple);
	Application::Exit();
}

System::Void Laba1windows::MyForm::button1_Click(System::Object^ sender, System::EventArgs^ e) //кнопка Искать
{
	char I[16];
	std::string Id;
	Convert_String_to_string(textBox1->Text, Id);
	S_count++;

	if (Id.empty())
	{
		return;
	}

	int c = Id.size();

	for (int i = 0; i <= 15; i++)
	{
		if (i < c)
		{
			I[i] = Id[i];
			continue;
		}
		I[i] = 32;
	}
	
	int Data_Simple[2] = { 1, 0 };
	int Data_Hard[2] = { 1, 0 };

	Search_simple(I, IDS_simple, R_Chisla, Data_Simple);
	Search_hard(I, Hash_table, Data_Hard);
	
	CompareNumsSimple = CompareNumsSimple + Data_Simple[0];
	CompareNumsHard = CompareNumsHard + Data_Hard[0];

	AverageCompareSimple = static_cast<float>(CompareNumsSimple) / S_count;
	AverageCompareHard = static_cast<float>(CompareNumsHard) / S_count;
	
	label13->Text = Convert_string_to_String(IntTostring(Data_Simple[0]));
	label12->Text = Convert_string_to_String(IntTostring(Data_Hard[0]));
	label14->Text = Convert_string_to_String(IntTostring(CompareNumsSimple));
	label15->Text = Convert_string_to_String(IntTostring(CompareNumsHard));
	label16->Text = Convert_string_to_String(std::to_string(RoundDva(AverageCompareSimple)))->Remove(5);
	label20->Text = Convert_string_to_String(std::to_string(RoundDva(AverageCompareHard)))->Remove(5);
	label4->Text = Convert_string_to_String(IntTostring(S_count));

	if (Data_Simple[1] == 1)
		label7->Text = "Идентификатор найден!";
	else
		label7->Text = "Идентификатор не найден.";

	if (Data_Hard[1] == 1)
		label10->Text = "Идентификатор найден!";
	else
		label10->Text = "Идентификатор не найден.";
}

System::Void Laba1windows::MyForm::button3_Click(System::Object^ sender, System::EventArgs^ e) //кнопка Сброс
{
	CompareNumsHard = 0; 
	CompareNumsSimple = 0; 
	AverageCompareHard = 0;
	AverageCompareSimple = 0;
	S_count = 0; 

	label4->Text = Convert_string_to_String(IntTostring(S_count));
	label7->Text = "";
	label10->Text = "";
	label13->Text = "";
	label12->Text = "";
	label14->Text = "";
	label15->Text = "";
	label16->Text = "";
	label20->Text = "";

}

System::Void Laba1windows::MyForm::MyForm_Shown(System::Object^ sender, System::EventArgs^ e) // при открытии окна
{
	CreateIDS(IDS);
	
	c_hard = PlaceIwithChains(IDS, Hash_table);
	listBox1->Items->Clear();

	for (int i = 0; i <= 150; i++)
	{
		if (Hash_table[i] == nullptr)
			continue;
		Identificator* Current = Hash_table[i];
		listBox1->Items->Add(Convert_string_to_String(Current->GetName()));
		while (Current->GetNext() != nullptr)
		{
			Current = Current->GetNext();
			listBox1->Items->Add(Convert_string_to_String(Current->GetName()));
		}
	}

	ReadingFile(S_count, CompareNumsHard, CompareNumsSimple);

	label21->Text = "";
	label25->Text = Convert_string_to_String(IntTostring(c_hard));
	label4->Text = Convert_string_to_String(IntTostring(S_count));
	label7->Text = "";
	label10->Text = "";
	label13->Text = "";
	label12->Text = "";
	label14->Text = Convert_string_to_String(IntTostring(CompareNumsSimple));
	label15->Text = Convert_string_to_String(IntTostring(CompareNumsHard));
	label16->Text = "";
	label20->Text = "";
	if (S_count != 0)
	{
		AverageCompareSimple = static_cast<float>(CompareNumsSimple) / S_count;
		AverageCompareHard = static_cast<float>(CompareNumsHard) / S_count;
		label16->Text = Convert_string_to_String(std::to_string(RoundDva(AverageCompareSimple)))->Remove(5);
		label20->Text = Convert_string_to_String(std::to_string(RoundDva(AverageCompareHard)))->Remove(5);
	}

	c_simple = PlaceIwithGPSCH(IDS, IDS_simple, R_Chisla);
	label21->Text = Convert_string_to_String(IntTostring(c_simple));
}

System::Void Laba1windows::MyForm::listBox1_MouseDoubleClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{		// копирование идентификатора в буфер обмена при двойном клике на него
	Clipboard::SetText(listBox1->SelectedItem->ToString());
}