#include <iostream>
#include <string>
#include <fstream>

class Adresses
{
public:
	Adresses(std::ifstream &inFile);

	std::string getAdressInline();
	std::string getCity() { return city; }

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

//сортировка по городу, нестабильная --> было б лучше сортировать по полной строке
void quickSortRecurs(Adresses **arr, int size) 
{
	if (size <= 1) { return; }
	int i_left, i_right;
	std::string pivot;
	Adresses *tmp;
	bool change;

	pivot = arr[size / 2]->getCity();
	i_left = 0;
	i_right = size - 1;
	while (i_left <= i_right)
	{
		while (arr[i_left]->getCity() < pivot) { i_left++; }
		while (arr[i_right]->getCity() > pivot) { i_right--; }
		if (i_left <= i_right)
		{
			tmp = arr[i_right];
			arr[i_right] = arr[i_left];
			arr[i_left] = tmp;
			i_left++;
			i_right--;
		}
	}
	if (i_right > 0) { quickSortRecurs(arr, i_right + 1); }
	if (i_left < size - 1) { quickSortRecurs(arr + i_left, size - i_left); }	
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

		//вызов сортировки массива
		quickSortRecurs(adressArr, countAdr);


		std::ofstream outFile;
		outFile.open("out.txt");
		//запись в файл адресов
		if (outFile.is_open())
		{
			outFile << countAdr;
			for (int i = 0; i < countAdr; ++i)
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

