#pragma once
#include "Connector.h"
#include "windows.h"

namespace JAProjectEdgeDetection {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Podsumowanie informacji o MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
		Connector* connector;
	public:
		MainForm(void)
		{
			InitializeComponent();

			connector = new Connector();
		}

	protected:
		/// <summary>
		/// Wyczyœæ wszystkie u¿ywane zasoby.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel1;
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel2;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::GroupBox^ groupBox1;
	private: System::Windows::Forms::RadioButton^ radioButton2;
	private: System::Windows::Forms::RadioButton^ radioButton1;
	private: System::Windows::Forms::TrackBar^ trackBar1;
	private: System::Windows::Forms::GroupBox^ groupBox2;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::GroupBox^ groupBox3;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::PictureBox^ pictureBox2;
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel3;

	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel2;
	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^ chart1;
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel4;
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel1;
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel3;
	private: System::Windows::Forms::Label^ label9;
	private: System::Windows::Forms::ListBox^ listBox1;
	protected:


	protected:

	private:
		/// <summary>
		/// Wymagana zmienna projektanta.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Metoda wymagana do obs³ugi projektanta — nie nale¿y modyfikowaæ
		/// jej zawartoœci w edytorze kodu.
		/// </summary>
		void InitializeComponent(void)
		{
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea5 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^ legend5 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^ series5 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::DataPoint^ dataPoint13 = (gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(1,
				0));
			System::Windows::Forms::DataVisualization::Charting::DataPoint^ dataPoint14 = (gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(2,
				0));
			System::Windows::Forms::DataVisualization::Charting::DataPoint^ dataPoint15 = (gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(3,
				0));
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->tableLayoutPanel2 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->radioButton2 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
			this->trackBar1 = (gcnew System::Windows::Forms::TrackBar());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->tableLayoutPanel3 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->flowLayoutPanel2 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->tableLayoutPanel4 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->flowLayoutPanel1 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->flowLayoutPanel3 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->tableLayoutPanel1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			this->tableLayoutPanel2->SuspendLayout();
			this->groupBox1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->BeginInit();
			this->groupBox2->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->tableLayoutPanel3->SuspendLayout();
			this->flowLayoutPanel2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->BeginInit();
			this->tableLayoutPanel4->SuspendLayout();
			this->flowLayoutPanel1->SuspendLayout();
			this->flowLayoutPanel3->SuspendLayout();
			this->SuspendLayout();
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->tableLayoutPanel1->ColumnCount = 1;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel1->Controls->Add(this->pictureBox1, 0, 0);
			this->tableLayoutPanel1->Controls->Add(this->pictureBox2, 0, 1);
			this->tableLayoutPanel1->Location = System::Drawing::Point(733, 12);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 2;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(685, 756);
			this->tableLayoutPanel1->TabIndex = 1;
			// 
			// pictureBox1
			// 
			this->pictureBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->pictureBox1->Location = System::Drawing::Point(3, 3);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(679, 372);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			// 
			// pictureBox2
			// 
			this->pictureBox2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->pictureBox2->Location = System::Drawing::Point(3, 381);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(679, 372);
			this->pictureBox2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox2->TabIndex = 1;
			this->pictureBox2->TabStop = false;
			// 
			// tableLayoutPanel2
			// 
			this->tableLayoutPanel2->ColumnCount = 2;
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel2->Controls->Add(this->button2, 1, 0);
			this->tableLayoutPanel2->Controls->Add(this->button3, 1, 1);
			this->tableLayoutPanel2->Controls->Add(this->groupBox1, 0, 0);
			this->tableLayoutPanel2->Controls->Add(this->trackBar1, 0, 1);
			this->tableLayoutPanel2->Controls->Add(this->groupBox2, 0, 2);
			this->tableLayoutPanel2->Controls->Add(this->groupBox3, 1, 2);
			this->tableLayoutPanel2->Location = System::Drawing::Point(13, 12);
			this->tableLayoutPanel2->Name = L"tableLayoutPanel2";
			this->tableLayoutPanel2->RowCount = 3;
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 48)));
			this->tableLayoutPanel2->Size = System::Drawing::Size(714, 159);
			this->tableLayoutPanel2->TabIndex = 2;
			// 
			// button2
			// 
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->button2->Location = System::Drawing::Point(360, 3);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(351, 49);
			this->button2->TabIndex = 0;
			this->button2->Text = L"Load Image";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MainForm::button2_Click);
			// 
			// button3
			// 
			this->button3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->button3->Location = System::Drawing::Point(360, 58);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(351, 49);
			this->button3->TabIndex = 1;
			this->button3->Text = L"Edge detection filter";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MainForm::button3_Click);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->radioButton2);
			this->groupBox1->Controls->Add(this->radioButton1);
			this->groupBox1->Location = System::Drawing::Point(3, 3);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(351, 49);
			this->groupBox1->TabIndex = 2;
			this->groupBox1->TabStop = false;
			// 
			// radioButton2
			// 
			this->radioButton2->AutoSize = true;
			this->radioButton2->Checked = true;
			this->radioButton2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->radioButton2->Location = System::Drawing::Point(11, 10);
			this->radioButton2->Name = L"radioButton2";
			this->radioButton2->Size = System::Drawing::Size(129, 29);
			this->radioButton2->TabIndex = 1;
			this->radioButton2->TabStop = true;
			this->radioButton2->Text = L"C++ library";
			this->radioButton2->UseVisualStyleBackColor = true;
			this->radioButton2->CheckedChanged += gcnew System::EventHandler(this, &MainForm::radioButton2_CheckedChanged);
			// 
			// radioButton1
			// 
			this->radioButton1->AutoSize = true;
			this->radioButton1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->radioButton1->Location = System::Drawing::Point(204, 10);
			this->radioButton1->Name = L"radioButton1";
			this->radioButton1->Size = System::Drawing::Size(130, 29);
			this->radioButton1->TabIndex = 0;
			this->radioButton1->Text = L"Asm library";
			this->radioButton1->UseVisualStyleBackColor = true;
			this->radioButton1->CheckedChanged += gcnew System::EventHandler(this, &MainForm::radioButton1_CheckedChanged);
			// 
			// trackBar1
			// 
			this->trackBar1->Cursor = System::Windows::Forms::Cursors::Cross;
			this->trackBar1->Location = System::Drawing::Point(3, 58);
			this->trackBar1->Maximum = 64;
			this->trackBar1->Minimum = 1;
			this->trackBar1->Name = L"trackBar1";
			this->trackBar1->Size = System::Drawing::Size(351, 49);
			this->trackBar1->TabIndex = 3;
			this->trackBar1->TickStyle = System::Windows::Forms::TickStyle::Both;
			this->trackBar1->Value = 1;
			this->trackBar1->ValueChanged += gcnew System::EventHandler(this, &MainForm::trackBar1_ValueChanged);
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->label2);
			this->groupBox2->Controls->Add(this->label1);
			this->groupBox2->Location = System::Drawing::Point(3, 113);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(351, 43);
			this->groupBox2->TabIndex = 4;
			this->groupBox2->TabStop = false;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->label2->Location = System::Drawing::Point(199, 8);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(23, 25);
			this->label2->TabIndex = 1;
			this->label2->Text = L"1";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->label1->Location = System::Drawing::Point(6, 8);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(178, 25);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Number of threads:";
			this->label1->Click += gcnew System::EventHandler(this, &MainForm::label1_Click);
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->label4);
			this->groupBox3->Controls->Add(this->label3);
			this->groupBox3->Location = System::Drawing::Point(360, 113);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(351, 43);
			this->groupBox3->TabIndex = 5;
			this->groupBox3->TabStop = false;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->label4->Location = System::Drawing::Point(167, 8);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(51, 25);
			this->label4->TabIndex = 1;
			this->label4->Text = L"C++";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->label3->Location = System::Drawing::Point(6, 8);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(155, 25);
			this->label3->TabIndex = 0;
			this->label3->Text = L"Choosen library:";
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			this->openFileDialog1->InitialDirectory = L"C:\\";
			// 
			// tableLayoutPanel3
			// 
			this->tableLayoutPanel3->ColumnCount = 1;
			this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel3->Controls->Add(this->flowLayoutPanel2, 0, 0);
			this->tableLayoutPanel3->Controls->Add(this->tableLayoutPanel4, 0, 1);
			this->tableLayoutPanel3->Location = System::Drawing::Point(13, 178);
			this->tableLayoutPanel3->Name = L"tableLayoutPanel3";
			this->tableLayoutPanel3->RowCount = 2;
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 56.66667F)));
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 43.33333F)));
			this->tableLayoutPanel3->Size = System::Drawing::Size(717, 590);
			this->tableLayoutPanel3->TabIndex = 3;
			// 
			// flowLayoutPanel2
			// 
			this->flowLayoutPanel2->Controls->Add(this->label8);
			this->flowLayoutPanel2->Controls->Add(this->chart1);
			this->flowLayoutPanel2->Location = System::Drawing::Point(3, 3);
			this->flowLayoutPanel2->Name = L"flowLayoutPanel2";
			this->flowLayoutPanel2->Size = System::Drawing::Size(708, 328);
			this->flowLayoutPanel2->TabIndex = 1;
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->label8->Location = System::Drawing::Point(3, 0);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(159, 25);
			this->label8->TabIndex = 1;
			this->label8->Text = L"Colors histogram";
			// 
			// chart1
			// 
			chartArea5->AxisX->Crossing = 1.7976931348623157E+308;
			chartArea5->AxisX->Maximum = 3;
			chartArea5->AxisX->Minimum = 1;
			chartArea5->AxisY->Maximum = 100;
			chartArea5->AxisY->Minimum = 0;
			chartArea5->Name = L"ChartArea1";
			this->chart1->ChartAreas->Add(chartArea5);
			legend5->Enabled = false;
			legend5->Name = L"Legend1";
			this->chart1->Legends->Add(legend5);
			this->chart1->Location = System::Drawing::Point(3, 28);
			this->chart1->Name = L"chart1";
			series5->ChartArea = L"ChartArea1";
			series5->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Bar;
			series5->Legend = L"Legend1";
			series5->Name = L"Series1";
			dataPoint14->Color = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			dataPoint15->Color = System::Drawing::Color::Red;
			dataPoint15->Label = L"";
			series5->Points->Add(dataPoint13);
			series5->Points->Add(dataPoint14);
			series5->Points->Add(dataPoint15);
			this->chart1->Series->Add(series5);
			this->chart1->Size = System::Drawing::Size(705, 300);
			this->chart1->TabIndex = 0;
			this->chart1->Text = L"chart1";
			// 
			// tableLayoutPanel4
			// 
			this->tableLayoutPanel4->ColumnCount = 1;
			this->tableLayoutPanel4->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel4->Controls->Add(this->flowLayoutPanel1, 0, 0);
			this->tableLayoutPanel4->Controls->Add(this->flowLayoutPanel3, 0, 1);
			this->tableLayoutPanel4->Location = System::Drawing::Point(3, 337);
			this->tableLayoutPanel4->Name = L"tableLayoutPanel4";
			this->tableLayoutPanel4->RowCount = 2;
			this->tableLayoutPanel4->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 24.53988F)));
			this->tableLayoutPanel4->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 75.46012F)));
			this->tableLayoutPanel4->Size = System::Drawing::Size(711, 250);
			this->tableLayoutPanel4->TabIndex = 2;
			// 
			// flowLayoutPanel1
			// 
			this->flowLayoutPanel1->Controls->Add(this->label5);
			this->flowLayoutPanel1->Controls->Add(this->label6);
			this->flowLayoutPanel1->Controls->Add(this->label7);
			this->flowLayoutPanel1->Location = System::Drawing::Point(3, 3);
			this->flowLayoutPanel1->Name = L"flowLayoutPanel1";
			this->flowLayoutPanel1->Size = System::Drawing::Size(705, 55);
			this->flowLayoutPanel1->TabIndex = 0;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Arial Narrow", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->label5->Location = System::Drawing::Point(3, 0);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(219, 29);
			this->label5->TabIndex = 0;
			this->label5->Text = L"Time taken to complete:";
			this->label5->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Arial Narrow", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->label6->Location = System::Drawing::Point(228, 0);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(20, 29);
			this->label6->TabIndex = 1;
			this->label6->Text = L"-";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"Arial Narrow", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->label7->Location = System::Drawing::Point(254, 0);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(49, 29);
			this->label7->TabIndex = 2;
			this->label7->Text = L" ms.";
			// 
			// flowLayoutPanel3
			// 
			this->flowLayoutPanel3->Controls->Add(this->label9);
			this->flowLayoutPanel3->Controls->Add(this->listBox1);
			this->flowLayoutPanel3->Location = System::Drawing::Point(3, 64);
			this->flowLayoutPanel3->Name = L"flowLayoutPanel3";
			this->flowLayoutPanel3->Size = System::Drawing::Size(705, 183);
			this->flowLayoutPanel3->TabIndex = 1;
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Font = (gcnew System::Drawing::Font(L"Arial Narrow", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->label9->Location = System::Drawing::Point(3, 0);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(174, 29);
			this->label9->TabIndex = 4;
			this->label9->Text = L"History of resoults:";
			this->label9->Click += gcnew System::EventHandler(this, &MainForm::label9_Click);
			// 
			// listBox1
			// 
			this->listBox1->FormattingEnabled = true;
			this->listBox1->ItemHeight = 16;
			this->listBox1->Location = System::Drawing::Point(183, 3);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(512, 148);
			this->listBox1->TabIndex = 3;
			this->listBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::listBox1_SelectedIndexChanged);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1430, 780);
			this->Controls->Add(this->tableLayoutPanel3);
			this->Controls->Add(this->tableLayoutPanel2);
			this->Controls->Add(this->tableLayoutPanel1);
			this->MaximizeBox = false;
			this->MaximumSize = System::Drawing::Size(1448, 827);
			this->MinimumSize = System::Drawing::Size(1448, 827);
			this->Name = L"MainForm";
			this->Text = L"Edge Detection";
			this->tableLayoutPanel1->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			this->tableLayoutPanel2->ResumeLayout(false);
			this->tableLayoutPanel2->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->EndInit();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			this->tableLayoutPanel3->ResumeLayout(false);
			this->flowLayoutPanel2->ResumeLayout(false);
			this->flowLayoutPanel2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->EndInit();
			this->tableLayoutPanel4->ResumeLayout(false);
			this->flowLayoutPanel1->ResumeLayout(false);
			this->flowLayoutPanel1->PerformLayout();
			this->flowLayoutPanel3->ResumeLayout(false);
			this->flowLayoutPanel3->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion

	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		//this button doesn't exists, method never gets invoked
	}


	private: System::Void radioButton1_CheckedChanged(System::Object^ sender, System::EventArgs^ e) 
	{
		//Nothing, second radioButton handles changes
	}

	//LOAD IMAGE, UPDATE HISTORAGM
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		connector->setUnready();
		this->openFileDialog1->ShowDialog();
			try {
			//Show image
			pictureBox1->ImageLocation = this->openFileDialog1->FileName;
			pictureBox1->Load();
			
			auto originalImageSize = pictureBox1->Image->Size;
			if (originalImageSize.Height > 11000 || originalImageSize.Width > 11000)
				throw 2;
			if (!pictureBox1->Image->RawFormat->Equals(System::Drawing::Imaging::ImageFormat::Bmp) &&
				!pictureBox1->Image->RawFormat->Equals(System::Drawing::Imaging::ImageFormat::Jpeg) &&
				!pictureBox1->Image->RawFormat->Equals(System::Drawing::Imaging::ImageFormat::Png) &&
				!pictureBox1->Image->RawFormat->Equals(System::Drawing::Imaging::ImageFormat::Tiff))
				throw 1;

			//set image path to the connector
			connector->setImage(connector->converSysStrToStdStr(this->openFileDialog1->FileName));

			//Get histogram and update graph
			if (connector->startHistogram()) {
				int histData[] = { connector->getGAmount(),connector->getBAmount(), connector->getRAmount() };
				updateHistogram(histData);
			}

			}
			catch (int mynum)
			{
				if(mynum == 1)
				System::Windows::Forms::MessageBox::Show("Format not supported,\nplese change image");
				else if(mynum == 2)
				System::Windows::Forms::MessageBox::Show("File resoulution is too big,\nplease try smaller image");
			}
			catch (...)
			{
				System::Windows::Forms::MessageBox::Show("Can't load resource,\nplease choose .bmp, .png, .jpeg, .jpg or .tiff file");
			}
	}

	private: void updateHistogram(int histData[]) 
	{
		this->chart1->Series[0]->Points->Clear();
		System::Windows::Forms::DataVisualization::Charting::DataPoint^ newdataPoint1 = (gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(1,
			(double)histData[0]));
		System::Windows::Forms::DataVisualization::Charting::DataPoint^ newdataPoint2 = (gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(2,
			(double)histData[1]));
		System::Windows::Forms::DataVisualization::Charting::DataPoint^ newdataPoint3 = (gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(3,
			(double)histData[2]));
		newdataPoint1->Color = System::Drawing::Color::Red; 
		newdataPoint2->Color = System::Drawing::Color::Green;
		newdataPoint3->Color = System::Drawing::Color::Blue;
		this->chart1->Series[0]->Points->Add(newdataPoint1);
		this->chart1->Series[0]->Points->Add(newdataPoint2);
		this->chart1->Series[0]->Points->Add(newdataPoint3);
	}

	//NUMBER OF THREADS, ONLY VISUAL CHANGES
	private: System::Void trackBar1_ValueChanged(System::Object^ sender, System::EventArgs^ e) 
	{
		int i = this->trackBar1->Value;
		this->label2->Text = i.ToString();
	}

	//CHANGES OF THE LIBRART, ONLY VISUAL
	private: System::Void radioButton2_CheckedChanged(System::Object^ sender, System::EventArgs^ e) 
	{
		if (this->radioButton2->Checked == true)
			this->label4->Text = "C++";
		else 
			this->label4->Text = "Asm";
	}

	//RUN FILTER BUTTON
	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		//Set choosen library
		int modeLib = 0;
		if (this->radioButton2->Checked == false)
			modeLib = 1;
		connector->setChoosenLib(modeLib);

		//Set number of threads
		int numThreads = 1;
		numThreads = this->trackBar1->Value;
		connector->setNumberOfThreads(numThreads);

		//Run filter
		bool filterSucces = false;
		if (connector->isReadyToFilter())
			filterSucces = connector->startFilterManager();
	
		if (filterSucces) {
			//Update filtered image
			this->pictureBox2->ImageLocation = connector->converStdStrToSysStr(connector->getFilteredImgPath());
			this->pictureBox2->Load();

			//Update time TO DO, should be in table not as a field, or at least table /w history + field /w newest time
			long time = connector->getTime(); 
			this->label6->Text = time.ToString();
			this->listBox1->Items->Add(connector->createFilterRaport(this->listBox1->Items->Count));
		}
	}


private: System::Void listBox1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void label9_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
}
}; //class end
} //Namespace end
