#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <string>
#include <map>
#include <fstream>
#include <list>
#include <algorithm>
#include <vector>
using namespace std;


void clear();
void write_txt(string text, string source);
void menu(string** arr, int size);
void print_for_question(int row, string arr[], int size, int sual_nomre, Quiz quiz);

#include "Class.h"

//Deyisenler ve arrayler
int size_all_quiz = 0;
string** quizler = nullptr;
string username;
string** sign = new string * [3]
{
	new string("Sign Up"),
		new string("Sign In"),
		new string("Exit")};
string** giris_menu = new string * [3]
{
	new string("Admin"),
		new string("User"),
		new string("Exit")};
string** menu_admin = new string * [4]
{
	new string("All Quizzes"),
		new string("New Quiz"),
		new string("Leader Board"),
		new string("Exit")};
string** menu_user = new string * [4]
{
	new string("All Quizzes"),
		new string("Start Quiz"),
		new string("Leader Board"),
		new string("Exit")};

//Funksiyalar
//Leader Boarddaki user-leri ballarina gore sort edir.
bool sorting(Leader& v1, Leader& v2)
{
	return v1.xal > v2.xal;
}
void write_txt(string text, string source) {
	ofstream file(source, ios::app);

	if (file.is_open()) {

		file << text << endl;
		file.close();

	}
	else {
		cout << "File did not open!" << endl;
	}
}
void leader_board_write()
{
	/*string data = user_name + "-" + to_string(duzgun_cavab_sayi);
	write_txt(data, "Leader Board.txt");*/

	string say, user_name_txt;
	int bal = 0;
	{
		fstream cleaning_file("Leader main.txt", ios::out);
		if (cleaning_file.is_open())
			cleaning_file.close();


		ifstream users("Users.txt", ios::in);
		ifstream file("Leader main.txt");

		if (!file) new exception("File Movcud deyil");

		system("cls");
		string username3;
		if (users.is_open())
		{
			while (!users.eof())
			{

				username3 = "";
				getline(users, username3, ' ');
				if (username3.compare("") == 0)
					break;
				bal = 0;
				ifstream file("Leader Board.txt", ios::in);
				while (!file.eof())
				{
					user_name_txt = "";
					getline(file, user_name_txt, '-');

					if (user_name_txt.compare(username3) == 0)
					{
						getline(file, say, '\n');
						bal += stoi(say);//stoi funksiyasi - str to int  etmek ucundur.
					}
					else
						getline(file, user_name_txt, '\n');

					if (file.eof())
						break;

				}
				file.close();
				string main = username3 + "-" + to_string(bal);
				getline(users, username3, '\n');
				write_txt(main, "Leader main.txt");

				if (users.eof())
					break;
			}
		}

		users.close();
	}


}
void leader_board()
{
	vector<Leader> leaders;
	fstream file("Leader main.txt", ios::in);

	if (file.is_open())
	{
		while (!file.eof())
		{
			string name;
			string point;
			getline(file, name, '-');
			getline(file, point, '\n');

			if (point.compare("") == 0)
				break;

			int point_int = stoi(point);

			leaders.push_back(Leader(name, point_int));
		}

		cout << "     Leader Board" << endl;
		cout << endl;

		sort(leaders.begin(), leaders.end(), sorting);

		int count;
		(leaders.size() > 10) ? count = 10 : count = leaders.size();

		for (size_t i = 0; i < count; i++) {
			HANDLE  console = GetStdHandle(STD_OUTPUT_HANDLE);
			if (i < 3) {
				SetConsoleTextAttribute(console, 14);
			}
			else
				SetConsoleTextAttribute(console, 7);

			cout << "   " << i + 1 << " " << leaders[i].name;
			for (size_t j = 0; j < 12 - leaders[i].name.length(); j++)
			{
				cout << " ";

			}
			cout << leaders[i].xal << endl;
		}

		file.close();
	}
}
string** all_quiz()
{
	system("cls");
	bool empty_quiz = false;

	fstream file("All Quizzes.txt", ios::in);

	if (!file) new exception("File Movcud deyil");

	string question, true_answer, answer1, answer2, answer3;

	if (!file.is_open())
	{
		cout << "File did not open." << endl;

	}

	string** quizler = new string * [100] {};
	int index = 0;

	while (!file.eof())
	{
		{
			string quiz_name;
			getline(file, quiz_name, '\n');

			if ((quiz_name).compare("") == 0)
				break;

			quizler[index++] = new string(quiz_name);
		}
	}

	size_all_quiz = index;

	return quizler;
}
void start_quiz_main(string quiz)
{

	int duzgun_cavab = 0;
	system("cls");
	Quiz new_quiz(quiz);
	new_quiz.read(quiz);

	int i = 0;
	string sual_arr[8];
next:

	//if (sual_arr != nullptr)
	//{
	//	for (size_t i = 0; i < 8; i++)
	//	{
	//		delete sual_arr[i];
	//	}
	//}


	list<string> variantlar;

	variantlar.push_back((new_quiz.data()[i]->get_true_answer()));
	variantlar.push_back((new_quiz.data()[i]->get_answer1()));
	variantlar.push_back((new_quiz.data()[i]->get_answer2()));
	variantlar.push_back((new_quiz.data()[i]->get_answer3()));


	sual_arr[0] = new_quiz.data()[i]->get_question();
	{
		srand(time(NULL));
		int randi = 1 + rand() % 4;
		if (randi == 1)
		{
			sual_arr[4] = variantlar.front(); variantlar.pop_front();
			sual_arr[2] = variantlar.front(); variantlar.pop_front();
			sual_arr[1] = variantlar.front(); variantlar.pop_front();
			sual_arr[3] = variantlar.front(); variantlar.pop_front();
		}
		else if (randi == 2)
		{
			sual_arr[3] = variantlar.front(); variantlar.pop_front();
			sual_arr[1] = variantlar.front(); variantlar.pop_front();
			sual_arr[4] = variantlar.front(); variantlar.pop_front();
			sual_arr[2] = variantlar.front(); variantlar.pop_front();
		}
		else if (randi == 3)
		{
			sual_arr[2] = variantlar.front(); variantlar.pop_front();
			sual_arr[3] = variantlar.front(); variantlar.pop_front();
			sual_arr[1] = variantlar.front(); variantlar.pop_front();
			sual_arr[4] = variantlar.front(); variantlar.pop_front();
		}
		else if (randi == 4)
		{
			sual_arr[1] = variantlar.front(); variantlar.pop_front();
			sual_arr[4] = variantlar.front(); variantlar.pop_front();
			sual_arr[3] = variantlar.front(); variantlar.pop_front();
			sual_arr[2] = variantlar.front(); variantlar.pop_front();
		}
	}
	sual_arr[5] = string("Previous");
	sual_arr[6] = string("Next");
	sual_arr[7] = string("Finish");

	int row = 1;
	int size_variant = 8;
	while (true)
	{

		system("cls");
		print_for_question(row, sual_arr, size_variant, i, new_quiz);

		int temp = _getch();


		if (temp == 224)
		{
			temp = _getch();

			if (temp == 72)//up
			{
				if (row == 1)
					row = size_variant - 1;
				else
					row--;

			}
			else if (temp == 80)//down
			{
				if (row == size_variant - 1)
					row = 1;
				else
					row++;
			}

		}

		else if (temp == 13)
		{//ENTER
			if (row == 5) {
				if (i == 0)
					i = new_quiz.size() - 1;
				else
					i--;
				goto next;
			}
			else if (row == 6) {
				if (i == new_quiz.size() - 1)
					i = 0;
				else
					i++;
				goto next;
			}
			else if (row == 7)
			{
				system("cls");
				for (size_t i = 0; i < new_quiz.size(); i++)
				{
					if (new_quiz.data()[i]->user_choice().compare(new_quiz.data()[i]->get_true_answer()) == 0)
						duzgun_cavab++;
				}

				cout << "Duzgun cavab: " << duzgun_cavab << endl;
				cout << "Sehv cavab: " << new_quiz.size() - duzgun_cavab << endl;

				string data = username + "-" + to_string(duzgun_cavab);
				write_txt(data, "Leader Board.txt");

				system("pause");
				return;
			}
			else//Variant A,B,C,D
			{

				new_quiz.data()[i]->set_user_choice(sual_arr[row]);

				if (i == new_quiz.size() - 1)
				{
					for (size_t i = 0; i < new_quiz.size(); i++)
					{
						if (new_quiz.data()[i]->user_choice().compare(new_quiz.data()[i]->get_true_answer()) == 0)
							duzgun_cavab++;
					}
					system("cls");
					cout << "Duzgun cavab: " << duzgun_cavab << endl;
					cout << "Sehv cavab: " << new_quiz.size() - duzgun_cavab << endl;

					string data = username + "-" + to_string(duzgun_cavab);
					write_txt(data, "leader board.txt");

					system("pause");
					return;
				}

				i++;
				goto next;
			}

		}
		/*else if (temp == 27) { exit(0); }*/
	}

}
bool check_data(string text, string source) {
	FILE* f;
	fopen_s(&f, source.c_str(), "r");

	if (f != nullptr) {


		int row = 0;
		int index = 0;
		char symbol;


		symbol = getc(f);
	start:
		while (symbol != EOF)
		{
			char* checking = new char[255] {};

			while (symbol != '\n') {
				checking[index++] = symbol;
				symbol = getc(f);

			}
			checking[index] = '\r';

			const char* a = text.c_str();

			if (strcmp(a, checking) == 0)
				return true;


			index = 0;
			symbol = getc(f);
			delete checking;
			goto start;
		}
		return false;
	}
	return false;
}
void print(int row, string** arr, int size) {
	cout << endl << endl << endl << endl;
	cout << endl << endl << endl << endl;
	for (size_t i = 0; i < size; i++)
	{

		cout << "\t\t\t\t\t\t\t\t\t";
		HANDLE  console = GetStdHandle(STD_OUTPUT_HANDLE);
		if (i == row)
			SetConsoleTextAttribute(console, 168);

		cout << *arr[i] << endl;

		SetConsoleTextAttribute(console, 7);
	}
}
void print_for_question(int row, string arr[], int size, int sual_nomre, Quiz quiz) {
	cout << endl << endl << endl << endl;
	cout << endl << endl << endl << endl;
	for (size_t i = 0; i < size; i++)
	{
		cout << "\t\t\t\t\t\t\t\t";
		if (i == 0)
			cout << sual_nomre + 1 << ")";
		if (i == 1)
			cout << "A)";
		if (i == 2)
			cout << "B)";
		if (i == 3)
			cout << "C)";
		if (i == 4)
			cout << "D)";

		HANDLE  console = GetStdHandle(STD_OUTPUT_HANDLE);

		if (arr[i].compare(quiz.data()[sual_nomre]->user_choice()) == 0)
			SetConsoleTextAttribute(console, 9);
		if (i == row)
			SetConsoleTextAttribute(console, 168);

		if (i == 0)
			cout << arr[i] << endl << endl;
		else
			cout << arr[i] << endl;
		if (i == 4)
			cout << endl;

		SetConsoleTextAttribute(console, 7);

	}
}
void admin()
{
menu_admin:
	//if (quizler != nullptr)
	//{
	//	for (size_t i = 0; i < size_all_quiz; i++)
	//	{
	//		if (quizler[i] != nullptr)
	//			delete[] quizler[i];
	//	}
	//	delete[] quizler;
	//}

	int row = 0;
	int size = 4;
	while (true)
	{



		system("cls");

		cout << endl << endl;
		cout << endl << endl;
		cout << "\t\t\t\t\t\t    $$$$$$\\  $$$$$$$\\  $$\\      $$\\ $$$$$$\\ $$\\   $$\\ " << endl
			<< "\t\t\t\t\t\t   $$  __$$\\ $$  __$$\\ $$$\\    $$$ |\\_$$  _|$$$\\  $$ |" << endl
			<< "\t\t\t\t\t\t   $$ /  $$ |$$ |  $$ |$$$$\\  $$$$ |  $$ |  $$$$\\ $$ |" << endl
			<< "\t\t\t\t\t\t   $$$$$$$$ |$$ |  $$ |$$\\$$\\$$ $$ |  $$ |  $$ $$\\$$ |" << endl
			<< "\t\t\t\t\t\t   $$  __$$ |$$ |  $$ |$$ \\$$$  $$ |  $$ |  $$ \\$$$$ |" << endl
			<< "\t\t\t\t\t\t   $$ |  $$ |$$ |  $$ |$$ |\\$  /$$ |  $$ |  $$ |\\$$$ |" << endl
			<< "\t\t\t\t\t\t   $$ |  $$ |$$$$$$$  |$$ | \\_/ $$ |$$$$$$\\ $$ | \\$$ |" << endl
			<< "\t\t\t\t\t\t   \\__|  \\__|\\_______/ \\__|     \\__|\\______|\\__|  \\__|";

		print(row, menu_admin, size);

		int temp = _getch();

		if (temp == 224)
		{
			temp = _getch();

			if (temp == 72)//up
			{
				if (row == 0)
					row = size - 1;
				else
					row--;

			}
			else if (temp == 80)//down
			{
				if (row == size - 1)
					row = 0;
				else
					row++;
			}
		}

		else if (temp == 13)
		{//ENTER

			if (row == 0)//All Quizzes
			{

				quizler = all_quiz();

				int row = 0;

				while (true)
				{
					system("cls");
					print(row, quizler, size_all_quiz);

					int temp = _getch();

					if (temp == 224)
					{
						temp = _getch();

						if (temp == 72)//up
						{
							if (row == 0)
								row = size_all_quiz - 1;
							else
								row--;

						}
						else if (temp == 80)//down
						{
							if (row == size_all_quiz - 1)
								row = 0;
							else
								row++;
						}
					}//Quizlerin hamisinin oldugu menyu
					else if (temp == 13)
					{
						system("cls");
						Quiz new_quiz(*quizler[row]);
						new_quiz.read(*quizler[row]);
						new_quiz.show();

						cout << "---------------------" << endl;
						system("pause");
					}
					else if (temp == 27)
					{
						goto menu_admin;
					}

				}
			}
			if (row == 1)//New Quiz
			{
				cin.ignore();
				system("cls");
				string quiz_name;
				cout << endl << "Quiz name daxil edin : "; getline(cin, quiz_name);
				system("cls");
				string sual, answer1, answer2, answer3, true_answer;

				Quiz new_quiz(quiz_name);

				write_txt(quiz_name, "All Quizzes.txt");//Quizin adini quizler txt file-a qeyd etmek ucun

				int count = 0;
				cout << "Quizdeki sual sayini daxil edin: "; cin >> count;
				for (size_t i = 0; i < count; i++)
				{

					cin.ignore();
					cout << "Question: "; getline(cin, sual);
					cout << "True answer: "; getline(cin, true_answer);
					cout << "Other answer: "; getline(cin, answer1);
					cout << "Other answer: "; getline(cin, answer2);
					cout << "Other answer: "; getline(cin, answer3);


					Question* new_question = new Question(sual, answer1, answer2, answer3, true_answer);
					new_quiz.add(new_question);
					system("cls");


				}

				new_quiz.write();//Oz daxilindeki question** daki butun questionlari txt file-a yazir.


				system("Color 2");

				cout << "Quiz elave edildi." << endl;
				system("Color 7");
				system("pause");
				goto menu_admin;

			}
			else if (row == 2)//Leader Bord
			{
				cout << "Leader Board:" << endl;
				leader_board_write();
				leader_board();
				system("pause");

			}
			else if (row == 3)//Exit
			{
				menu(giris_menu, 3);
			}
		}
		else if (temp == 27) { menu(giris_menu, 3); }
		else {}
	}


}
void user()
{
menu_user_1:
	int row = 0;
	int size = 4;
	while (true)
	{
		system("cls");
		cout << endl << endl;
		cout << "\t\t\t\t\t\t\t   $$\\  $$\\   $$$$$$\\  $$$$$$$$\\ $$$$$$$\\ " << endl
			<< "\t\t\t\t\t\t\t   $$ |  $$ |$$  __$$\\ $$  _____|$$  __$$\\ " << endl
			<< "\t\t\t\t\t\t\t   $$ |  $$ |$$ /  \\__|$$ |      $$ |  $$ |" << endl
			<< "\t\t\t\t\t\t\t   $$ |  $$ |\\$$$$$$\\  $$$$$\\    $$$$$$$  |" << endl
			<< "\t\t\t\t\t\t\t   $$ |  $$ | \\____$$\\ $$  __|   $$  __$$< " << endl
			<< "\t\t\t\t\t\t\t   $$ |  $$ |$$\\   $$ |$$ |      $$ |  $$ |" << endl
			<< "\t\t\t\t\t\t\t   \\$$$$$$  |\\$$$$$$  |$$$$$$$$\\ $$ |  $$ |" << endl
			<< "\t\t\t\t\t\t\t    \\______/  \\______/ \\________|\\__|  \\__|";

		print(row, menu_user, size);

		int temp = _getch();

		if (temp == 224)
		{
			temp = _getch();

			if (temp == 72)//up
			{
				if (row == 0)
					row = size - 1;
				else
					row--;

			}
			else if (temp == 80)//down
			{
				if (row == size - 1)
					row = 0;
				else
					row++;
			}
		}

		else if (temp == 13)
		{//ENTER
			//User -> ALL QUIZZES 
			if (row == 0)
			{
				string** quizler = all_quiz();
				int row = 0;

				while (true)
				{
					system("cls");
					print(row, quizler, size_all_quiz);

					int temp = _getch();

					if (temp == 224)
					{
						temp = _getch();

						if (temp == 72)//up
						{
							if (row == 0)
								row = size_all_quiz - 1;
							else
								row--;

						}
						else if (temp == 80)//down
						{
							if (row == size_all_quiz - 1)
								row = 0;
							else
								row++;
						}
					}//Quizlerin hamisinin oldugu menyu
					else if (temp == 13)
					{
						system("cls");
						Quiz new_quiz(*quizler[row]);

						new_quiz.read(*quizler[row]);

						new_quiz.show();

						cout << "---------------------" << endl;

						system("pause");
					}
					else if (temp == 27)
					{

						goto menu_user_1;
					}
				}
			}

			//User -> Start Quizz
			else if (row == 1)
			{
				string** quizler = all_quiz();
				int row = 0;

				while (true)
				{
					system("cls");
					print(row, quizler, size_all_quiz);

					int temp = _getch();

					if (temp == 224)
					{
						temp = _getch();

						if (temp == 72)//up
						{
							if (row == 0)
								row = size_all_quiz - 1;
							else
								row--;

						}
						else if (temp == 80)//down
						{
							if (row == size_all_quiz - 1)
								row = 0;
							else
								row++;
						}
					}//Quizlerin hamisinin oldugu menyu
					else if (temp == 13)
					{
						start_quiz_main(*(quizler[row]));

					}
					else if (temp == 27)
					{
						user();
					}
				}

			}
			else if (row == 2)
			{
				cout << "Leader Board:" << endl;
				leader_board_write();
				leader_board();
				system("pause");

			}
			else if (row == 3)//Exit
			{
				menu(giris_menu, 3);
			}


		}

		else if (temp == 27) { menu(giris_menu, 3); }
		else {}
	}
}
void sign_in_up()
{
	int row = 0;
	int size = 3;
	while (true)
	{
		system("Color 7");
		system("cls");

		print(row, sign, size);

		int temp = _getch();

		if (temp == 224)
		{
			temp = _getch();

			if (temp == 72)//up
			{
				if (row == 0)
					row = size - 1;
				else
					row--;

			}
			else if (temp == 80)//down
			{
				if (row == size - 1)
					row = 0;
				else
					row++;
			}
		}

		else if (temp == 13) {//ENTER
			if (row == 0)//Sign UP
			{
			user:
				system("Color 7");
				string username, password;
				system("cls");
				cin.ignore();
				cout << "\t\t\t\t\t\t ---Qeydiyyat---" << endl << endl;
				cout << "\t\t\t\t\t\tUsername daxil edin: "; getline(cin, username);
				cout << "\t\t\t\t\t\tPassword daxil edin: "; getline(cin, password);

				system("cls");
				fstream file("Users.txt", ios::in);
				if (!file)
				{
					cout << "File acilmadi." << endl;
					return;
				}
				string username_check;
				if (file.is_open()) {
					while (!file.eof())
					{
						username_check = "";
						getline(file, username_check, ' ');

						if (username_check.compare(username) == 0) {
							system("Color 4");
							cout << "\t\t\t\t\t\tUsername movcuddur." << endl;
							system("pause");
							goto user;
						}
						getline(file, username_check, '\n');

						if (file.eof())
							break;
					}
					file.close();
				}
				string user_password = username + " " + password;
				write_txt(user_password, "Users.txt");
				system("Color 2");
				cout << "\t\t\t\t\t\tQeydiyyat ugurla tamamlandi." << endl;
				system("pause");
				system("Color 7");
			}
			else if (row == 1)//Sign IN
			{
				menu(giris_menu, 3);
			}
			else if (row == 2)
			{
				clear();
				exit(0);
			}
		}
		else {}
	}


}
void menu(string** arr, int size) {
menu:
	int row = 0;

	while (true)
	{
		system("Color 7");
		system("cls");
		cout << endl;

		cout << "\t\t\t\t\t\t\t    $$$$$$\\           $$\\				 " << endl
			<< "\t\t\t\t\t\t\t   $$  __$$\\          \\__|			 " << endl
			<< "\t\t\t\t\t\t\t   $$ /  $$ |$$\\  $$\\ $$\\ $$$$$$$$\\	 " << endl
			<< "\t\t\t\t\t\t\t   $$ |  $$ |$$ | $$ |$$ | \\____$$ |	 " << endl
			<< "\t\t\t\t\t\t\t   $$ |  $$ |$$ | $$ |$$ |   $$$$_/	 " << endl
			<< "\t\t\t\t\t\t\t   $$$$\\$$  |$$ | $$ |$$ |  $$ _/	 " << endl
			<< "\t\t\t\t\t\t\t   \\$$$$$$ / \\$$$$$$ |$$ | $$$$$$$$\\	 " << endl
			<< "\t\t\t\t\t\t\t   \\___$$$\\  \\______/ \\__|\\_________|" << endl
			<< "\t\t\t\t\t\t\t      \\___ |								 " << endl;


		print(row, arr, size);

		int temp = _getch();

		if (temp == 224)
		{
			temp = _getch();

			if (temp == 72)//up
			{
				if (row == 0)
					row = size - 1;
				else
					row--;

			}
			else if (temp == 80)//down
			{
				if (row == size - 1)
					row = 0;
				else
					row++;
			}
		}

		else if (temp == 13) {//ENTER
		first_part:
			if (row == 2) {//EXIT
				sign_in_up();


			}
			///////////////////////////
	/*		if (row == 0)
			{
				system("cls");
				admin();
			}
			else if (row == 1)
			{
				system("cls");
				user();
			}*/

			//Burdan asagi hisse username ve password ile daxil olmaq ucundur.
			//Lakin hal hazirda yuxaridaki if  else bu hisseni legv etmis veziyyetdedir.

			system("Color 7");
			system("cls");
			cout << "\t\t\t\t\t\t\t\t\t" << "Username: "; cin >> username;
			cout << "\t\t\t\t\t\t\t\t\t" << "Password: ";
			char password_chr[50]{};
			int index = 0;
			while (true)
			{
				temp = _getch();


				if (index < 48)
					password_chr[index++] = char(temp);

				cout << "*";
				if (temp == 13)//ENTER 
				{
					system("cls");
					string sign;
					sign = username + " " + string(password_chr);
					if (row == 0)
					{
						if (check_data(sign, "Admins.txt"))
						{
							system("cls");

							system("cls");
							admin();
							goto menu;
						}
						else
						{
							system("cls");
							system("Color 4");
							cout << "Parol yanlisdir." << endl;
							system("pause");
							goto menu;
						}

					}
					else if (row == 1)
					{
						if (check_data(sign, "Users.txt"))
						{
							system("cls");
							user();
							goto menu;
						}
						else
						{
							system("cls");
							system("Color 4");
							cout << "Parol yanlisdir." << endl;
							system("pause");
							goto menu;
						}
					}


				}
				else if (temp == 27)
				{
					goto menu;
				}

			}
			system("cls");

		}
		else if (temp == 27) {
			sign_in_up();
		}
	}


}
void clear()
{
	for (int i = 0; i < 3; ++i)
		delete giris_menu[i];
	delete[] giris_menu;

	for (int i = 0; i < 3; ++i)
		delete sign[i];
	delete[] sign;

	for (int i = 0; i < 3; ++i)
		delete menu_user[i];
	delete[] menu_user;

	for (int i = 0; i < 3; ++i)
		delete menu_admin[i];
	delete[] menu_admin;


}

int main()
{
	sign_in_up();
	return 0;

}

