#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>

struct Node
{
	int MSSV;
	std::string FullName;
	int age;
	float point;
	
	Node* next;
};

struct LinkedList
{
	Node* head;
	int length;
};

void ReadData(LinkedList* list, std::string NameFile)
{
	std::ifstream input(NameFile);
	std::string StringLine;
	int CountStudent = 0;
	Node* p = NULL;
	while (std::getline(input, StringLine))
	{
		Node* NewNode = new Node();
		std::stringstream ss(StringLine);
		std::string temp;
		std::vector <std::string> information;
		while (std::getline(ss,temp, '|'))
			information.push_back(temp);

		//add more information about student in here
		int indx = 0;
		NewNode->MSSV = stoi(information[indx++]);
		NewNode->FullName = information[indx++];
		NewNode->age = stoi(information[indx++]);
		NewNode->point = stod(information[indx++]);

		CountStudent++;
		if (CountStudent == 1)
		{
			list->head = NewNode;
			p = list->head;
		}
		else
		{
			p->next = NewNode;
			p = p->next;
		}
	}
	list->length = CountStudent;
}

void gotocol(int col)
{
	std::cout << "\033[" << col << "G";
}

void print_list(LinkedList* list)
{	
	std::cout << "\t+-------+----------+------------------------------+-------+-------+\n"
		<< "\t| No.   | MSSV     | Full name                    | Age   | Point |\n"
		<< "\t+-------+----------+------------------------------+-------+-------+\n";
	int count = 0;
	for (Node* p = list->head;p != NULL;p = p->next)
	{
		count++;
		std::cout << "\t| " << count << "\t| " << p->MSSV;
		gotocol(28);
		std::cout << "| " << p->FullName;
		gotocol(59);
		std::cout << "| " << p->age;
		gotocol(67);
		std::cout << "| " << p->point;
		gotocol(75);
		std::cout << "|\n";
	}
	std::cout << "\t+-------+----------+------------------------------+-------+-------+\n";
}

void push_back(LinkedList* list)
{
	list->length++;
	int NewMSSV;
	std::string NewFullName;
	int NewAge;
	float NewPoint;
	std::cout << "[2] Add Student\n";
	std::cout << "\t(?) Enter MSSV: "; std::cin >> NewMSSV;
	std::cout << "\t(?) Enter full name: ";
	std::cin.ignore();
	std::getline(std::cin,NewFullName);
	std::cout << "\t(?) Enter age: "; std::cin >> NewAge;
	std::cout << "\t(?) Enter point: "; std::cin >> NewPoint;
	Node* NewNode = new Node({NewMSSV,NewFullName,NewAge,NewPoint });
	if (list->head == NULL)
	{
		list->head = NewNode;
	}
	else
	{
		Node* p = list->head;
		//Go to the end of the list
		while (p->next != NULL)
		{
			p = p->next;
		}
		p->next = NewNode;
	}
	
	std::cout << "\t(!) Add Successfully!\n";
}

void modify(LinkedList* list)
{
	int index;
	std::cout << "\t(?) Enter the Numero of student that need modify: "; std::cin >> index;

	if (index <= 0 || index > list->length)
	{
		std::cout << "Out of range!!\n"; 
		return;
	}

	std::cout << "Choose the information need change:\n"
		<< "\t1 - MSSV\n"
		<< "\t2 - FullName\n"
		<< "\t3 - Age\n"
		<< "\t4 - Point\n";
	int number;
	std::cout << "\t(?) Choose: "; std::cin >> number;

	//move to the position the modify point
	int count = 1;
	Node* p = list->head;
	while (count < index)
	{
		count++;
		p = p->next;
	}
	
	if (number == 1)
	{
		int NewMSSV;
		std::cout << "(?) Enter MSSV: "; std::cin >> NewMSSV;
		p->MSSV = NewMSSV;
	}
	else if (number == 2)
	{
		std::string NewFullName;
		std::cout << "(?) Enter Full Name: ";
		std::cin.ignore();
		std::getline(std::cin, NewFullName);
		p->FullName = NewFullName;
	}
	else if (number == 3)
	{
		int NewAge;
		std::cout << "(?) Enter Age: "; std::cin >> NewAge;
		p->age = NewAge;
	}
	else if (number == 4)
	{
		float NewPoint;
		std::cout << "(?) Enter Point: "; std::cin >> NewPoint;
		p->point = NewPoint;
	}
	else
	{
		std::cout << "Out of range!!\n";
		return;
	}
}

void erase(LinkedList* list)
{
	int index;
	std::cout << "\t(?) Enter numero: ";std::cin >> index;

	if (index <= 0 || index > list->length)
	{
		std::cout << "Out of range!!\n";
		return;
	}

	//move to the position immediately before the erased point
	int count = 1;
	Node* p = list->head;
	while (count < index-1)
	{
		count++;
		p = p->next;
	}
	Node* OldNode = p->next;
	p->next = p->next->next;
	free(OldNode);
	std::cout << "\t(!) Erase successfuly!\n";
}

void search(LinkedList* list)
{
	std::string FindName;
	std::cout << "\t(?) Enter the character/name: ";
	std::cin.ignore();
	std::getline(std::cin, FindName);
	bool check = false; //check whether find successfully or not
	LinkedList ListFind(NULL, 0);
	Node* PtrFind = ListFind.head;
	for (Node* p = list->head;p != NULL;p = p->next)
	{
		if (p->FullName.find(FindName) != std::string::npos)
		{
			if (ListFind.head == NULL)
			{
				check = true;
				Node* CopyStudent = new Node(p->MSSV, p->FullName, p->age, p->point, NULL);
				ListFind.head = CopyStudent;
				PtrFind = ListFind.head;
			}
			else
			{
				Node* CopyStudent = new Node(p->MSSV, p->FullName, p->age, p->point, NULL);
				PtrFind->next = CopyStudent;
				PtrFind = PtrFind->next;
			}
		}
	}
	if (check)
		print_list(&ListFind);
	else
		std::cout << "\t(!) Not found the Character/String\n";
}

void swap_node(Node* p, Node* q)
{
	int MSSVTemp = p->MSSV;
	std::string FullNameTemp = p->FullName;
	int AgeTemp = p->age;
	float PointTemp = p->point;
	p->MSSV = q->MSSV;
	p->FullName = q->FullName;
	p->age = q->age;
	p->point = q->point;
	q->MSSV = MSSVTemp;
	q->FullName = FullNameTemp;
	q->age = AgeTemp;
	q->point = PointTemp;
}

std::string get_given_name(std::string FullName)
{
	int FindSpace = FullName.find(' ');
	while (FindSpace != std::string::npos)
	{
		FullName = FullName.substr(FindSpace + 1);
		FindSpace = FullName.find(' ');
	}
	return FullName;
}

void sort(LinkedList* list)
{
	std::cout << "\t(?) Kind of sort:\n"
		<< "\t(!) 1 - sort by MSSV (ascending oder)\n"
		<< "\t(!) 2 - Sort by ABC\n"
		<< "\t(!) 3 - Sort by age (ascending oder)\n"
		<< "\t(!) 4 - Sort by point (ascending oder)\n";
	int KindSort;
	std::cout << "(?) Choose: "; std::cin >> KindSort;

	if (KindSort == 1)
	{
		for (Node* p = list->head;p != NULL;p = p->next)
			for (Node* q = p->next;q != NULL;q = q->next)
				if (p->MSSV > q->MSSV)
					swap_node(p, q);
	}
	else if (KindSort == 2)
	{
		for (Node* p = list->head;p != NULL;p = p->next)
			for (Node* q = p->next;q != NULL;q = q->next)
				if (get_given_name(p->FullName) > get_given_name(q->FullName))
					swap_node(p, q);
	}
	else if (KindSort == 3)
	{
		for (Node* p = list->head;p != NULL;p = p->next)
			for (Node* q = p->next;q != NULL;q = q->next)
				if (p->age > q->age)
					swap_node(p, q);
	}
	else if (KindSort == 4)
	{
		for (Node* p = list->head;p != NULL;p = p->next)
			for (Node* q = p->next;q != NULL;q = q->next)
				if (p->point > q->point)
					swap_node(p, q);
	}
	else
	{
		std::cout << "OUT OF RANGE!\n";
		return;
	}

	print_list(list);
}

void compile_statistic(LinkedList* list)
{
	// Excellent student: point >= 8
	// Good student: point >= 4 
	// Poor student: point < 4
	float AveragePoint = 0,ExtSt = 0,GdSt = 0,PrSt = 0,HighestPoint = 0;
	for (Node* p = list->head;p != NULL;p = p->next)
	{
		AveragePoint += p->point;
		if (p->point >= 8)
			ExtSt++;
		else if (p->point >= 4)
			GdSt++;
		else PrSt++;
		if (p->point > HighestPoint)
			HighestPoint = p->point;
	}
	AveragePoint /= list->length;
	ExtSt = (ExtSt / list->length) * 100;
	GdSt = (GdSt / list->length) * 100;
	PrSt = (PrSt / list->length) * 100;
	
	std::cout << "\t(!) Class's Average point: " << AveragePoint << "\n"
		<< "\t(!) Excellent student rate: " << ExtSt << "%" << "\n"
		<< "\t(!) Good student rate: " << GdSt << "%" << "\n"
		<< "\t(!) Poor student rate: " << PrSt << "%" << "\n"
		<< "\t(!) Students have highest point (" << HighestPoint << "):\n";
	for (Node* p = list->head;p != NULL;p = p->next)
		if (p->point == HighestPoint)
			std::cout << "\t\t" << p->FullName << "\n";
}

void save(LinkedList* list, std::string NameFile)
{
	std::cout << "Save successfully!";
	std::ofstream writer(NameFile);

	for (Node* p = list->head;p != NULL;p = p->next)
		writer << p->MSSV << "|" << p->FullName << "|" << p->age << "|" << p->point << "\n";
}

int main()
{
	LinkedList StudentList(NULL, 0);
	std::string NameFile = "Data.txt";
	ReadData(&StudentList, NameFile);
	int command = 0;
	while (command != 9)
	{
		std::cout << "List activities:\n"
			<< "1 - Print student's list\n"
			<< "2 - Add\n"
			<< "3 - Modify\n"
			<< "4 - Erase\n"
			<< "5 - Find\n"
			<< "6 - Sort\n"
			<< "7 - Compile statistics\n"
			<< "8 - Save\n"
			<< "9 - End\n";
		std::cout << "Enter command: ";std::cin >> command;
		if (command == 1)
		{
			std::cout << "[1] Print student list:\n";
			print_list(&StudentList);
		}
		else if (command == 2)
			push_back(&StudentList);
		else if (command == 3)
		{
			std::cout << "[3] modify student's information:\n";
			modify(&StudentList);
		}
		else if (command == 4)
		{
			std::cout << "[4] Erase student\n";
			erase(&StudentList);
		}
		else if (command == 5)
		{
			std::cout << "[5] Search:\n";
			search(&StudentList);
		}
		else if (command == 6)
		{
			std::cout << "[6] Sort:\n";
			sort(&StudentList);
		}
		else if (command == 7)
		{
			std::cout << "[7] Statistic\n";
			compile_statistic(&StudentList);
		}
		else if (command == 8)
		{
			std::cout << "[8] Save List\n";
			save(&StudentList, NameFile);
		}

		std::cout << "Press any key to continue...";
		std::cin.ignore();
		std::cin.get();
		system("cls");
	}
}