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
		cout � "������������: " � calorii � endl;
	}

	~CaloricInfo() {};
};

template <typename T1, typename T2>
class Pair {
public:
	Pair() {}
	Pair(const T1& first, const T2& second) : first(first), second(second) {}

	void displayPair() const {
		std::cout � first � ": " � second � std::endl;
	}

	void savePairToFile(std::ofstream& outFile) const {
		outFile � first � " " � second � " ";
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
		cout � "�������� �����: " � name � endl;
		cout � "���������: " � price � endl;
		cout � "���: " � type � endl;
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
		outFile � name � " | " � price � " | " � type � "\n";
	}

	virtual ~MenuItem() {};
};

class Appetizer : public MenuItem {
protected:
	string type_appet;

public:
	Appetizer(const string& name, const double& price, const string& type, const string& type_appet) : MenuItem(name, price, type), type_appet(type_appet) {};

	void displayInfo() const override {
		cout � "�������� �����: " � name � endl;
		cout � "���������: " � price � endl;
		cout � "���: " � type � endl;
		cout � "��� �������: " � type_appet � endl;
	}

	~Appetizer() {};
};

class MainCourse : public MenuItem {
protected:
	int grammi;
public:
	MainCourse(const string& name, const double& price, const string& type, const int& grammi) : MenuItem(name, price, type), grammi(grammi) {};

	void displayInfo() const override {
		cout � "�������� �����: " � name � endl;
		cout � "���������: " � price � endl;
		cout � "���: " � type � endl;
		cout � "������: " � grammi � endl;
	}

	~MainCourse() {};
};

class Dessert : public MenuItem {
protected:
	int fat;
public:
	Dessert(const string& name, const double& price, const string& type, const int& fat) : MenuItem(name, price, type), fat(fat) {};

	void displayInfo() const override {
		cout � "�������� �����: " � name � endl;
		cout � "���������: " � price � endl;
		cout � "���: " � type � endl;
		cout � "��������: " � fat � "%" � endl;
	}

	~Dessert() {};
};

void modifyBludo(MenuItem* bludo) {
	cout � "����� �������. ��� �� ������ ��������?" � endl;
	cout � "1) ��������" � endl;
	cout � "2) ���������" � endl;
	cout � "3) ���" � endl;

	int choice;
	cin � choice;

	switch (choice)
	{
	case 1: {
		string newTitle;
		cout � "������� ����� �������� �����: " � endl;
		cin � newTitle;
		bludo->setTitle(newTitle);
		break;
	}
	case 2: {
		double newPrice;
		cout � "������� ����� ��������� �����: " � endl;
		cin � newPrice;
		bludo->setPrice(newPrice);
		break;
	}
	case 3: {
		string newType;
		cout � "������� ����� ��� �����: " � endl;
		cin � newType;
		bludo->setType(newType);
		break;
	}
	}

}

void saveBludaToFile(const vector<MenuItem*>& bluda, const string& filename) {
	ofstream outFile(filename);
	outFile � "�������� | " � "��������� | " �
		"���" � "\n";
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
		cout � "�����:" � endl;
		cout � "1) �������� �����" � endl;
		cout � "2) ����� �����" � endl;
		cout � "3) ���������� ���� �� ����" � endl;
		cout � "4) ������� ��� �����" � endl;
		cout � "5) ��������� ����� � ����" � endl;
		cout � "6) �������� �����" � endl;
		cout � "7) �����" � endl;

		cout � "������� ��� �����: ";
		cin � choice;

		switch (choice)
		{
			// ���������� ������ �����
		case 1: {
			system("cls");
			string name, type;
			double price;
			int bludo_choice;

			cout � "������� �������� �����: " � endl;
			cin � name;
			cout � "������� ��������� �����: " � endl;
			cin � price;

			cout � "�������� ��� �����: " � endl;
			cout � "1) �������" � endl;
			cout � "2) �������" � endl;
			cout � "3) ��������" � endl;
			cout � "4) ������" � endl;
			cin � bludo_choice;
			switch (bludo_choice)
			{
			case 1: {
				type = "�������";
				bluda.push_back(new MenuItem(name, price, type));
				break;
			}
			case 2: {
				type = "�������";
				string type_appet;
				cout � "������� ��� ������� (�������� ��� �������)" � endl;
				cin � type_appet;
				bluda.push_back(new Appetizer(name, price, type, type_appet));
				break;
			}
			case 3: {
				type = "��������";
				int grammi;
				cout � "������� ������ ��������� �����:" � endl;
				cin � grammi;
				bluda.push_back(new MainCourse(name, price, type, grammi));
				break;
			}
			case 4: {
				type = "������";
				int fat;
				cout � "������� �������� �������:" � endl;
				cin � fat;
				bluda.push_back(new Dessert(name, price, type, fat));
				break;
			}
			}
			break;
		}
			  // ����� �����
		case 2: {
			system("cls");
			string title;
			cout � "������� �������� �����, ������� ������ �����: " � endl;
			cin � title;
			auto it = find_if(bluda.begin(), bluda.end(), [&](const MenuItem* bludo) {
				return bludo->getTitle() == title;
				});

			if (it != bluda.end()) {
				(*it)->displayInfo();
			}
			else {
				cout � "����� �� �������" � endl;
			}
			break;
		}
			  // ���������� ���� �� ����
		case 3: {
			sort(begin(bluda), end(bluda), MenuItem::compareByPrice);
			break;
		}
			  // ����� ���� ����
		case 4: {
			system("cls");
			for (const auto i : bluda) {
				i->displayInfo();
				delete i;
			}
			break;
		}
			  // ���������� ���� � ����
		case 5: {
			system("cls");
			string filename;
			cout � "������� ��� ����� ��� ����������: " � endl;
			cin � filename;
			saveBludaToFile(bluda, filename);
			break;
		}
		case 6: {
			system("cls");
			string title;
			cout � "������� ������ ����� ��� ���������:" � endl;
			cin � title;
			auto it = find_if(bluda.begin(), bluda.end(), [&](const MenuItem* bludo) {
				return bludo->getTitle() == title;
				});

			if (it != bluda.end()) {
				modifyBludo(*it);
			}
			else {
				std::cout � "����� �� �������." � std::endl;
			}
			break;
		}
		case 7:
			break;
		}
	} while (choice != 7);

	system("pause > nul");

	return 0;
}
