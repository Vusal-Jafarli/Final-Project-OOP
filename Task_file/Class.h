#pragma once

class Question
{
	string _question;
	string _answer_1;
	string _answer_2;
	string _answer_3;
	string _true_answer;
	string _user_choice = "";

public:
	Question(string question, string answer1, string answer2, string answer3, string true_answer)
	{
		set_question(question);
		set_answer1(answer1);
		set_answer2(answer2);
		set_answer3(answer3);
		set_true_answer(true_answer);
		//_user_choice = "";
	}

	Question(const Question& other)
	{
		this->_question = other._question;
		this->_answer_1 = other._answer_1;
		this->_answer_2 = other._answer_2;
		this->_answer_3 = other._answer_3;
		this->_true_answer = other._true_answer;
	}

	void set_question(string question)
	{
		if (question.size() > 0)
		{
			_question = question;
		}
		else
			cout << "ERROR SET QUESTION ";
	}
	void set_answer1(string answer1)
	{
		if (answer1.size() > 0)
		{
			_answer_1 = answer1;
		}
		else
			cout << "ERROR answer1 ";
	}
	void set_answer2(string answer2)
	{
		if (answer2.size() > 0)
		{
			_answer_2 = answer2;
		}
		else
			cout << "ERROR answer2 ";
	}
	void set_answer3(string answer3)
	{
		if (answer3.size() > 0)
		{
			_answer_3 = answer3;
		}
		else
			cout << "ERROR answer3 ";
	}
	void set_true_answer(string true_answer)
	{
		if (true_answer.size() > 0)
		{
			_true_answer = true_answer;
		}
		else
			cout << "ERROR true_answer ";
	}
	void set_user_choice(string choice)
	{
		if (choice.size() > 0)
		{
			_user_choice = choice;
		}
		else
			cout << "Error user choice ";
	}


	string get_question() { return _question; }
	string get_answer1() { return _answer_1; }
	string get_answer2() { return _answer_2; }
	string get_answer3() { return _answer_3; }
	string get_true_answer() { return _true_answer; }
	string user_choice() { return _user_choice; }

	void show()
	{
		cout << endl;
		cout << "             < " << _question << " >" << endl
			<< "A) " << _answer_1 << endl
			<< "B) " << _answer_2 << endl
			<< "C) " << _answer_3 << endl
			<< "D) " << _true_answer << endl;

	}

	string data()
	{
		string data = _question + "-" + _answer_1 + "-" + _answer_2 + "-" + _answer_3 + "-" + _true_answer;
		return data;
	}
};
class Quiz
{
	int static _static_id;
	int _id;
	string _name;
	string _type;
	Question** _questions;
	int _count;

public:
	Quiz(string name, Question** questions, int count)
	{
		_id = _static_id++;
		set_name(name);
		//set_type(type);
		_questions = questions;
		_count = count;
	}
	Quiz(string name)
	{
		_id = _static_id++;
		set_name(name);
		set_type("NULL");
		_questions = nullptr;
		_count = 0;
	}
	void set_name(string name)
	{
		if (name.size() > 0)
		{
			_name = name;
		}
		else
			cout << "ERROR name Quiz ";
	}
	void set_type(string type)
	{
		if (type.size() > 0)
		{
			_type = type;
		}
		else
			cout << "ERROR type Quiz ";
	}

	string get_name() { return _name; }
	string get_type() { return _type; }
	Question** data() { return _questions; }
	int size() { return _count; }


	void add(Question* question)
	{
		if (question == nullptr) { return; }

		Question** new_questions = new Question * [_count + 1] {};

		for (size_t i = 0; i < _count; i++)
			new_questions[i] = new Question(*_questions[i]);//COPY CONSTRUCTOR YAZ

		new_questions[_count] = new Question(*question);

		for (size_t i = 0; i < _count; i++)
			delete _questions[i];
		delete _questions;

		_questions = new_questions;
		_count++;
	}

	void show()
	{
		cout << endl;

		HANDLE  console = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(console, 14);
		cout << "Quiz: " << _name << endl;
		SetConsoleTextAttribute(console, 7);
		for (size_t i = 0; i < _count; i++)
		{

			_questions[i]->show();
			cout << endl;
		}
	}

	void write()
	{
		for (size_t i = 0; i < _count; i++)
		{
			string quiz_location = "Quizzes/" + _name + ".txt";
			write_txt(_questions[i]->data(), quiz_location);
		}
	}

	void read(string source)
	{
		string quiz_name = "Quizzes/" + source + ".txt";
		ifstream file(quiz_name, ios::in);

		if (!file) new exception("File Movcud deyil");

		string question, true_answer, answer1, answer2, answer3;

		if (file.is_open())
		{

			while (!file.eof())
			{
				getline(file, question, '-');
				getline(file, answer1, '-');
				getline(file, answer2, '-');
				getline(file, answer3, '-');
				getline(file, true_answer, '\n');


				if (file.eof())
					break;
				add(new Question(question, answer1, answer2, answer3, true_answer));

			}


			file.close();
		}

	}

	~Quiz()
	{

		/*	if (_questions != nullptr)
			{
				for (size_t i = 0; i < _count; i++)
				{
					delete _questions[i];
				}
				delete[] _questions;
			}*/
	}
};
class Leader
{
public:

	string name;
	int xal;

	Leader(string name, int xal)
	{
		this->name = name;
		this->xal = xal;
	}


	void show()
	{
		cout << "      " << name << "    " << xal << char(4) << endl;
	}
};
int Quiz::_static_id = 1;