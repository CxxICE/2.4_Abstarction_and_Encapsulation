#include <iostream>
#include <string>
#include <fstream>

class Adresses
{
public:
	Adresses(std::ifstream &inFile);
	
	std::string getAdressInline();

private:
	std::string city;
	std::string street;
	int build;
	int flat;
};

Adresses::Adresses(std::ifstream &inFile)
{
	inFile >> city;
	inFile >> street;
	inFile >> build;
	inFile >> flat;
}

//функция создания строки адреса
std::string Adresses::getAdressInline()
{
	return (city + ", " + street + ", " + std::to_string(build) + ", " + std::to_string(flat));
}

int main()
{
	setlocale(LC_ALL, "RU");

	int countAdr;

	std::ifstream inFile;
	inFile.open("in.txt");
	if (inFile.is_open())
	{
		inFile >> countAdr;
		//создание динамического массива указателей на объекты
		Adresses **adressArr = new Adresses *[countAdr];
		for (int i = 0; i < countAdr; ++i)
		{
			adressArr[i] = new Adresses(inFile);
		}
		inFile.close();

		std::ofstream outFile;
		outFile.open("out.txt");
		//запись в файл адресов
		if (outFile.is_open())
		{
			outFile << countAdr;
			for (int i = countAdr - 1; i >= 0; --i)
			{
				outFile << "\n" << (adressArr[i]->getAdressInline());
			}
			outFile.flush();
			outFile.close();

			//освобождение памяти
			for (int i = 0; i < countAdr; ++i)
			{
				delete adressArr[i];
			}
			delete[] adressArr;
			adressArr = nullptr;
		}
		else
		{
			std::cout << "Ошибка открытия файла out.txt!" << std::endl;
		}
	}
	else
	{
		std::cout << "Ошибка открытия файла in.txt!" << std::endl;
	}
	return 0;
}

