#pragma once
#include <string>
#include <ctime>
//#include "stdafx.h"
#include <time.h>
#include <iostream>
#include <fstream>
#include <Windows.h>
#include "MyForm2.h"

using namespace std;

static string outfile;
static string path_config; // глобальная переменная для записи текущей директории конфигурационного файла
static string id_pers; // глобальная переменная для идентификации пользователя
static string path_exe_file; // глобальная переменная для записи текущей директории exe файла


namespace Methodicmoroz {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;


	/// <summary>
	/// Summary for MyForm2
	/// </summary>
	public ref class MyForm2 : public System::Windows::Forms::Form
	{
	public:
		int version, count_present, min_t, max_t; // переменные из конфигурационного файла
		// version - версия программы: методика Мороз/ ПЗМР
		// count_present - максимальное количество представлений
		//  min_t, max_t - минимальное/максимальное время паузы перед показам белого квадрата 
		bool btnQ, btnP; // переменные для кажатия клавиш Q и P 
		double end_time, start_present, start_time, react_time;
		// strat_present - время начала показал белого квадрата (представления)
		// start_time - время запуска методики
		double *resQ, * resP;
		int k;
		char *Date;
		int timeCounter;
	private: System::Windows::Forms::Timer^ timer;
	public:
		char* Time;
		MyForm2(string path_e, string ident, string path_c)
		//MyForm2(void)
		{
			InitializeComponent();
			path_exe_file = path_e;
			id_pers = ident;
			path_config = path_c;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm2()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^ white_square;
	private: System::ComponentModel::IContainer^ components;
	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->white_square = (gcnew System::Windows::Forms::PictureBox());
			this->timer = (gcnew System::Windows::Forms::Timer(this->components));
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->white_square))->BeginInit();
			this->SuspendLayout();
			// 
			// white_square
			// 
			this->white_square->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->white_square->BackColor = System::Drawing::Color::White;
			this->white_square->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->white_square->Location = System::Drawing::Point(12, 12);
			this->white_square->Name = L"white_square";
			this->white_square->Size = System::Drawing::Size(112, 94);
			this->white_square->TabIndex = 2;
			this->white_square->TabStop = false;
			this->white_square->Visible = false;
			this->white_square->VisibleChanged += gcnew System::EventHandler(this, &MyForm2::white_square_VisibleChanged);
			// 
			// timer
			// 
			this->timer->Tick += gcnew System::EventHandler(this, &MyForm2::timer_Tick);
			// 
			// MyForm2
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->ClientSize = System::Drawing::Size(139, 120);
			this->Controls->Add(this->white_square);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"MyForm2";
			this->ShowIcon = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Methodic Moroz";
			this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MyForm2::MyForm2_FormClosing);
			this->Load += gcnew System::EventHandler(this, &MyForm2::MyForm2_Load);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm2::MyForm2_KeyDown);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->white_square))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void MyForm2_Load(System::Object^ sender, System::EventArgs^ e) {
		this->Refresh(); // обновление экрана
		setlocale(LC_ALL, "rus");
		srand(time(0));

		Date = new char[33];
		Time = new char[33];
		time_t seconds = time(NULL);
		tm* timeinfo = localtime(&seconds);
		//char* format = "%A, %B %d, %Y %I:%M:%S";
		char* format_date = "%d.%B.%Y;"; // формат записи даты
		char* format_time = "%I:%M:%S;"; // формат записи времени
		strftime(Date, 33, format_date, timeinfo); // запись даты 
		strftime(Time, 33, format_time, timeinfo); // запись времени

		ifstream conf(path_config); // открытие конфигурационного файла 
		int c_p, ver, mn_t, mx_t;
		// c_p - максимальное количество представлений
		// ver - версия программы: методика Мороз/ ПЗМР
		//  m_t, m_t - минимальное/максимальное время паузы перед показам белого квадрата 
		conf >> ver >> c_p >> mn_t >> mx_t; // считывание из файла 
		count_present = c_p; version = ver; min_t = mn_t; max_t = mx_t;
		conf.close();

		if (version == 1)
			outfile = id_pers + "_PZMR_A.csv";
		else
			outfile = id_pers + "_PZMR.csv";

		resQ = new double[count_present * sizeof(double)];
		resP = new double[count_present * sizeof(double)];
		k = 0;

		// обнуляем флаги нажатия клавиш
		btnQ = false; 
		btnP = false;

		//start_time = clock(); // время начала работы программы
		Sleep((rand() % (max_t * 1000 - min_t * 1000 + 1) + min_t * 1000));
		this->white_square->Visible = true; //отображаем белый квадрат

	}

	private: System::Void MyForm2_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		// обработчики нажатия клавиш
		if (e->KeyCode == Keys::Q)
		{
			if (this->white_square->Visible == true && btnQ == false)
			{
				end_time = clock(); // засекаем  время
				resQ[k] = (end_time - start_present) / 1000; // время реакции
			}
			btnQ = true;
		}

		if (e->KeyCode == Keys::P)
		{
			if (this->white_square->Visible == true && btnP == false)
			{
				end_time = clock(); // засекаем  время
				resP[k] = (end_time - start_present) / 1000; // время реакции
			}
			btnP = true;
		}

		if ((btnQ == true) && (btnP == true) && (this->white_square->Visible == true))
		{
			// обнуляем флаги нажатия клавиш
			btnQ = false;
			btnP = false;
			if (version == 2) // если методика Мороз
			{
				timer->Enabled = false; // останавливаем работу таймера
				timeCounter = 0; // обнуляем счетчик
			}
			this->white_square->Visible = false; // убираем белый квадрат
		}
	}

	private: System::Void white_square_VisibleChanged(System::Object^ sender, System::EventArgs^ e) {
		if (this->white_square->Visible == true)
		{
			if (count_present <= 0)
			{
				this->Close(); // закрываем форму, если закончилось кол-во предъявлений
			}
			this->Refresh();
			if (version == 2) // если методика Мороз
			{
				timeCounter = 0; // обнуляем счетчик
				timer->Interval = 100; // инвервал изменения значения таймера
				timer->Enabled = true; // запускаем таймер
			}
			count_present--;
			start_present = clock(); // если отобразили квадрат, то засекаем время, до нажатия клавиш
		}
		else
		{
			k++;
			Sleep((rand() % (max_t * 1000 - min_t * 1000 + 1) + min_t * 1000)); // делаем задержку
			// обнуляем флаги нажатия клавиш
			btnQ = false;
			btnP = false;
			this->white_square->Visible = true; // отображаем квадрат
		}
	}
private: System::Void MyForm2_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {
	int Q = 0, P = 0;

	ofstream result(outfile, ios::app);
	result << "\n" << "Date;Time;Hand;NPr;Tmin;Tmax";
	for (int i = 0; i < k; i++)
		result << ";" << "V" << i + 1;
	result << "\n";
	
	result << Date << Time << "L;" << k << ";" << min_t << ";" << max_t << ";";
	
	while (Q < k)
	{
		result << resQ[Q] << ';'; // если MS Excel не русифицирован, то ','
		// ; нужна для разделения результатов по столбцам
		Q++;
	}
	result << "\n";

	result << Date << Time << "R;" << k << ";" << min_t << ";" << max_t << ";";

	while (P < k)
	{
		result << resP[P] << ';'; // если MS Excel не русифицирован, то ','
		// ; нужна для разделения результатов по столбцам
		P++;
	}
	result << "\n";
	result.close(); // закрываем файл
}
private: System::Void timer_Tick(System::Object^ sender, System::EventArgs^ e) {
	timeCounter++;
	if (timeCounter == 20)
	{
		resQ[k] = 0;
		resP[k] = 0;
		// обнуляем флаги нажатия клавиш
		btnQ = false;
		btnP = false;
		timer->Enabled = false;
		timeCounter = 0;
		this->white_square->Visible = false; // убираем белый квадрат
	}
}
};
}
