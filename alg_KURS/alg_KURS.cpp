#include "Graph.h"

using namespace std;


int getId1() {
	int id1;
	cout << "Введите номер начальной вершины:\n";

	while (!(std::cin >> id1)) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Ошибка: введите целое число.\n";
		std::cout << "Введите номер начальной вершины:\n";
	}
	return id1;
}
int getId() {
	int id;
	cout << "Введите номер вершины:\n";

	while (!(std::cin >> id)) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Ошибка: введите целое число.\n";
		std::cout << "Введите номер вершины:\n";
	}
	return id;
}

int getId2() {
	int id2;
	cout << "Введите номер конечной вершины:\n";
	while (!(std::cin >> id2)) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Ошибка: введите целое число.\n";
		std::cout << "Введите номер конечной вершины:\n";
	}
	return id2;
}


int main()
{
	setlocale(LC_ALL, "rus");
	Graph graph;
	string file = "input.dot";
	bool check1, check2, check3;
	int id;
	int id1;
	int id2;
	int t;
	int w;
	Edge edge1;
	Vertex v1;
	list<int> selectedRoads;
	int roadType;
	char answer;

	char choice;

	do {
		system("cls");		// cleaning screen
		printMenu();
		cout << "Нажмите клавишу...\n";
		choice = _getch();
		switch (choice) {
		case '1':
			// Логика для добавления вершины
			cout << "Вы выбрали: Добавить вершину" << endl;
			id = getId();

			v1.setID(id);
			graph.addVertex(v1);
			PrintSuccess();
			_getch();
			break;
		case '3':
			// Логика для удаления вершины
			cout << "Вы выбрали: Удалить вершину" << endl;
			id = getId();
			if (graph.checkIfVertexExistByID(id)) {
				graph.deleteVertexByID(id);
				PrintSuccess();
				_getch();
			}
			else {
				cout << "Вершина с таким номером не существует.\n";
				PrintFailure();
				_getch();
			}
			break;
		case '4':
			// Логика для добавления ребра
			cout << "Вы выбрали: Добавить ребро" << endl;
			id1 = getId1();
			id2 = getId2();
			if (!graph.checkIfEdgeExistById(id1, id2) && graph.checkIfVertexExistByID(id1) && graph.checkIfVertexExistByID(id2)) {
				cout << "Введите вес ребра:\n"; cin >> w;
				cout << "Введите тип дороги:\n"
					<< "1 - велодорожка\n"
					<< "2 - гравий\n"
					<< "3 - грунт\n"
					<< "4 - автомагистраль\n"; cin >> t;
				graph.addEdgeByID(id1, id2, w, t);
				PrintSuccess();
				_getch();
			}
			else {
				cout << "Ребро между вершинами " << graph.getVertexByID(id1).getID() << " и " << graph.getVertexByID(id2).getID() << " уже существует или таких вершин нет.\n";
				PrintFailure();
				_getch();
			}
			break;
		case '5':
			// Логика для редактирования ребра
			cout << "Вы выбрали: Редактировать ребро" << endl;
			id1 = getId1();
			id2 = getId2();
			if (graph.checkIfEdgeExistById(id1, id2) && graph.checkIfVertexExistByID(id1) && graph.checkIfVertexExistByID(id2)) {
				cout << "Введите НОВЫЙ вес ребра:\n"; cin >> w;
				cout << "Введите НОВЫЙ тип дороги:\n"
					<< "1 - велодорожка\n"
					<< "2 - гравий\n"
					<< "3 - грунт\n"
					<< "4 - автомагистраль\n"
					<< "5 - назад\n"; cin >> t;
				graph.updateEdgeByID(id1, id2, w, t);
				PrintSuccess();
				_getch();
			}
			else {
				cout << "Ребро между вершинами " << graph.getVertexByID(id1).getID() << " и " << graph.getVertexByID(id2).getID() << " не существует.\n";
				PrintFailure();
				_getch();
			}
			break;
		case '6':
			// Логика для удаления ребра
			cout << "Вы выбрали: Удалить ребро" << endl;
			id1 = getId1();
			id2 = getId2();
			if (graph.checkIfEdgeExistById(id1, id2)) {
				graph.deleteEdgeByID(id1, id2);
				PrintSuccess();
				_getch();
			}
			else {
				cout << "Ребро между вершинами " << graph.getVertexByID(id1).getID() << " и " << graph.getVertexByID(id2).getID() << " не существует.\n";
				PrintFailure();
				_getch();
			}
			break;
		case 'e':
			cout << "Выход" << endl;
			break;
		case 's':
			// Логика для показа из файла графа
			cout << "Вы выбрали: Показать граф" << endl;
			graph.saveGraphToFile(file);
			system("showgraph.bat");
			_getch();
			break;
		case 'd':
			// Логика для нахождения кратчайшего пути
			cout << "Вы выбрали: Кратчайший путь" << endl;
			id1 = getId1();
			if (graph.checkIfVertexExistByID(id1)) {
				id2 = getId2();
				if (graph.checkIfVertexExistByID(id2)) {
					cout << "Введите приемлемые дороги:\n"
						<< "1 - велодорожка\n"
						<< "2 - гравий\n"
						<< "3 - грунт\n"
						<< "4 - автомагистраль\n"
						<< "5 - назад\n";
					while (true) {
						std::cin >> roadType;

						if (roadType >= 1 && roadType <= 4) {
							selectedRoads.push_back(roadType);
						}
						else if (roadType == 5) {
							break;
						}
						else {
							std::cout << "Некорректный ввод. Попробуйте снова.\n";
							break;
						}
					}
					graph.dijkstra(id1, id2, selectedRoads);
					if (graph.sp == 777) {
						cout << "нет такого пути\n";
					}
					else {
						cout << "Сохранить путь?\n"
							<< "y - сохранить\n"
							<< "n - отмена\n";
						std::cin >> answer;
						if (answer == 'y') {
							cout << graph.pathStr << endl;
						}
						else {
							cout << "Не сохраняем путь...\n";
						}
					}
					PrintSuccess();
					selectedRoads.clear();
					_getch();
				}
				else {
					cout << "Вершина с таким номером не существует.\n";
					PrintFailure();
					_getch();
				}
			}
			else {
				cout << "Вершина с таким номером не существует.\n";
				PrintFailure();
				_getch();
			}
			break;
			_getch();
			break;
		default:
			PrintWrong();
			_getch();
			break;
		}
	} while (choice != 'e');
}
