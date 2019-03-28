#include<iostream>
#include<iomanip>
#include<Windows.h>
#include<locale.h>
#include<ctime>
#include<fstream>

int buf_size = 0;

int cur_size = 0;

using namespace std;

struct Zapis
{
	int number : 31;

	char name[30];

	char surname[30];

	void print()
	{
		cout << number << " " << name << " " << surname << endl;
	}

	void printphones()
	{
		cout << number << endl;
	}

};

void sortbyname(Zapis *&fs) 
{

	for (size_t i = 0; i < cur_size; i++)
	{
		for (size_t j = 1; j < cur_size; j++)
		{

			if (strcmp(fs[j].name,fs[j - 1].name) == 1)
			{
				swap(fs[j], fs[j - 1]);
			}

		}

	}

}

void sortbysurname(Zapis *&fs)
{

	for (size_t i = 0; i < cur_size; i++)
	{
		for (size_t j = 1; j < cur_size; j++)
		{

			if (strcmp(fs[j].surname, fs[j - 1].surname) == 1)
			{
				swap(fs[j], fs[j - 1]);
			}

		}

	}

}

void sortbynumber(Zapis *&fs)
{


	for (size_t i = 0; i < cur_size; i++)
	{
		for (size_t j = 1; j < cur_size; j++)
		{
			if (fs[j].number > fs[j - 1].number)
			{
				swap(fs[j], fs[j - 1]);

			}
		}

	}

}

void add(Zapis*&fs, Zapis el)
{
	if (buf_size == 0)
	{
		buf_size = 4;
		fs = new Zapis[buf_size];
	}
	else
	{
		if (cur_size == buf_size)
		{
			buf_size *= 2;
			Zapis *tmp = new Zapis[buf_size];
			for (size_t i = 0; i < cur_size; i++)
			{
				tmp[i] = fs[i];
			}
			delete []fs;
			fs = tmp;
		}

	}
	fs[cur_size++] = el;

}

void change(Zapis *&el, int n)
{

	int flag =0;
	int tmp;
	char text[30];

	el[n - 1].print();

	cout << "1. Изменить номер" << endl << "2. Изменить имя"<< endl << "3. Изменить фамилию" << endl;
	cin >> flag;
	if (flag == 1)
	{
		cout << "Введите номер" << endl;
		cin >> tmp;
		el[n - 1].number = tmp;
	}
	if (flag == 2)
	{
		cout << "Введите имя" << endl;
		cin >> text;
		strcpy_s(el[n-1].name, text);
	}
	if (flag == 3)
	{
		cout << "Введите фамилию" << endl;
		cin >> text;
		strcpy_s(el[n - 1].surname, text);
	}
}

void Delete(Zapis *&el,char ch1[30])
{
	Zapis* tmp;

	tmp = new Zapis[cur_size--];

	int flag = 0;

	for (size_t i = 0; i < cur_size; i++)
	{
		if (!strcmp(ch1,el[i].name))
		{
			flag = 1;
		}
		if (flag == 0)
		{
			tmp[i] = el[i];
		}
		else
			tmp[i] = el[i + 1];


	}

	delete[] el;
	el = tmp;
}

void New(Zapis &fs)
{


	int tmpn;

	
	
	cout << "Введите номер" << endl;
	cin >> tmpn;
	fs.number = tmpn;

	cout << "Введите имя" << endl;
	cin >> fs.name;

	cout << "Введите фамилию" << endl;
	cin >> fs.surname;

}

int main()
{
	setlocale(LC_ALL, "");

	ifstream in_file("in.txt");

	Zapis el;

	int flag = 0;

	int n;

	int tmp;

	Zapis* zs = 0;

	while (!in_file.eof())
	{
		in_file >> tmp;
		el.number = tmp;

		in_file >> el.name;

		in_file >> el.surname;

		add(zs, el);
	}

	for (size_t i = 0; i < cur_size; i++)
	{
		zs[i].print();
	}

	int task;
	
	char ch1[30];

	int fl;

	do
	{
		cout << "1.Редактирование" << endl << "2.Удаление" << endl << "3.Добавление" << endl << "4.Сортировка" << endl;
		cin >> task;

		switch (task)
		{
		case 1:
			do
			{
				cout << "Введите номер записи для редактирования" << endl;
				cin >> n;

				change(zs, n);

				for (size_t i = 0; i < cur_size; i++)
				{
					zs[i].print();
				}
				cout << "Хотите продолжить?" << endl;
				cin >> flag;

			} while (flag != 0); break;
		case 2:

			cout << "Введите имя записи которую хотите удалить" << endl;
			cin >> ch1;
			Delete(zs, ch1);
			break;
		case 3:
			New(el);
			add(zs, el);
			break;
		case 4:
			int flags;
			cout << "1.Сортировка по имени" << endl << "2.Сортировка по фамилии" << endl << "3.Сортировка по номеру" << endl;
			cin >> flags;
			if (flags == 1)
			{
				sortbyname(zs);
			}
			else if (flags == 2)
			{
				sortbysurname(zs);
			}
			else if (flags == 3)
			{
				sortbynumber(zs);
			}break;
		}
		for (size_t i = 0; i < cur_size; i++)
		{
			zs[i].print();
		}

		cout << "Продолжить?" << endl;
		cin >> fl;



	} while (fl !=0);

	//Редактирование 



	//Добавление


	//Удаление

	cout << endl;






	system("pause");
	return 0;
}