#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

class CaloricInfo {
private:
	int calorii;

public:
	CaloricInfo() {};
	CaloricInfo(const int& calorii) : calorii(calorii) {};

	const int& getCalorii() const {
		return calorii;
	};

	void setCalorii(const int& newCalorii) {
		calorii = newCalorii;
	}

	virtual void displayInfo() const {
		cout << "Калорийность: " << calorii << endl;
	}

	~CaloricInfo() {};
};

template <typename T1, typename T2>
class Pair {
public:
	Pair() {}
	Pair(const T1& first, const T2& second) : first(first), second(second) {}

	void displayPair() const {
		std::cout << first << ": " << second << std::endl;
	}

	void savePairToFile(std::ofstream& outFile) const {
		outFile << first << " " << second << " ";
	}

private:
	T1 first;
	T2 second;
};

class MenuItem {
protected:
	string name;
	double price;
	string type;
	CaloricInfo caloricInfo;

public:
	MenuItem(const string& name, const double& price, const string& type) : name(name), price(price), type(type) {};

	virtual void displayInfo() const {
		cout << "Название блюда: " << name << endl;
		cout << "Стоимость: " << price << endl;
		cout << "Вид: " << type << endl;
	}

	void setTitle(const string& newTitle) {
		name = newTitle;
	}

	void setPrice(const double& newPrice) {
		price = newPrice;
	}

	void setType(const string& newType) {
		type = newType;
	}

	const double& getPrice() const {
		return price;
	}

	const string& getTitle() const {
		return name;
	}

	static bool compareByPrice(const MenuItem* bludo1, const MenuItem* bludo2) {
		return bludo1->getPrice() < bludo2->getPrice();
	}

	void saveToFile(ofstream& outFile) const {
		outFile << name << " | " << price << " | " << type << "\n";
	}

	virtual ~MenuItem() {};
};

class Appetizer : public MenuItem {
protected:
	string type_appet;

public:
	Appetizer(const string& name, const double& price, const string& type, const string& type_appet) : MenuItem(name, price, type), type_appet(type_appet) {};

	void displayInfo() const override {
		cout << "Название блюда: " << name << endl;
		cout << "Стоимость: " << price << endl;
		cout << "Вид: " << type << endl;
		cout << "Тип закуски: " << type_appet << endl;
	}

	~Appetizer() {};
};

class MainCourse : public MenuItem {
protected:
	int grammi;
public:
	MainCourse(const string& name, const double& price, const string& type, const int& grammi) : MenuItem(name, price, type), grammi(grammi) {};

	void displayInfo() const override {
		cout << "Название блюда: " << name << endl;
		cout << "Стоимость: " << price << endl;
		cout << "Вид: " << type << endl;
		cout << "Граммы: " << grammi << endl;
	}

	~MainCourse() {};
};

class Dessert : public MenuItem {
protected:
	int fat;
public:
	Dessert(const string& name, const double& price, const string& type, const int& fat) : MenuItem(name, price, type), fat(fat) {};

	void displayInfo() const override {
		cout << "Название блюда: " << name << endl;
		cout << "Стоимость: " << price << endl;
		cout << "Вид: " << type << endl;
		cout << "Жирность: " << fat << "%" << endl;
	}

	~Dessert() {};
};

void modifyBludo(MenuItem* bludo) {
	cout << "Блюдо найдено. Что Вы хотите изменить?" << endl;
	cout << "1) Название" << endl;
	cout << "2) Стоимость" << endl;
	cout << "3) Вид" << endl;

	int choice;
	cin >> choice;

	switch (choice)
	{

	case 1: {
		string newTitle;
		cout << "Введите новое название блюда: " << endl;
		cin >> newTitle;
		bludo->setTitle(newTitle);
		break;
	}
	case 2: {
		double newPrice;
		cout << "Введите новую стоимость блюда: " << endl;
		cin >> newPrice;
		bludo->setPrice(newPrice);
		break;
	}
	case 3: {
		string newType;
		cout << "Введите новый тип блюда: " << endl;
		cin >> newType;
		bludo->setType(newType);
		break;
	}
	}

}

void saveBludaToFile(const vector<MenuItem*>& bluda, const string& filename) {
	ofstream outFile(filename);
	outFile << "Название | " << "Стоимость | " <<
		"Вид" << "\n";
	for (const auto* bludo : bluda) {
		bludo->saveToFile(outFile);
	}
	outFile.close();
}

int main()
{
	system("chcp 1251 > nul");

	vector<MenuItem*> bluda;
	int choice;

	do {
		cout << "Опции:" << endl;
		cout << "1) Добавить блюдо" << endl;
		cout << "2) Поиск блюда" << endl;
		cout << "3) Сортировка блюд по цене" << endl;
		cout << "4) Вывести все блюда" << endl;
		cout << "5) Сохранить блюда в файл" << endl;
		cout << "6) Изменить блюдо" << endl;
		cout << "7) Выход" << endl;

		cout << "Введите ваш выбор: ";
		cin >> choice;

		switch (choice)
		{
			// Добавление нового блюда
		case 1: {
			system("cls");
			string name, type;
			double price;
			int bludo_choice;

			cout << "Введите название блюда: " << endl;
			cin >> name;
			cout << "Введите стоимость блюда: " << endl;
			cin >> price;

			cout << "Выберете вид блюда: " << endl;
			cout << "1) Обычное" << endl;
			cout << "2) Закуска" << endl;
			cout << "3) Основное" << endl;
			cout << "4) Десерт" << endl;
			cin >> bludo_choice;
			switch (bludo_choice)
			{
			case 1: {
				type = "Обычное";
				bluda.push_back(new MenuItem(name, price, type));
				break;
			}
			case 2: {
				type = "Закуска";
				string type_appet;
				cout << "Введите вид закуски (холодная или горячая)" << endl;
				cin >> type_appet;
				bluda.push_back(new Appetizer(name, price, type, type_appet));
				break;
			}
			case 3: {
				type = "Основное";
				int grammi;
				cout << "Введите граммы основного блюда:" << endl;
				cin >> grammi;
				bluda.push_back(new MainCourse(name, price, type, grammi));
				break;
			}
			case 4: {
				type = "Десерт";
				int fat;
				cout << "Введите жирность десерта:" << endl;
				cin >> fat;
				bluda.push_back(new Dessert(name, price, type, fat));
				break;
			}
			}
			break;
		}
			  // Поиск блюда
		case 2: {
			system("cls");
			string title;
			cout << "Введите название блюда, которое хотите найти: " << endl;
			cin >> title;
			auto it = find_if(bluda.begin(), bluda.end(), [&](const MenuItem* bludo) {
				return bludo->getTitle() == title;
				});

			if (it != bluda.end()) {
				(*it)->displayInfo();
			}
			else {
				cout << "Блюдо не найдено" << endl;
			}
			break;
		}
			  // Сортировка блюд по цене
		case 3: {
			sort(begin(bluda), end(bluda), MenuItem::compareByPrice);
			break;
		}
			  // Вывод всех блюд
		case 4: {
			system("cls");
			for (const auto i : bluda) {
				i->displayInfo();
				delete i;
			}
			break;
		}
			  // Сохранение блюд в файл
		case 5: {
			system("cls");
			string filename;
			cout << "Введите имя файла для сохранения: " << endl;
			cin >> filename;
			saveBludaToFile(bluda, filename);
			break;
		}
		case 6: {
			system("cls");
			string title;
			cout << "Введите данные блюда для изменения:" << endl;
			cin >> title;
			auto it = find_if(bluda.begin(), bluda.end(), [&](const MenuItem* bludo) {
				return bludo->getTitle() == title;
				});

			if (it != bluda.end()) {
				modifyBludo(*it);
			}
			else {
				std::cout << "Блюдо не найдено." << std::endl;
			}
			break;
		}
		case 7:
			break;
		}
	} while (choice != 7);
	bluda.erase(bluda.begin(), bluda.end());
	system("pause > nul");

	return 0;
}
