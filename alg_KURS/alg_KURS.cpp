#include "Graph.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");
	Graph graph;
	string file = "input.dot";
	bool check1, check2, check3;
	int id1;
	int id2;
	int t;
	int w;
	Edge edge1;
	Vertex v1;
	list<int> selectedRoads;
	int roadType;


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
			cout << "Введите номер вершины:\n"; cin >> id1;

			v1.setID(id1);
			graph.addVertex(v1);
			PrintSuccess();
			_getch();
			break;
		case '3':
			// Логика для удаления вершины
			cout << "Вы выбрали: Удалить вершину" << endl;
			cout << "Введите номер вершины:\n"; cin >> id1;
			if (graph.checkIfVertexExistByID(id1)) {
				graph.deleteVertexByID(id1);
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
			cout << "Введите номер начальной вершины:\n"; cin >> id1;
			cout << "Введите номер конечной вершины:\n"; cin >> id2;
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
			cout << "Введите номер начальной вершины:\n"; cin >> id1;
			cout << "Введите номер конечной вершины:\n"; cin >> id2;
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
			cout << "Введите номер начальной вершины:\n"; cin >> id1;
			cout << "Введите номер конечной вершины:\n"; cin >> id2;
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
			cout << "Введите номер начальной вершины:\n"; cin >> id1;
			if (graph.checkIfVertexExistByID(id1)) {
				cout << "Введите номер конечной вершины:\n"; cin >> id2;
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
						}
					}
					graph.dijkstra(id1, id2, selectedRoads);
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
