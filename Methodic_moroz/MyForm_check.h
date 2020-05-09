#pragma once
#include "MyForm2.h"

static string path_conf_check; // глобальная переменная для записи текущей директории конфигурационного файла
static string id_check; // глобальная переменная для идентификации пользователя
static string path_exe_check; // глобальная переменная для записи текущей директории exe файла


namespace Methodicmoroz {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm_check
	/// </summary>
	public ref class MyForm_check : public System::Windows::Forms::Form
	{
	public:
		bool btnQ, btnP; // переменные для кажатия клавиш Q и P
		MyForm_check(string path_e, string ident, string path_c)
			//MyForm2(void)
		{
			InitializeComponent();
			path_exe_check = path_e;
			id_check = ident;
			path_conf_check = path_c;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm_check()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label1;
	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(44, 38);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(264, 26);
			this->label1->TabIndex = 0;
			this->label1->Text = L"                              Приготовьтесь...\r\nДля начала теста нажмите [Q] и [P"
				L"] одновременно";
			// 
			// MyForm_check
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(367, 111);
			this->Controls->Add(this->label1);
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"MyForm_check";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Начало тестирования";
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm_check::MyForm_check_KeyDown);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void MyForm_check_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		// обработчики нажатия клавиш
		if (e->KeyCode == Keys::Q) btnQ = true;
		if (e->KeyCode == Keys::P) btnP = true;

		if ((btnQ == true) && (btnP == true))
		{
			MyForm2^ F2 = gcnew MyForm2(path_exe_check, id_check, path_conf_check);
			F2->ShowDialog();
			this->Close();
		}
	}
	};
}
