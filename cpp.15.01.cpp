#include<iostream>
#include <string>
#include <fstream>
#include <sstream>

struct Person
{
	std::string FullName;
	int age;
	float height,weight;
	std::string nationality;
};

int load_person(std::string filename, Person* person_list)
{
	int count = 0;
	std::string list;
	std::ifstream input(filename);
	while (std::getline(input, list))
	{
		//get FullName
		int found = list.find('|');
		person_list[count].FullName = list.substr(0, found);
		list = list.substr(found + 1);
		
		//get Age,Height and Weigth
		for (int i = 0;i < list.size();i++)
			if (list[i] ==  '|')
				list[i] = ' ';
		std::stringstream ss(list);
		ss >> person_list[count].age >> person_list[count].height
			>> person_list[count].weight;

		//get Nationality
		std::getline(ss, person_list[count].nationality);
		person_list[count].nationality = person_list[count].nationality.substr(1);

		count++;
	}
	return count;
}

void add_person(std::string filename)
{
	std::string fn, na;
	int a;
	float h, w;
	
	std::ofstream writer(filename,std::ios::app);
	//If don't have "std::ios::app",the app will delete the input before write

	std::cin.ignore();
	std::cout << "Enter full name: "; std::getline(std::cin, fn);
	std::cout << "Enter age: "; std::cin >> a;
	std::cout << "Enter height: "; std::cin >> h;
	std::cout << "Enter weight: "; std::cin >> w;
	std::cin.ignore();
	std::cout << "Enter nationality: "; std::getline(std::cin, na);
	writer << "\n" << fn << "|" << a << "|" << h << "|" << w << "|" << na;
}

void print_persons(Person* person_list, int count)
{
	for (int i = 0;i < count;i++)
	{
		std::cout << "Name: " << person_list[i].FullName << "\n"
			<< "Age: " << person_list[i].age << "\n"
			<< "Height: " << person_list[i].height << "\n"
			<< "Weight: " << person_list[i].weight << "\n"
			<< "Nationality: " << person_list[i].nationality << "\n"
			<< "============================\n";
	}
}

int main()
{
	const std::string filename = "Data.txt";
	int command;

	do
	{ 
		std::cout << "Enter options (1 - Print / 2 - Add): ";
		std::cin >> command;
		 if (command == 2)
			add_person(filename);
	} while (command == 2);
	if (command == 1)
	{
		const int MAX = 100;
		Person person_list[MAX];
		int count = load_person(filename, person_list);
		print_persons(person_list, count);
	}
	else std::cout << "Invalid value!!!";
}
