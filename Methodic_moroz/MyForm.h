#pragma once

#include <string>
#include <ctime>
#include <time.h>
#include <iostream>
#include <fstream>
#include <Windows.h>
#include "MyForm2.h"
#include "MyForm_check.h"
#include <msclr\marshal_cppstd.h> 

using namespace std;

static string path_conf; // глобальная переменная для записи текущей директории конфигурационного файла
static string id; // глобальная переменная для идентификации пользователя
static string path_exe; // глобальная переменная для записи текущей директории exe файла

namespace Methodicmoroz {
	using namespace msclr::interop;
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	using namespace System::Text;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm()
		{
			InitializeComponent();
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ button_start;
	private: System::Windows::Forms::TextBox^ textBox_instruction;


	protected:

	protected:

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button_start = (gcnew System::Windows::Forms::Button());
			this->textBox_instruction = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// button_start
			// 
			this->button_start->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->button_start->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->button_start->Font = (gcnew System::Drawing::Font(L"Matura MT Script Capitals", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button_start->Location = System::Drawing::Point(203, 241);
			this->button_start->Name = L"button_start";
			this->button_start->Size = System::Drawing::Size(368, 72);
			this->button_start->TabIndex = 0;
			this->button_start->Text = L"Начать ";
			this->button_start->UseVisualStyleBackColor = true;
			this->button_start->Click += gcnew System::EventHandler(this, &MyForm::button_start_Click);
			// 
			// textBox_instruction
			// 
			this->textBox_instruction->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->textBox_instruction->Font = (gcnew System::Drawing::Font(L"Harrington", 20.25F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox_instruction->Location = System::Drawing::Point(12, 12);
			this->textBox_instruction->Multiline = true;
			this->textBox_instruction->Name = L"textBox_instruction";
			this->textBox_instruction->ReadOnly = true;
			this->textBox_instruction->Size = System::Drawing::Size(766, 223);
			this->textBox_instruction->TabIndex = 1;
			this->textBox_instruction->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::AppWorkspace;
			this->ClientSize = System::Drawing::Size(790, 325);
			this->Controls->Add(this->textBox_instruction);
			this->Controls->Add(this->button_start);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->Name = L"MyForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Инструкция";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button_start_Click(System::Object^ sender, System::EventArgs^ e) {
		this->button_start->Enabled = false; // выключение кнопки "Начать"
		this->button_start->Visible = false; // делаем кнопку "Начать" невидимой
		MyForm_check^ F_check = gcnew MyForm_check(path_exe, id, path_conf);
		//this->WindowState = System::Windows::Forms::FormWindowState::Minimized;
		F_check->ShowDialog();
		this->button_start->Enabled = true; // включение кнопки "Начать"
		this->button_start->Visible = true; // делаем кнопку "Начать" видимой
	}

private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
	char load_string[333];
	
	// ОБРАБОТКА ДАННЫХ ИЗ cmd 
	LPWSTR* Arglist;
	int nArgs;
	Arglist = CommandLineToArgvW(GetCommandLineW(), &nArgs);
	char** argv = new char* [nArgs];
	for (int i = 0; i < nArgs; i++) {
		LPWSTR warg = Arglist[i];
		// Compute the size of the required buffer
		DWORD size = WideCharToMultiByte(CP_UTF8, 0, warg, -1, NULL, 0, NULL, NULL);

		// Do the actual conversion
		argv[i] = new char[size];
		DWORD result = WideCharToMultiByte(CP_UTF8, 0, warg, -1, argv[i], size, NULL, NULL);
	}

	path_conf = "";

	if (nArgs == 3)
	{
		path_exe = argv[0];
		id = argv[1];
		path_conf = argv[2];
	}
	else if(nArgs == 2)
	{
		path_exe = argv[0];
		id = argv[1];
	}
	else if (nArgs == 1)
	{
		path_exe = argv[0];
		id = "id_example";
	}
	else
	{
		MessageBox::Show("Вы неправильно ввели параметры. \nПерезапустите приложение с правильными параметрами!\n\nПример запуска приложения через cmd:\n <Путь к exe файлу> <Персональный id> <Путь к конфигурационному файлу>\n\nЕсли вы находитесь в папке с exe и/или конфигурационным файлом, то полный путь писать не обязательно, достаточно только их имя и расширение.", "Закрытие", MessageBoxButtons::OK, MessageBoxIcon::Error);
		this->Close();
	}
	/*
	const int LEN = 255;
	TCHAR tmp[LEN];
	//char tmp[LEN];
	memset(tmp, 0, LEN);
	int i = GetModuleFileName(GetModuleHandle(NULL), tmp, LEN) - 1;
	do {
		if (tmp[i] == '\\') {
			break;
		}
		tmp[i] = 0;
	} while (--i);
	
	String^ config_path;
	if (nArgs == 3)
		config_path = gcnew String(argv[2]);
	else
		config_path = gcnew String(&tmp[0]);

	path_conf = config_path.c_str() + "\instruction.txt";
	*/
	ifstream instruction("instruction.txt"); // открытие файла на чтение
	instruction.getline(load_string, sizeof(load_string)); // считывание текста из файла 
	String^ instruction_text = gcnew String(load_string); // создание переменной instruction_text типа String^, для записи текста в textbox

	this->textBox_instruction->Text = instruction_text; // запись в textbox

	instruction.close();

	path_conf += "\config.txt";
}

};
}
