#pragma once
#include "UserHashing.h"
#include "GitHubManager.h"
#include "Graph.h"

UserHashing UsersPasswords;
GitHubManager* github_main;
Graph followers;

Node* RepositoryView;
Node* RepositoryEdit;
bool show_create_repo_input = false;

string CurrentUserName = "";
int CurrentUserIndex = -1;

string ViewingUserName = "";
int ViewingUserIndex = -1;

namespace $safeprojectname$
{

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//

			UsersPasswords.LoadData();
			followers.LoadData();
			GitHubManager::LoadAllData(github_main);

			main_menu->Show();
			login_groupbox->Hide();
			register_groupbox->Hide();
			GitHub_groupbox->Hide();

			// Sub-Groupbox
			following_gb->Hide();
		}

		string ToCustomString(String^ str) {
			string s;
			for (int i = 0; i < str->Length; i++) {
				s += static_cast<char>(str[i]);
			}
			return s;
		}
		String^ ToCustomString(string str) {
			String^ s = gcnew String("");
			for (int i = 0; i < str.length(); i++) {
				s += (wchar_t) str[i];
			}
			return s;
		}
		void UpdateViewing() {
			if (ViewingUserName == "") { return; }
			if (ViewingUserIndex == -1) { return; }
			
			TabControl->SelectTab("view");

			vector<string> repos = github_main[ViewingUserIndex].GetRepoList();
			all_viewing_repo_list->Items->Clear();
			for (int i = 0; i < repos.size(); i++) {
				all_viewing_repo_list->Items->Add(ToCustomString(repos[i]));
			}

			view_username->Text = "Viewing: " + ToCustomString(ViewingUserName);
		}
		void UpdateRepositoryView(string ownername) {
			if (RepositoryView == nullptr) { return; }
			
			TabControl->SelectTab("files");

			repo_ownername->Text = ToCustomString("Owner: " + ownername);
			repo_reponame->Text = ToCustomString(RepositoryView->Repository_Name);

			int files_list = RepositoryView->files->GetListSize();
			all_repo_files_list->Items->Clear();
			for (int i = 0; i < files_list; i++) {
				String^ filename = ToCustomString(RepositoryView->files->GetDataFromIndex(i));
				all_repo_files_list->Items->Add(filename);
			}
			int commits_list = RepositoryView->commits->GetListSize();
			all_repo_commits_list->Items->Clear();
			for (int i = 0; i < files_list; i++) {
				String^ commit = ToCustomString(RepositoryView->commits->GetDataFromIndex(i));
				all_repo_commits_list->Items->Add(commit);
			}
		}
		void UpdateUserRepoList() {
			if (CurrentUserName == "") { return; }
			if (CurrentUserIndex == -1) { return; }

			all_user_repo_list->Items->Clear();
			vector<string> repos = github_main[CurrentUserIndex].GetRepoList();
			for (int i = 0; i < repos.size(); i++) {
				String^ reponame = ToCustomString(repos[i]);
				all_user_repo_list->Items->Add(reponame);
			}
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ login_register_btn;
	private: System::Windows::Forms::Label^ main_title;
	private: System::Windows::Forms::Button^ made_by_btn;
	private: System::Windows::Forms::Button^ quit_btn;
	private: System::Windows::Forms::GroupBox^ main_menu;
	private: System::Windows::Forms::GroupBox^ login_groupbox;
	private: System::Windows::Forms::Label^ login_title;
	private: System::Windows::Forms::Label^ login_username;
	private: System::Windows::Forms::Label^ login_password;
	private: System::Windows::Forms::TextBox^ login_username_input;
	private: System::Windows::Forms::TextBox^ login_password_input;
	private: System::Windows::Forms::Button^ login_user_btn;
	private: System::Windows::Forms::Button^ register_btn;
	private: System::Windows::Forms::Button^ login_goback_btn;

	private: System::Windows::Forms::GroupBox^ register_groupbox;
	private: System::Windows::Forms::Button^ go_to_mainmenu;

	private: System::Windows::Forms::Button^ go_back_login_page;

	private: System::Windows::Forms::Button^ register_user_btn;


	private: System::Windows::Forms::TextBox^ reg_password_input;

	private: System::Windows::Forms::TextBox^ reg_username_input;

	private: System::Windows::Forms::Label^ reg_password;

	private: System::Windows::Forms::Label^ reg_username;

	private: System::Windows::Forms::Label^ register_title;
	private: System::Windows::Forms::TextBox^ reg_password_input2;
	private: System::Windows::Forms::Label^ reg_password2;
	private: System::Windows::Forms::GroupBox^ GitHub_groupbox;
	private: System::Windows::Forms::Label^ gh_welcome;
	private: System::Windows::Forms::Label^ gh_username_title;


	private: System::Windows::Forms::ListBox^ all_following_list;
	private: System::Windows::Forms::GroupBox^ following_gb;
	private: System::Windows::Forms::Button^ show_users_btn;





	private: System::Windows::Forms::Button^ unfollow_btn;
	private: System::Windows::Forms::GroupBox^ users_gb;

	private: System::Windows::Forms::Button^ Follow_user_btn;
	private: System::Windows::Forms::Button^ view_usr_btn;



	private: System::Windows::Forms::Button^ show_following_btn;
	private: System::Windows::Forms::ListBox^ all_users_list;
private: System::Windows::Forms::TabControl^ TabControl;

	private: System::Windows::Forms::TabPage^ user;
	private: System::Windows::Forms::TabPage^ view;
	private: System::Windows::Forms::TabPage^ edit;
private: System::Windows::Forms::Button^ logout;
private: System::Windows::Forms::ListBox^ all_user_repo_list;
private: System::Windows::Forms::Label^ all_repo;
private: System::Windows::Forms::Button^ edit_repo_btn;
private: System::Windows::Forms::Button^ view_repo_btn;
private: System::Windows::Forms::Button^ create_new_repo_btn;
private: System::Windows::Forms::TabPage^ files;
private: System::Windows::Forms::Label^ repo_reponame;

private: System::Windows::Forms::Label^ repo_ownername;
private: System::Windows::Forms::ListBox^ all_repo_commits_list;
private: System::Windows::Forms::ListBox^ all_repo_files_list;
private: System::Windows::Forms::Label^ label_c;
private: System::Windows::Forms::Label^ label_f;
private: System::Windows::Forms::Label^ view_username;
private: System::Windows::Forms::Button^ open_viewing_repo;

private: System::Windows::Forms::ListBox^ all_viewing_repo_list;
private: System::Windows::Forms::Button^ fork_viewing_repo;
private: System::Windows::Forms::Button^ view_following_btn;
private: System::Windows::Forms::TextBox^ reponame_input;
private: System::Windows::Forms::Label^ reponame;
private: System::Windows::Forms::GroupBox^ enter_reponame_gb;
private: System::Windows::Forms::Label^ edit_reponame;
private: System::Windows::Forms::Label^ edit_enter;
private: System::Windows::Forms::TextBox^ edit_filename_input;
private: System::Windows::Forms::Button^ edit_addfile_btn;
private: System::Windows::Forms::Button^ edit_removefile_btn;
private: System::Windows::Forms::Label^ edit_enter_cmit;
private: System::Windows::Forms::TextBox^ edit_cmit_input;
private: System::Windows::Forms::Label^ edit_repo_status;


































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
			this->login_register_btn = (gcnew System::Windows::Forms::Button());
			this->main_title = (gcnew System::Windows::Forms::Label());
			this->made_by_btn = (gcnew System::Windows::Forms::Button());
			this->quit_btn = (gcnew System::Windows::Forms::Button());
			this->main_menu = (gcnew System::Windows::Forms::GroupBox());
			this->GitHub_groupbox = (gcnew System::Windows::Forms::GroupBox());
			this->logout = (gcnew System::Windows::Forms::Button());
			this->TabControl = (gcnew System::Windows::Forms::TabControl());
			this->user = (gcnew System::Windows::Forms::TabPage());
			this->enter_reponame_gb = (gcnew System::Windows::Forms::GroupBox());
			this->reponame = (gcnew System::Windows::Forms::Label());
			this->reponame_input = (gcnew System::Windows::Forms::TextBox());
			this->create_new_repo_btn = (gcnew System::Windows::Forms::Button());
			this->view_repo_btn = (gcnew System::Windows::Forms::Button());
			this->edit_repo_btn = (gcnew System::Windows::Forms::Button());
			this->all_repo = (gcnew System::Windows::Forms::Label());
			this->all_user_repo_list = (gcnew System::Windows::Forms::ListBox());
			this->view = (gcnew System::Windows::Forms::TabPage());
			this->fork_viewing_repo = (gcnew System::Windows::Forms::Button());
			this->open_viewing_repo = (gcnew System::Windows::Forms::Button());
			this->all_viewing_repo_list = (gcnew System::Windows::Forms::ListBox());
			this->view_username = (gcnew System::Windows::Forms::Label());
			this->edit = (gcnew System::Windows::Forms::TabPage());
			this->edit_repo_status = (gcnew System::Windows::Forms::Label());
			this->edit_enter_cmit = (gcnew System::Windows::Forms::Label());
			this->edit_cmit_input = (gcnew System::Windows::Forms::TextBox());
			this->edit_removefile_btn = (gcnew System::Windows::Forms::Button());
			this->edit_enter = (gcnew System::Windows::Forms::Label());
			this->edit_filename_input = (gcnew System::Windows::Forms::TextBox());
			this->edit_addfile_btn = (gcnew System::Windows::Forms::Button());
			this->edit_reponame = (gcnew System::Windows::Forms::Label());
			this->files = (gcnew System::Windows::Forms::TabPage());
			this->label_c = (gcnew System::Windows::Forms::Label());
			this->label_f = (gcnew System::Windows::Forms::Label());
			this->all_repo_commits_list = (gcnew System::Windows::Forms::ListBox());
			this->all_repo_files_list = (gcnew System::Windows::Forms::ListBox());
			this->repo_reponame = (gcnew System::Windows::Forms::Label());
			this->repo_ownername = (gcnew System::Windows::Forms::Label());
			this->gh_username_title = (gcnew System::Windows::Forms::Label());
			this->gh_welcome = (gcnew System::Windows::Forms::Label());
			this->following_gb = (gcnew System::Windows::Forms::GroupBox());
			this->view_following_btn = (gcnew System::Windows::Forms::Button());
			this->all_following_list = (gcnew System::Windows::Forms::ListBox());
			this->unfollow_btn = (gcnew System::Windows::Forms::Button());
			this->show_users_btn = (gcnew System::Windows::Forms::Button());
			this->users_gb = (gcnew System::Windows::Forms::GroupBox());
			this->all_users_list = (gcnew System::Windows::Forms::ListBox());
			this->Follow_user_btn = (gcnew System::Windows::Forms::Button());
			this->view_usr_btn = (gcnew System::Windows::Forms::Button());
			this->show_following_btn = (gcnew System::Windows::Forms::Button());
			this->login_groupbox = (gcnew System::Windows::Forms::GroupBox());
			this->login_goback_btn = (gcnew System::Windows::Forms::Button());
			this->register_btn = (gcnew System::Windows::Forms::Button());
			this->login_user_btn = (gcnew System::Windows::Forms::Button());
			this->login_password_input = (gcnew System::Windows::Forms::TextBox());
			this->login_username_input = (gcnew System::Windows::Forms::TextBox());
			this->login_password = (gcnew System::Windows::Forms::Label());
			this->login_username = (gcnew System::Windows::Forms::Label());
			this->login_title = (gcnew System::Windows::Forms::Label());
			this->register_groupbox = (gcnew System::Windows::Forms::GroupBox());
			this->reg_password_input2 = (gcnew System::Windows::Forms::TextBox());
			this->reg_password2 = (gcnew System::Windows::Forms::Label());
			this->go_to_mainmenu = (gcnew System::Windows::Forms::Button());
			this->go_back_login_page = (gcnew System::Windows::Forms::Button());
			this->register_user_btn = (gcnew System::Windows::Forms::Button());
			this->reg_password_input = (gcnew System::Windows::Forms::TextBox());
			this->reg_username_input = (gcnew System::Windows::Forms::TextBox());
			this->reg_password = (gcnew System::Windows::Forms::Label());
			this->reg_username = (gcnew System::Windows::Forms::Label());
			this->register_title = (gcnew System::Windows::Forms::Label());
			this->main_menu->SuspendLayout();
			this->GitHub_groupbox->SuspendLayout();
			this->TabControl->SuspendLayout();
			this->user->SuspendLayout();
			this->enter_reponame_gb->SuspendLayout();
			this->view->SuspendLayout();
			this->edit->SuspendLayout();
			this->files->SuspendLayout();
			this->following_gb->SuspendLayout();
			this->users_gb->SuspendLayout();
			this->login_groupbox->SuspendLayout();
			this->register_groupbox->SuspendLayout();
			this->SuspendLayout();
			// 
			// login_register_btn
			// 
			this->login_register_btn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->login_register_btn->Location = System::Drawing::Point(275, 206);
			this->login_register_btn->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->login_register_btn->Name = L"login_register_btn";
			this->login_register_btn->Size = System::Drawing::Size(264, 53);
			this->login_register_btn->TabIndex = 0;
			this->login_register_btn->Text = L"Login / Register";
			this->login_register_btn->UseVisualStyleBackColor = true;
			this->login_register_btn->Click += gcnew System::EventHandler(this, &MyForm::login_register_btn_Click);
			// 
			// main_title
			// 
			this->main_title->AutoSize = true;
			this->main_title->BackColor = System::Drawing::Color::DimGray;
			this->main_title->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 22.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->main_title->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->main_title->Location = System::Drawing::Point(228, 43);
			this->main_title->Name = L"main_title";
			this->main_title->Size = System::Drawing::Size(357, 42);
			this->main_title->TabIndex = 1;
			this->main_title->Text = L"Welcome to GitHub";
			// 
			// made_by_btn
			// 
			this->made_by_btn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->made_by_btn->Location = System::Drawing::Point(324, 272);
			this->made_by_btn->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->made_by_btn->Name = L"made_by_btn";
			this->made_by_btn->Size = System::Drawing::Size(165, 50);
			this->made_by_btn->TabIndex = 2;
			this->made_by_btn->Text = L"Credits";
			this->made_by_btn->UseVisualStyleBackColor = true;
			// 
			// quit_btn
			// 
			this->quit_btn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->quit_btn->Location = System::Drawing::Point(337, 336);
			this->quit_btn->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->quit_btn->Name = L"quit_btn";
			this->quit_btn->Size = System::Drawing::Size(139, 50);
			this->quit_btn->TabIndex = 3;
			this->quit_btn->Text = L"Quit";
			this->quit_btn->UseVisualStyleBackColor = true;
			this->quit_btn->Click += gcnew System::EventHandler(this, &MyForm::quit_btn_Click);
			// 
			// main_menu
			// 
			this->main_menu->Controls->Add(this->main_title);
			this->main_menu->Controls->Add(this->login_register_btn);
			this->main_menu->Controls->Add(this->quit_btn);
			this->main_menu->Controls->Add(this->made_by_btn);
			this->main_menu->Location = System::Drawing::Point(10, 9);
			this->main_menu->Margin = System::Windows::Forms::Padding(0);
			this->main_menu->Name = L"main_menu";
			this->main_menu->Padding = System::Windows::Forms::Padding(0);
			this->main_menu->Size = System::Drawing::Size(813, 434);
			this->main_menu->TabIndex = 4;
			this->main_menu->TabStop = false;
			this->main_menu->Enter += gcnew System::EventHandler(this, &MyForm::main_menu_Enter);
			// 
			// GitHub_groupbox
			// 
			this->GitHub_groupbox->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->GitHub_groupbox->Controls->Add(this->logout);
			this->GitHub_groupbox->Controls->Add(this->TabControl);
			this->GitHub_groupbox->Controls->Add(this->gh_username_title);
			this->GitHub_groupbox->Controls->Add(this->gh_welcome);
			this->GitHub_groupbox->Controls->Add(this->following_gb);
			this->GitHub_groupbox->Controls->Add(this->users_gb);
			this->GitHub_groupbox->Location = System::Drawing::Point(10, 9);
			this->GitHub_groupbox->Margin = System::Windows::Forms::Padding(0);
			this->GitHub_groupbox->Name = L"GitHub_groupbox";
			this->GitHub_groupbox->Padding = System::Windows::Forms::Padding(0);
			this->GitHub_groupbox->Size = System::Drawing::Size(813, 434);
			this->GitHub_groupbox->TabIndex = 5;
			this->GitHub_groupbox->TabStop = false;
			// 
			// logout
			// 
			this->logout->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->logout->Location = System::Drawing::Point(697, 19);
			this->logout->Name = L"logout";
			this->logout->Size = System::Drawing::Size(100, 36);
			this->logout->TabIndex = 11;
			this->logout->Text = L"Logout";
			this->logout->UseVisualStyleBackColor = true;
			this->logout->Click += gcnew System::EventHandler(this, &MyForm::logout_Click);
			// 
			// TabControl
			// 
			this->TabControl->Controls->Add(this->user);
			this->TabControl->Controls->Add(this->view);
			this->TabControl->Controls->Add(this->edit);
			this->TabControl->Controls->Add(this->files);
			this->TabControl->Location = System::Drawing::Point(3, 105);
			this->TabControl->Name = L"TabControl";
			this->TabControl->SelectedIndex = 0;
			this->TabControl->Size = System::Drawing::Size(606, 325);
			this->TabControl->SizeMode = System::Windows::Forms::TabSizeMode::Fixed;
			this->TabControl->TabIndex = 10;
			// 
			// user
			// 
			this->user->Controls->Add(this->enter_reponame_gb);
			this->user->Controls->Add(this->create_new_repo_btn);
			this->user->Controls->Add(this->view_repo_btn);
			this->user->Controls->Add(this->edit_repo_btn);
			this->user->Controls->Add(this->all_repo);
			this->user->Controls->Add(this->all_user_repo_list);
			this->user->Location = System::Drawing::Point(4, 25);
			this->user->Name = L"user";
			this->user->Padding = System::Windows::Forms::Padding(3);
			this->user->Size = System::Drawing::Size(598, 296);
			this->user->TabIndex = 0;
			this->user->Text = L"User Page";
			this->user->UseVisualStyleBackColor = true;
			// 
			// enter_reponame_gb
			// 
			this->enter_reponame_gb->Controls->Add(this->reponame);
			this->enter_reponame_gb->Controls->Add(this->reponame_input);
			this->enter_reponame_gb->Location = System::Drawing::Point(434, 224);
			this->enter_reponame_gb->Name = L"enter_reponame_gb";
			this->enter_reponame_gb->Size = System::Drawing::Size(151, 59);
			this->enter_reponame_gb->TabIndex = 7;
			this->enter_reponame_gb->TabStop = false;
			// 
			// reponame
			// 
			this->reponame->AutoSize = true;
			this->reponame->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->reponame->Location = System::Drawing::Point(6, 10);
			this->reponame->Name = L"reponame";
			this->reponame->Size = System::Drawing::Size(103, 20);
			this->reponame->TabIndex = 6;
			this->reponame->Text = L"Enter Name:";
			// 
			// reponame_input
			// 
			this->reponame_input->BackColor = System::Drawing::Color::MidnightBlue;
			this->reponame_input->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->reponame_input->ForeColor = System::Drawing::SystemColors::InactiveBorder;
			this->reponame_input->Location = System::Drawing::Point(6, 30);
			this->reponame_input->Name = L"reponame_input";
			this->reponame_input->Size = System::Drawing::Size(132, 22);
			this->reponame_input->TabIndex = 5;
			// 
			// create_new_repo_btn
			// 
			this->create_new_repo_btn->BackColor = System::Drawing::Color::Silver;
			this->create_new_repo_btn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->create_new_repo_btn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->create_new_repo_btn->Location = System::Drawing::Point(441, 183);
			this->create_new_repo_btn->Margin = System::Windows::Forms::Padding(0);
			this->create_new_repo_btn->Name = L"create_new_repo_btn";
			this->create_new_repo_btn->Size = System::Drawing::Size(137, 39);
			this->create_new_repo_btn->TabIndex = 4;
			this->create_new_repo_btn->Text = L"Create";
			this->create_new_repo_btn->UseVisualStyleBackColor = false;
			this->create_new_repo_btn->Click += gcnew System::EventHandler(this, &MyForm::create_new_repo_btn_Click);
			// 
			// view_repo_btn
			// 
			this->view_repo_btn->BackColor = System::Drawing::Color::Silver;
			this->view_repo_btn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->view_repo_btn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->view_repo_btn->Location = System::Drawing::Point(20, 183);
			this->view_repo_btn->Margin = System::Windows::Forms::Padding(0);
			this->view_repo_btn->Name = L"view_repo_btn";
			this->view_repo_btn->Size = System::Drawing::Size(137, 39);
			this->view_repo_btn->TabIndex = 3;
			this->view_repo_btn->Text = L"Open";
			this->view_repo_btn->UseVisualStyleBackColor = false;
			this->view_repo_btn->Click += gcnew System::EventHandler(this, &MyForm::view_repo_btn_Click);
			// 
			// edit_repo_btn
			// 
			this->edit_repo_btn->BackColor = System::Drawing::Color::Silver;
			this->edit_repo_btn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->edit_repo_btn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->edit_repo_btn->Location = System::Drawing::Point(230, 183);
			this->edit_repo_btn->Margin = System::Windows::Forms::Padding(0);
			this->edit_repo_btn->Name = L"edit_repo_btn";
			this->edit_repo_btn->Size = System::Drawing::Size(137, 39);
			this->edit_repo_btn->TabIndex = 2;
			this->edit_repo_btn->Text = L"Edit";
			this->edit_repo_btn->UseVisualStyleBackColor = false;
			this->edit_repo_btn->Click += gcnew System::EventHandler(this, &MyForm::edit_repo_btn_Click);
			// 
			// all_repo
			// 
			this->all_repo->AutoSize = true;
			this->all_repo->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->all_repo->Location = System::Drawing::Point(20, 31);
			this->all_repo->Name = L"all_repo";
			this->all_repo->Size = System::Drawing::Size(206, 29);
			this->all_repo->TabIndex = 1;
			this->all_repo->Text = L"All Repositories:";
			// 
			// all_user_repo_list
			// 
			this->all_user_repo_list->FormattingEnabled = true;
			this->all_user_repo_list->ItemHeight = 16;
			this->all_user_repo_list->Location = System::Drawing::Point(20, 64);
			this->all_user_repo_list->Name = L"all_user_repo_list";
			this->all_user_repo_list->Size = System::Drawing::Size(557, 116);
			this->all_user_repo_list->TabIndex = 0;
			// 
			// view
			// 
			this->view->Controls->Add(this->fork_viewing_repo);
			this->view->Controls->Add(this->open_viewing_repo);
			this->view->Controls->Add(this->all_viewing_repo_list);
			this->view->Controls->Add(this->view_username);
			this->view->Location = System::Drawing::Point(4, 25);
			this->view->Name = L"view";
			this->view->Padding = System::Windows::Forms::Padding(3);
			this->view->Size = System::Drawing::Size(598, 296);
			this->view->TabIndex = 1;
			this->view->Text = L"View User";
			this->view->UseVisualStyleBackColor = true;
			// 
			// fork_viewing_repo
			// 
			this->fork_viewing_repo->BackColor = System::Drawing::Color::Silver;
			this->fork_viewing_repo->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->fork_viewing_repo->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->fork_viewing_repo->Location = System::Drawing::Point(231, 188);
			this->fork_viewing_repo->Margin = System::Windows::Forms::Padding(0);
			this->fork_viewing_repo->Name = L"fork_viewing_repo";
			this->fork_viewing_repo->Size = System::Drawing::Size(137, 39);
			this->fork_viewing_repo->TabIndex = 6;
			this->fork_viewing_repo->Text = L"Fork";
			this->fork_viewing_repo->UseVisualStyleBackColor = false;
			this->fork_viewing_repo->Click += gcnew System::EventHandler(this, &MyForm::fork_viewing_repo_Click);
			// 
			// open_viewing_repo
			// 
			this->open_viewing_repo->BackColor = System::Drawing::Color::Silver;
			this->open_viewing_repo->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->open_viewing_repo->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->open_viewing_repo->Location = System::Drawing::Point(21, 188);
			this->open_viewing_repo->Margin = System::Windows::Forms::Padding(0);
			this->open_viewing_repo->Name = L"open_viewing_repo";
			this->open_viewing_repo->Size = System::Drawing::Size(137, 39);
			this->open_viewing_repo->TabIndex = 5;
			this->open_viewing_repo->Text = L"Open";
			this->open_viewing_repo->UseVisualStyleBackColor = false;
			this->open_viewing_repo->Click += gcnew System::EventHandler(this, &MyForm::open_viewing_repo_Click);
			// 
			// all_viewing_repo_list
			// 
			this->all_viewing_repo_list->FormattingEnabled = true;
			this->all_viewing_repo_list->ItemHeight = 16;
			this->all_viewing_repo_list->Location = System::Drawing::Point(21, 69);
			this->all_viewing_repo_list->Name = L"all_viewing_repo_list";
			this->all_viewing_repo_list->Size = System::Drawing::Size(557, 116);
			this->all_viewing_repo_list->TabIndex = 4;
			// 
			// view_username
			// 
			this->view_username->AutoSize = true;
			this->view_username->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->view_username->Location = System::Drawing::Point(20, 24);
			this->view_username->Name = L"view_username";
			this->view_username->Size = System::Drawing::Size(111, 29);
			this->view_username->TabIndex = 0;
			this->view_username->Text = L"Viewing: ";
			// 
			// edit
			// 
			this->edit->Controls->Add(this->edit_repo_status);
			this->edit->Controls->Add(this->edit_enter_cmit);
			this->edit->Controls->Add(this->edit_cmit_input);
			this->edit->Controls->Add(this->edit_removefile_btn);
			this->edit->Controls->Add(this->edit_enter);
			this->edit->Controls->Add(this->edit_filename_input);
			this->edit->Controls->Add(this->edit_addfile_btn);
			this->edit->Controls->Add(this->edit_reponame);
			this->edit->Location = System::Drawing::Point(4, 25);
			this->edit->Name = L"edit";
			this->edit->Size = System::Drawing::Size(598, 296);
			this->edit->TabIndex = 2;
			this->edit->Text = L"Edit User";
			this->edit->UseVisualStyleBackColor = true;
			// 
			// edit_repo_status
			// 
			this->edit_repo_status->AutoSize = true;
			this->edit_repo_status->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->edit_repo_status->Location = System::Drawing::Point(499, 33);
			this->edit_repo_status->Name = L"edit_repo_status";
			this->edit_repo_status->Size = System::Drawing::Size(77, 20);
			this->edit_repo_status->TabIndex = 7;
			this->edit_repo_status->Text = L"<Status>";
			this->edit_repo_status->Click += gcnew System::EventHandler(this, &MyForm::edit_repo_status_Click);
			// 
			// edit_enter_cmit
			// 
			this->edit_enter_cmit->AutoSize = true;
			this->edit_enter_cmit->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->edit_enter_cmit->Location = System::Drawing::Point(52, 127);
			this->edit_enter_cmit->Name = L"edit_enter_cmit";
			this->edit_enter_cmit->Size = System::Drawing::Size(222, 25);
			this->edit_enter_cmit->TabIndex = 6;
			this->edit_enter_cmit->Text = L"Enter Commit Message:";
			// 
			// edit_cmit_input
			// 
			this->edit_cmit_input->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->edit_cmit_input->Location = System::Drawing::Point(57, 153);
			this->edit_cmit_input->Name = L"edit_cmit_input";
			this->edit_cmit_input->Size = System::Drawing::Size(432, 30);
			this->edit_cmit_input->TabIndex = 5;
			// 
			// edit_removefile_btn
			// 
			this->edit_removefile_btn->Location = System::Drawing::Point(286, 206);
			this->edit_removefile_btn->Name = L"edit_removefile_btn";
			this->edit_removefile_btn->Size = System::Drawing::Size(157, 43);
			this->edit_removefile_btn->TabIndex = 4;
			this->edit_removefile_btn->Text = L"Remove File";
			this->edit_removefile_btn->UseVisualStyleBackColor = true;
			this->edit_removefile_btn->Click += gcnew System::EventHandler(this, &MyForm::edit_removefile_btn_Click);
			// 
			// edit_enter
			// 
			this->edit_enter->AutoSize = true;
			this->edit_enter->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->edit_enter->Location = System::Drawing::Point(52, 84);
			this->edit_enter->Name = L"edit_enter";
			this->edit_enter->Size = System::Drawing::Size(143, 25);
			this->edit_enter->TabIndex = 3;
			this->edit_enter->Text = L"Enter Filename";
			// 
			// edit_filename_input
			// 
			this->edit_filename_input->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->edit_filename_input->Location = System::Drawing::Point(201, 81);
			this->edit_filename_input->Name = L"edit_filename_input";
			this->edit_filename_input->Size = System::Drawing::Size(281, 30);
			this->edit_filename_input->TabIndex = 2;
			// 
			// edit_addfile_btn
			// 
			this->edit_addfile_btn->Location = System::Drawing::Point(103, 206);
			this->edit_addfile_btn->Name = L"edit_addfile_btn";
			this->edit_addfile_btn->Size = System::Drawing::Size(157, 43);
			this->edit_addfile_btn->TabIndex = 1;
			this->edit_addfile_btn->Text = L"Add File";
			this->edit_addfile_btn->UseVisualStyleBackColor = true;
			this->edit_addfile_btn->Click += gcnew System::EventHandler(this, &MyForm::edit_addfile_btn_Click);
			// 
			// edit_reponame
			// 
			this->edit_reponame->AutoSize = true;
			this->edit_reponame->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->edit_reponame->Location = System::Drawing::Point(17, 24);
			this->edit_reponame->Name = L"edit_reponame";
			this->edit_reponame->Size = System::Drawing::Size(212, 29);
			this->edit_reponame->TabIndex = 0;
			this->edit_reponame->Text = L"Repository Name: ";
			// 
			// files
			// 
			this->files->Controls->Add(this->label_c);
			this->files->Controls->Add(this->label_f);
			this->files->Controls->Add(this->all_repo_commits_list);
			this->files->Controls->Add(this->all_repo_files_list);
			this->files->Controls->Add(this->repo_reponame);
			this->files->Controls->Add(this->repo_ownername);
			this->files->Location = System::Drawing::Point(4, 25);
			this->files->Name = L"files";
			this->files->Padding = System::Windows::Forms::Padding(3);
			this->files->Size = System::Drawing::Size(598, 296);
			this->files->TabIndex = 3;
			this->files->Text = L"Repository";
			this->files->UseVisualStyleBackColor = true;
			// 
			// label_c
			// 
			this->label_c->AutoSize = true;
			this->label_c->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label_c->Location = System::Drawing::Point(409, 62);
			this->label_c->Name = L"label_c";
			this->label_c->Size = System::Drawing::Size(79, 22);
			this->label_c->TabIndex = 5;
			this->label_c->Text = L"Commits";
			// 
			// label_f
			// 
			this->label_f->AutoSize = true;
			this->label_f->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label_f->Location = System::Drawing::Point(225, 62);
			this->label_f->Name = L"label_f";
			this->label_f->Size = System::Drawing::Size(48, 22);
			this->label_f->TabIndex = 4;
			this->label_f->Text = L"Files";
			// 
			// all_repo_commits_list
			// 
			this->all_repo_commits_list->FormattingEnabled = true;
			this->all_repo_commits_list->ItemHeight = 16;
			this->all_repo_commits_list->Location = System::Drawing::Point(413, 87);
			this->all_repo_commits_list->Name = L"all_repo_commits_list";
			this->all_repo_commits_list->SelectionMode = System::Windows::Forms::SelectionMode::None;
			this->all_repo_commits_list->Size = System::Drawing::Size(179, 196);
			this->all_repo_commits_list->TabIndex = 3;
			// 
			// all_repo_files_list
			// 
			this->all_repo_files_list->FormattingEnabled = true;
			this->all_repo_files_list->ItemHeight = 16;
			this->all_repo_files_list->Location = System::Drawing::Point(228, 87);
			this->all_repo_files_list->Name = L"all_repo_files_list";
			this->all_repo_files_list->SelectionMode = System::Windows::Forms::SelectionMode::None;
			this->all_repo_files_list->Size = System::Drawing::Size(179, 196);
			this->all_repo_files_list->TabIndex = 2;
			// 
			// repo_reponame
			// 
			this->repo_reponame->AutoSize = true;
			this->repo_reponame->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->repo_reponame->Location = System::Drawing::Point(17, 44);
			this->repo_reponame->Name = L"repo_reponame";
			this->repo_reponame->Size = System::Drawing::Size(79, 29);
			this->repo_reponame->TabIndex = 1;
			this->repo_reponame->Text = L"label1";
			// 
			// repo_ownername
			// 
			this->repo_ownername->AutoSize = true;
			this->repo_ownername->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->repo_ownername->Location = System::Drawing::Point(17, 15);
			this->repo_ownername->Name = L"repo_ownername";
			this->repo_ownername->Size = System::Drawing::Size(79, 29);
			this->repo_ownername->TabIndex = 0;
			this->repo_ownername->Text = L"label1";
			// 
			// gh_username_title
			// 
			this->gh_username_title->AutoSize = true;
			this->gh_username_title->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 22.2F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->gh_username_title->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->gh_username_title->Location = System::Drawing::Point(268, 55);
			this->gh_username_title->Name = L"gh_username_title";
			this->gh_username_title->Size = System::Drawing::Size(190, 42);
			this->gh_username_title->TabIndex = 1;
			this->gh_username_title->Text = L"Username";
			this->gh_username_title->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// gh_welcome
			// 
			this->gh_welcome->AutoSize = true;
			this->gh_welcome->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 22.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->gh_welcome->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->gh_welcome->Location = System::Drawing::Point(268, 13);
			this->gh_welcome->Name = L"gh_welcome";
			this->gh_welcome->Size = System::Drawing::Size(277, 42);
			this->gh_welcome->TabIndex = 0;
			this->gh_welcome->Text = L"Welcome Back,";
			this->gh_welcome->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// following_gb
			// 
			this->following_gb->Controls->Add(this->view_following_btn);
			this->following_gb->Controls->Add(this->all_following_list);
			this->following_gb->Controls->Add(this->unfollow_btn);
			this->following_gb->Controls->Add(this->show_users_btn);
			this->following_gb->Location = System::Drawing::Point(609, 121);
			this->following_gb->Name = L"following_gb";
			this->following_gb->Size = System::Drawing::Size(200, 310);
			this->following_gb->TabIndex = 5;
			this->following_gb->TabStop = false;
			// 
			// view_following_btn
			// 
			this->view_following_btn->BackColor = System::Drawing::Color::White;
			this->view_following_btn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->view_following_btn->Location = System::Drawing::Point(6, 277);
			this->view_following_btn->Name = L"view_following_btn";
			this->view_following_btn->Size = System::Drawing::Size(83, 27);
			this->view_following_btn->TabIndex = 9;
			this->view_following_btn->Text = L"View";
			this->view_following_btn->UseVisualStyleBackColor = false;
			this->view_following_btn->Click += gcnew System::EventHandler(this, &MyForm::view_following_btn_Click);
			// 
			// all_following_list
			// 
			this->all_following_list->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->all_following_list->ForeColor = System::Drawing::SystemColors::HotTrack;
			this->all_following_list->FormattingEnabled = true;
			this->all_following_list->ItemHeight = 16;
			this->all_following_list->Location = System::Drawing::Point(6, 59);
			this->all_following_list->Name = L"all_following_list";
			this->all_following_list->Size = System::Drawing::Size(188, 212);
			this->all_following_list->TabIndex = 4;
			this->all_following_list->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::all_following_list_SelectedIndexChanged);
			// 
			// unfollow_btn
			// 
			this->unfollow_btn->BackColor = System::Drawing::Color::White;
			this->unfollow_btn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->unfollow_btn->Location = System::Drawing::Point(111, 277);
			this->unfollow_btn->Name = L"unfollow_btn";
			this->unfollow_btn->Size = System::Drawing::Size(83, 27);
			this->unfollow_btn->TabIndex = 8;
			this->unfollow_btn->Text = L"Unfollow";
			this->unfollow_btn->UseVisualStyleBackColor = false;
			this->unfollow_btn->Click += gcnew System::EventHandler(this, &MyForm::unfollow_btn_Click);
			// 
			// show_users_btn
			// 
			this->show_users_btn->BackColor = System::Drawing::Color::White;
			this->show_users_btn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->show_users_btn->Location = System::Drawing::Point(6, 13);
			this->show_users_btn->Name = L"show_users_btn";
			this->show_users_btn->Size = System::Drawing::Size(188, 40);
			this->show_users_btn->TabIndex = 6;
			this->show_users_btn->Text = L"Show Users";
			this->show_users_btn->UseVisualStyleBackColor = false;
			this->show_users_btn->Click += gcnew System::EventHandler(this, &MyForm::show_users_btn_Click);
			// 
			// users_gb
			// 
			this->users_gb->Controls->Add(this->all_users_list);
			this->users_gb->Controls->Add(this->Follow_user_btn);
			this->users_gb->Controls->Add(this->view_usr_btn);
			this->users_gb->Controls->Add(this->show_following_btn);
			this->users_gb->Location = System::Drawing::Point(609, 121);
			this->users_gb->Name = L"users_gb";
			this->users_gb->Size = System::Drawing::Size(200, 310);
			this->users_gb->TabIndex = 9;
			this->users_gb->TabStop = false;
			// 
			// all_users_list
			// 
			this->all_users_list->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->all_users_list->ForeColor = System::Drawing::SystemColors::HotTrack;
			this->all_users_list->FormattingEnabled = true;
			this->all_users_list->ItemHeight = 16;
			this->all_users_list->Location = System::Drawing::Point(6, 59);
			this->all_users_list->Name = L"all_users_list";
			this->all_users_list->Size = System::Drawing::Size(188, 212);
			this->all_users_list->TabIndex = 4;
			// 
			// Follow_user_btn
			// 
			this->Follow_user_btn->BackColor = System::Drawing::Color::White;
			this->Follow_user_btn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->Follow_user_btn->Location = System::Drawing::Point(111, 277);
			this->Follow_user_btn->Name = L"Follow_user_btn";
			this->Follow_user_btn->Size = System::Drawing::Size(83, 27);
			this->Follow_user_btn->TabIndex = 8;
			this->Follow_user_btn->Text = L"Follow";
			this->Follow_user_btn->UseVisualStyleBackColor = false;
			this->Follow_user_btn->Click += gcnew System::EventHandler(this, &MyForm::Follow_user_btn_Click);
			// 
			// view_usr_btn
			// 
			this->view_usr_btn->BackColor = System::Drawing::Color::White;
			this->view_usr_btn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->view_usr_btn->Location = System::Drawing::Point(6, 277);
			this->view_usr_btn->Name = L"view_usr_btn";
			this->view_usr_btn->Size = System::Drawing::Size(83, 27);
			this->view_usr_btn->TabIndex = 7;
			this->view_usr_btn->Text = L"View";
			this->view_usr_btn->UseVisualStyleBackColor = false;
			this->view_usr_btn->Click += gcnew System::EventHandler(this, &MyForm::view_usr_btn_Click);
			// 
			// show_following_btn
			// 
			this->show_following_btn->BackColor = System::Drawing::Color::White;
			this->show_following_btn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->show_following_btn->Location = System::Drawing::Point(6, 13);
			this->show_following_btn->Name = L"show_following_btn";
			this->show_following_btn->Size = System::Drawing::Size(188, 40);
			this->show_following_btn->TabIndex = 6;
			this->show_following_btn->Text = L"Show Following";
			this->show_following_btn->UseVisualStyleBackColor = false;
			this->show_following_btn->Click += gcnew System::EventHandler(this, &MyForm::show_following_btn_Click);
			// 
			// login_groupbox
			// 
			this->login_groupbox->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->login_groupbox->Controls->Add(this->login_goback_btn);
			this->login_groupbox->Controls->Add(this->register_btn);
			this->login_groupbox->Controls->Add(this->login_user_btn);
			this->login_groupbox->Controls->Add(this->login_password_input);
			this->login_groupbox->Controls->Add(this->login_username_input);
			this->login_groupbox->Controls->Add(this->login_password);
			this->login_groupbox->Controls->Add(this->login_username);
			this->login_groupbox->Controls->Add(this->login_title);
			this->login_groupbox->Location = System::Drawing::Point(10, 9);
			this->login_groupbox->Margin = System::Windows::Forms::Padding(0);
			this->login_groupbox->Name = L"login_groupbox";
			this->login_groupbox->Padding = System::Windows::Forms::Padding(0);
			this->login_groupbox->Size = System::Drawing::Size(813, 434);
			this->login_groupbox->TabIndex = 5;
			this->login_groupbox->TabStop = false;
			// 
			// login_goback_btn
			// 
			this->login_goback_btn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->login_goback_btn->Location = System::Drawing::Point(319, 363);
			this->login_goback_btn->Margin = System::Windows::Forms::Padding(4);
			this->login_goback_btn->Name = L"login_goback_btn";
			this->login_goback_btn->Size = System::Drawing::Size(177, 41);
			this->login_goback_btn->TabIndex = 7;
			this->login_goback_btn->Text = L"Go Back";
			this->login_goback_btn->UseVisualStyleBackColor = true;
			this->login_goback_btn->Click += gcnew System::EventHandler(this, &MyForm::login_goback_btn_Click);
			// 
			// register_btn
			// 
			this->register_btn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->register_btn->Location = System::Drawing::Point(293, 321);
			this->register_btn->Margin = System::Windows::Forms::Padding(4);
			this->register_btn->Name = L"register_btn";
			this->register_btn->Size = System::Drawing::Size(227, 34);
			this->register_btn->TabIndex = 6;
			this->register_btn->Text = L"Register an Account";
			this->register_btn->UseVisualStyleBackColor = true;
			this->register_btn->Click += gcnew System::EventHandler(this, &MyForm::register_btn_Click);
			// 
			// login_user_btn
			// 
			this->login_user_btn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->login_user_btn->Location = System::Drawing::Point(312, 258);
			this->login_user_btn->Margin = System::Windows::Forms::Padding(4);
			this->login_user_btn->Name = L"login_user_btn";
			this->login_user_btn->Size = System::Drawing::Size(191, 55);
			this->login_user_btn->TabIndex = 5;
			this->login_user_btn->Text = L"Login";
			this->login_user_btn->UseVisualStyleBackColor = true;
			this->login_user_btn->Click += gcnew System::EventHandler(this, &MyForm::login_user_btn_Click);
			// 
			// login_password_input
			// 
			this->login_password_input->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->login_password_input->Location = System::Drawing::Point(327, 197);
			this->login_password_input->Margin = System::Windows::Forms::Padding(4);
			this->login_password_input->Name = L"login_password_input";
			this->login_password_input->Size = System::Drawing::Size(275, 30);
			this->login_password_input->TabIndex = 4;
			// 
			// login_username_input
			// 
			this->login_username_input->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->login_username_input->Location = System::Drawing::Point(327, 153);
			this->login_username_input->Margin = System::Windows::Forms::Padding(4);
			this->login_username_input->Name = L"login_username_input";
			this->login_username_input->Size = System::Drawing::Size(275, 30);
			this->login_username_input->TabIndex = 3;
			// 
			// login_password
			// 
			this->login_password->AutoSize = true;
			this->login_password->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->login_password->ForeColor = System::Drawing::SystemColors::Control;
			this->login_password->Location = System::Drawing::Point(179, 198);
			this->login_password->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->login_password->Name = L"login_password";
			this->login_password->Size = System::Drawing::Size(138, 29);
			this->login_password->TabIndex = 2;
			this->login_password->Text = L"Password : ";
			// 
			// login_username
			// 
			this->login_username->AutoSize = true;
			this->login_username->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->login_username->ForeColor = System::Drawing::SystemColors::Control;
			this->login_username->Location = System::Drawing::Point(179, 154);
			this->login_username->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->login_username->Name = L"login_username";
			this->login_username->Size = System::Drawing::Size(136, 29);
			this->login_username->TabIndex = 1;
			this->login_username->Text = L"Username: ";
			// 
			// login_title
			// 
			this->login_title->AutoSize = true;
			this->login_title->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 21.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->login_title->ForeColor = System::Drawing::SystemColors::Control;
			this->login_title->Location = System::Drawing::Point(293, 52);
			this->login_title->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->login_title->Name = L"login_title";
			this->login_title->Size = System::Drawing::Size(218, 42);
			this->login_title->TabIndex = 0;
			this->login_title->Text = L"Login Page";
			// 
			// register_groupbox
			// 
			this->register_groupbox->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->register_groupbox->Controls->Add(this->reg_password_input2);
			this->register_groupbox->Controls->Add(this->reg_password2);
			this->register_groupbox->Controls->Add(this->go_to_mainmenu);
			this->register_groupbox->Controls->Add(this->go_back_login_page);
			this->register_groupbox->Controls->Add(this->register_user_btn);
			this->register_groupbox->Controls->Add(this->reg_password_input);
			this->register_groupbox->Controls->Add(this->reg_username_input);
			this->register_groupbox->Controls->Add(this->reg_password);
			this->register_groupbox->Controls->Add(this->reg_username);
			this->register_groupbox->Controls->Add(this->register_title);
			this->register_groupbox->Location = System::Drawing::Point(10, 9);
			this->register_groupbox->Margin = System::Windows::Forms::Padding(0);
			this->register_groupbox->Name = L"register_groupbox";
			this->register_groupbox->Padding = System::Windows::Forms::Padding(0);
			this->register_groupbox->Size = System::Drawing::Size(813, 434);
			this->register_groupbox->TabIndex = 8;
			this->register_groupbox->TabStop = false;
			// 
			// reg_password_input2
			// 
			this->reg_password_input2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->reg_password_input2->Location = System::Drawing::Point(343, 201);
			this->reg_password_input2->Margin = System::Windows::Forms::Padding(4);
			this->reg_password_input2->Name = L"reg_password_input2";
			this->reg_password_input2->Size = System::Drawing::Size(275, 30);
			this->reg_password_input2->TabIndex = 4;
			// 
			// reg_password2
			// 
			this->reg_password2->AutoSize = true;
			this->reg_password2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->reg_password2->ForeColor = System::Drawing::SystemColors::Control;
			this->reg_password2->Location = System::Drawing::Point(195, 202);
			this->reg_password2->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->reg_password2->Name = L"reg_password2";
			this->reg_password2->Size = System::Drawing::Size(138, 29);
			this->reg_password2->TabIndex = 8;
			this->reg_password2->Text = L"Password : ";
			// 
			// go_to_mainmenu
			// 
			this->go_to_mainmenu->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->go_to_mainmenu->Location = System::Drawing::Point(318, 363);
			this->go_to_mainmenu->Margin = System::Windows::Forms::Padding(4);
			this->go_to_mainmenu->Name = L"go_to_mainmenu";
			this->go_to_mainmenu->Size = System::Drawing::Size(177, 41);
			this->go_to_mainmenu->TabIndex = 7;
			this->go_to_mainmenu->Text = L"Go Back";
			this->go_to_mainmenu->UseVisualStyleBackColor = true;
			this->go_to_mainmenu->Click += gcnew System::EventHandler(this, &MyForm::go_to_mainmenu_Click);
			// 
			// go_back_login_page
			// 
			this->go_back_login_page->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->go_back_login_page->Location = System::Drawing::Point(274, 321);
			this->go_back_login_page->Margin = System::Windows::Forms::Padding(4);
			this->go_back_login_page->Name = L"go_back_login_page";
			this->go_back_login_page->Size = System::Drawing::Size(265, 34);
			this->go_back_login_page->TabIndex = 6;
			this->go_back_login_page->Text = L"Login into an Account";
			this->go_back_login_page->UseVisualStyleBackColor = true;
			this->go_back_login_page->Click += gcnew System::EventHandler(this, &MyForm::go_back_login_page_Click);
			// 
			// register_user_btn
			// 
			this->register_user_btn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->register_user_btn->Location = System::Drawing::Point(311, 258);
			this->register_user_btn->Margin = System::Windows::Forms::Padding(4);
			this->register_user_btn->Name = L"register_user_btn";
			this->register_user_btn->Size = System::Drawing::Size(191, 55);
			this->register_user_btn->TabIndex = 5;
			this->register_user_btn->Text = L"Register Account";
			this->register_user_btn->UseVisualStyleBackColor = true;
			this->register_user_btn->Click += gcnew System::EventHandler(this, &MyForm::register_user_btn_Click);
			// 
			// reg_password_input
			// 
			this->reg_password_input->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->reg_password_input->Location = System::Drawing::Point(343, 161);
			this->reg_password_input->Margin = System::Windows::Forms::Padding(4);
			this->reg_password_input->Name = L"reg_password_input";
			this->reg_password_input->Size = System::Drawing::Size(275, 30);
			this->reg_password_input->TabIndex = 3;
			// 
			// reg_username_input
			// 
			this->reg_username_input->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->reg_username_input->Location = System::Drawing::Point(343, 121);
			this->reg_username_input->Margin = System::Windows::Forms::Padding(4);
			this->reg_username_input->Name = L"reg_username_input";
			this->reg_username_input->Size = System::Drawing::Size(275, 30);
			this->reg_username_input->TabIndex = 2;
			// 
			// reg_password
			// 
			this->reg_password->AutoSize = true;
			this->reg_password->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->reg_password->ForeColor = System::Drawing::SystemColors::Control;
			this->reg_password->Location = System::Drawing::Point(195, 162);
			this->reg_password->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->reg_password->Name = L"reg_password";
			this->reg_password->Size = System::Drawing::Size(138, 29);
			this->reg_password->TabIndex = 2;
			this->reg_password->Text = L"Password : ";
			// 
			// reg_username
			// 
			this->reg_username->AutoSize = true;
			this->reg_username->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->reg_username->ForeColor = System::Drawing::SystemColors::Control;
			this->reg_username->Location = System::Drawing::Point(195, 122);
			this->reg_username->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->reg_username->Name = L"reg_username";
			this->reg_username->Size = System::Drawing::Size(136, 29);
			this->reg_username->TabIndex = 1;
			this->reg_username->Text = L"Username: ";
			// 
			// register_title
			// 
			this->register_title->AutoSize = true;
			this->register_title->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 21.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->register_title->ForeColor = System::Drawing::SystemColors::Control;
			this->register_title->Location = System::Drawing::Point(229, 52);
			this->register_title->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->register_title->Name = L"register_title";
			this->register_title->Size = System::Drawing::Size(354, 42);
			this->register_title->TabIndex = 0;
			this->register_title->Text = L"Registeration Page";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::Black;
			this->ClientSize = System::Drawing::Size(832, 453);
			this->Controls->Add(this->GitHub_groupbox);
			this->Controls->Add(this->main_menu);
			this->Controls->Add(this->login_groupbox);
			this->Controls->Add(this->register_groupbox);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->Name = L"MyForm";
			this->Text = L"GitHib";
			this->main_menu->ResumeLayout(false);
			this->main_menu->PerformLayout();
			this->GitHub_groupbox->ResumeLayout(false);
			this->GitHub_groupbox->PerformLayout();
			this->TabControl->ResumeLayout(false);
			this->user->ResumeLayout(false);
			this->user->PerformLayout();
			this->enter_reponame_gb->ResumeLayout(false);
			this->enter_reponame_gb->PerformLayout();
			this->view->ResumeLayout(false);
			this->view->PerformLayout();
			this->edit->ResumeLayout(false);
			this->edit->PerformLayout();
			this->files->ResumeLayout(false);
			this->files->PerformLayout();
			this->following_gb->ResumeLayout(false);
			this->users_gb->ResumeLayout(false);
			this->login_groupbox->ResumeLayout(false);
			this->login_groupbox->PerformLayout();
			this->register_groupbox->ResumeLayout(false);
			this->register_groupbox->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void main_menu_Enter(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void quit_btn_Click(System::Object^ sender, System::EventArgs^ e) {
		Close();
	}
	private: System::Void login_register_btn_Click(System::Object^ sender, System::EventArgs^ e) {
		main_menu->Hide();
		login_groupbox->Show();
	}
	private: System::Void login_goback_btn_Click(System::Object^ sender, System::EventArgs^ e) {
		main_menu->Show();
		login_groupbox->Hide();
	}
	private: System::Void login_user_btn_Click(System::Object^ sender, System::EventArgs^ e) {
		string username = ToCustomString(login_username_input->Text);
		string password = ToCustomString(login_password_input->Text);

		MessageBox::Show("Logged In As: " + login_username_input->Text);
		if (UsersPasswords.CheckUserPass({ username, password })) {
			//Login Event
			login_groupbox->Hide();
			GitHub_groupbox->Show();

			CurrentUserName = username;
			CurrentUserIndex = followers.FindUser(username);

			gh_username_title->Text = ToCustomString(username);

			// Update User Repo List
			UpdateUserRepoList();

			enter_reponame_gb->Hide();
			show_create_repo_input = false;

			vector<string> users = followers.getUserList();
			all_users_list->Items->Clear();
			for (int i = 0; i < users.size(); i++) {
				string str = users[i];
				String^ usr = ToCustomString(str);
				all_users_list->Items->Add(usr);
			}
			
			all_following_list->Items->Clear();
			vector<string> fol = followers.getFollowingList(username);
			for (int i = 0; i < fol.size(); i++) {
				all_following_list->Items->Add(ToCustomString(fol[i]));
			}
		}
		else {
			MessageBox::Show("Wrong Username or Password.");
		}
	}
	private: System::Void register_btn_Click(System::Object^ sender, System::EventArgs^ e) {
		register_groupbox->Show();
		login_groupbox->Hide();

	}
	private: System::Void go_to_mainmenu_Click(System::Object^ sender, System::EventArgs^ e) {
		register_groupbox->Hide();
		main_menu->Show();
	}
	private: System::Void go_back_login_page_Click(System::Object^ sender, System::EventArgs^ e) {
		register_groupbox->Hide();
		login_groupbox->Show();
	}
	private: System::Void register_user_btn_Click(System::Object^ sender, System::EventArgs^ e) {
		string username = ToCustomString(reg_username_input->Text);
		string password = ToCustomString(reg_password_input->Text);
		string password2 = ToCustomString(reg_password_input2->Text);

		if (username == "") {
			MessageBox::Show("Error: Username cannot be Empty!");
			return;
		}
		if (password != password2) {
			MessageBox::Show("Error: Passwords do not Match!");
			return;
		}

		//Register User
		UserStruct user(username, password);
		if (!UsersPasswords.AddNewUser(user)) {
			MessageBox::Show("Invalid Username Or User already registered");
			return;
		}
		followers.NewUserRegister(username);
		if (!GitHubManager::RegisterUser(username)) {
			MessageBox::Show("Invalid Username Or User already registered");
			return;
		}
		UsersPasswords.SaveData();
		followers.SaveData();
		GitHubManager::SaveAllData(github_main);
		GitHubManager::LoadAllData(github_main);
		MessageBox::Show("User Registered Successfully!");
	}
	private: System::Void show_following_btn_Click(System::Object^ sender, System::EventArgs^ e) {
		users_gb->Hide();
		following_gb->Show();
	}
	private: System::Void show_users_btn_Click(System::Object^ sender, System::EventArgs^ e) {
		users_gb->Show();
		following_gb->Hide();
	}
	private: System::Void Follow_user_btn_Click(System::Object^ sender, System::EventArgs^ e) {
		if (all_users_list->SelectedIndex < 0) { return; }
		string SelUser = ToCustomString(all_users_list->SelectedItem->ToString());

		followers.FollowUser(CurrentUserName, SelUser);
		//Update Following List.
		all_following_list->Items->Clear();
		vector<string> fol = followers.getFollowingList(CurrentUserName);
		for (int i = 0; i < fol.size(); i++) {
			all_following_list->Items->Add(ToCustomString(fol[i]));
		}
		followers.SaveData();
		followers.LoadData();
	}
	private: System::Void logout_Click(System::Object^ sender, System::EventArgs^ e) {
		GitHub_groupbox->Hide();
		login_groupbox->Show();

		CurrentUserName = "";
		CurrentUserIndex = -1;
	}
	private: System::Void view_usr_btn_Click(System::Object^ sender, System::EventArgs^ e) {
		if (all_users_list->SelectedIndex < 0) { return; }

		string SelUser = ToCustomString(all_users_list->SelectedItem->ToString());

		ViewingUserName = SelUser;
		ViewingUserIndex = followers.FindUser(ViewingUserName);
		//Update View
		UpdateViewing();
	}
	private: System::Void view_following_btn_Click(System::Object^ sender, System::EventArgs^ e) {
		if (all_following_list->SelectedIndex < 0) { return; }

		string SelUser = ToCustomString(all_following_list->SelectedItem->ToString());

		ViewingUserName = SelUser;
		ViewingUserIndex = followers.FindUser(ViewingUserName);
		//Update View
		UpdateViewing();
	}
	private: System::Void edit_repo_btn_Click(System::Object^ sender, System::EventArgs^ e) {
		if (all_user_repo_list->SelectedIndex < 0) { return; }

		string reponame = ToCustomString(all_user_repo_list->SelectedItem->ToString());

		RepositoryEdit = github_main[CurrentUserIndex].GetRepo(reponame);
		edit_reponame->Text = "Repository Name: " + ToCustomString(RepositoryEdit->Repository_Name);
		if (RepositoryEdit->isPrivate) {
			edit_repo_status->Text = "Private";
		}
		else {
			edit_repo_status->Text = "Public";
		}
		TabControl->SelectTab("edit");
	}
	private: System::Void view_repo_btn_Click(System::Object^ sender, System::EventArgs^ e) {
		//View Own Repo
		if (all_user_repo_list->SelectedIndex < 0) { return; }

		string reponame = ToCustomString(all_user_repo_list->SelectedItem->ToString());

		RepositoryView = github_main[CurrentUserIndex].GetRepo(reponame);
		//Update Repository Files View
		UpdateRepositoryView(CurrentUserName);
	}
	private: System::Void open_viewing_repo_Click(System::Object^ sender, System::EventArgs^ e) {
		//View Others'
		if (all_viewing_repo_list->SelectedIndex < 0) { return; }

		string reponame = ToCustomString(all_viewing_repo_list->SelectedItem->ToString());

		RepositoryView = github_main[ViewingUserIndex].GetRepo(reponame);
		if (RepositoryView->isPrivate) 
		{ MessageBox::Show("Cannot View, Repository is set to Private."); return; }
		UpdateRepositoryView(ViewingUserName);
	}
	private: System::Void create_new_repo_btn_Click(System::Object^ sender, System::EventArgs^ e) {
		if (show_create_repo_input) {
			//Create Repo

			string reponame = ToCustomString(reponame_input->Text);
			github_main[CurrentUserIndex].CreateANewRepo(reponame);

			GitHubManager::SaveAllData(github_main);
			GitHubManager::LoadAllData(github_main);

			enter_reponame_gb->Hide();
			show_create_repo_input = false;

			UpdateUserRepoList();
		}
		else {
			//Show Input
			enter_reponame_gb->Show();
			show_create_repo_input = true;
		}
	}
	private: System::Void unfollow_btn_Click(System::Object^ sender, System::EventArgs^ e) {
		if (all_following_list->SelectedIndex < 0) { return; }
		string SelUser = ToCustomString(all_following_list->SelectedItem->ToString());

		followers.UnFollowUser(CurrentUserName, SelUser);
		//Update Following List.
		all_following_list->Items->Clear();
		vector<string> fol = followers.getFollowingList(CurrentUserName);
		for (int i = 0; i < fol.size(); i++) {
			all_following_list->Items->Add(ToCustomString(fol[i]));
		}
		followers.SaveData();
		followers.LoadData();
	}
	private: System::Void edit_addfile_btn_Click(System::Object^ sender, System::EventArgs^ e) {
		if (RepositoryEdit == nullptr) { return; }

		string filename = ToCustomString(edit_filename_input->Text);
		string cmmitmsg = ToCustomString(edit_cmit_input->Text);
		if (cmmitmsg == "") {
			cmmitmsg = filename + " was added.";
		}

		github_main[CurrentUserIndex].InsertFileInRepo(RepositoryEdit->Repository_Name, filename);
		github_main[CurrentUserIndex].Add_Commit_Msg(RepositoryEdit->Repository_Name, cmmitmsg);
		GitHubManager::SaveAllData(github_main);
	}
	private: System::Void edit_removefile_btn_Click(System::Object^ sender, System::EventArgs^ e) {
		if (RepositoryEdit == nullptr) { return; }

		string filename = ToCustomString(edit_filename_input->Text);
		string cmmitmsg = ToCustomString(edit_cmit_input->Text);

		github_main[CurrentUserIndex].DeleteFileFromRepo(RepositoryEdit->Repository_Name, filename, cmmitmsg);
		GitHubManager::SaveAllData(github_main);
	}
	private: System::Void edit_repo_status_Click(System::Object^ sender, System::EventArgs^ e) {
		if (RepositoryEdit == nullptr) { return; }

		if (edit_repo_status->Text == "Private") {
			RepositoryEdit->isPrivate = false;
			edit_repo_status->Text = "Public";
		}
		else if (edit_repo_status->Text == "Public") {
			RepositoryEdit->isPrivate = true;
			edit_repo_status->Text = "Private";
		}

		GitHubManager::SaveAllData(github_main);
	}
	private: System::Void fork_viewing_repo_Click(System::Object^ sender, System::EventArgs^ e) {
		if (CurrentUserIndex == -1) { return; }
		if (ViewingUserIndex == -1) { return; }
		if (all_viewing_repo_list->SelectedIndex < 0) { return; }

		String^ reponame = all_viewing_repo_list->SelectedItem->ToString();
		string repo = ToCustomString(reponame);

		bool foked = github_main[ViewingUserIndex].ForkARepository(repo, github_main[CurrentUserIndex]);
		if (!foked) {
			MessageBox::Show("Forked Failed, Make sure the Repository\nIs not a set to Private.");
		}
		else {
			GitHubManager::SaveAllData(github_main);
			GitHubManager::LoadAllData(github_main);

			UpdateUserRepoList();
			MessageBox::Show("Copied Repository: " + reponame);
		}
	}
private: System::Void all_following_list_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
}
};
}
