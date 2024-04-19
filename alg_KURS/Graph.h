#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <limits>
#include <iterator>
#include <list>
#include <conio.h>
#include<string>
#include <fstream>
#include <unordered_set>
#include <algorithm>
#include <regex>
using namespace std;




class Edge {
public:
	int DestinationVertexId;
	int weight;
	int traffic;

	Edge() {

	}
	Edge(int destVID, int w, int t) {
		DestinationVertexId = destVID;
		weight = w;
		traffic = t;
	}

	void setEdgeValues(int destVID, int w, int t) {
		DestinationVertexId = destVID;
		weight = w;
		traffic = t;
	}

	void setDestinationVertexId(int destVID) {
		DestinationVertexId = destVID;
	}

	int getDestinationVertexId() {
		return DestinationVertexId;
	}

	int getWeight() {
		return weight;
	}

	void setWeight(int w) {
		weight = w;
	}

	int getTraffic() {
		return traffic;
	}

	void setTraffic(int t) {
		traffic = t;
	}
};



class Vertex {
public:

	int id;
	list<Edge> edgeList;


	Vertex() {
		id = 0;
	}

	Vertex(int id) {
		this->id = id;
	}

	int getID() {
		return id;
	}

	void setID(int id) {
		this->id = id;
	}

	list<Edge> getEdgeList() {
		return edgeList;
	}

	void printEdgeList() {
		cout << " [";
		for (auto it = edgeList.begin(); it != edgeList.end(); it++) {
			cout << it->getDestinationVertexId() << " (" << it->getWeight() << ", " << it->getTraffic() << ") --> ";
		}
		cout << "]\n";
	}

	void printToFileEdgeList(ofstream file) {

		cout << " [";
		for (auto it = edgeList.begin(); it != edgeList.end(); it++) {
			file << "  " << it->getDestinationVertexId() << " -- " << it->getDestinationVertexId() << " [label=\"" << it->getWeight() << ", " << it->getTraffic() << "\"];\n";
		}
		cout << "]\n";
	}
};

class Graph {

public:
	// список вершин
	vector<Vertex> vertices;

	// хранение пути
	string pathStr;

	int sp;

	// все методы работы с графом будут тут
	// добавить вершину
	void addVertex(Vertex newVertex) {
		if (checkIfVertexExistByID(newVertex.getID())) {
			cout << "Вершина с таким номером уже существует.\n";
		}
		else {
			vertices.push_back(newVertex);
			cout << "Новая вершина добавлена.\n";
		}
	}

	// существует ли вершина?
	bool checkIfVertexExistByID(int vid) {
		for (int i = 0; i < vertices.size(); i++) {
			if (vertices.at(i).getID() == vid) {
				return true;
			}
		}
		return false;

	}
	// получить вершину по номеру
	Vertex getVertexByID(int v) {
		Vertex temp;
		for (int i = 0; i < vertices.size(); i++) {
			temp = vertices.at(i);	// по хорошему тут нужно обработать исключение
			if (temp.getID() == v) {
				return temp;
			}
		}
		return temp;
	}
	// существует ли ребро?
	bool checkIfEdgeExistById(int fromVertex, int toVertex) {
		Vertex v = getVertexByID(fromVertex);
		list <Edge> e;
		e = v.getEdgeList();
		for (auto it = e.begin(); it != e.end(); it++) {

			if (it->getDestinationVertexId() == toVertex) {
				return true;
			}
		}
		return false;
	}
	// добавить ребро
	void addEdgeByID(int fromVertex, int toVertex, int w, int t) {
		for (int i = 0; i < vertices.size(); i++) {
			if (vertices.at(i).getID() == fromVertex) {
				Edge e(toVertex, w, t);
				vertices.at(i).edgeList.push_back(e);
				// если граф неориетированный то нужно еще раз добавить от toVertex до fromVertex
			}
			else if (vertices.at(i).getID() == toVertex) {
				Edge e(fromVertex, w, t);
				vertices.at(i).edgeList.push_back(e);
			}
		}
		cout << "Ребро между вершинами " << getVertexByID(fromVertex).getID() << " и " << getVertexByID(toVertex).getID() << " добавлено.\n";
	}
	// напечатать граф
	void printGraph() {
		Vertex temp;
		for (int i = 0; i < vertices.size(); i++) {
			temp = vertices.at(i);
			cout << temp.getID() << " --> ";
			temp.printEdgeList();
		}
	}
	// удалить ребро
	void deleteEdgeByID(int fromVertex, int toVertex) {
		//if (checkIfEdgeExistById(fromVertex, toVertex)) {
		for (int i = 0; i < vertices.size(); i++) {					// проходим по вектору вершин
			if (vertices.at(i).getID() == fromVertex) {				// находим нужную вершину
				for (auto it = vertices.at(i).edgeList.begin();		// проходим по списку ребёр этого узла
					it != vertices.at(i).edgeList.end(); it++) {	// 
					if (it->getDestinationVertexId() == toVertex) { // находим вторую нужную вершину
						vertices.at(i).edgeList.erase(it);			// удаляем ребро с первой вершины до второй
						//cout << "Первое удаление\n";
						break;
					}
				}
			}

			if (vertices.at(i).getID() == toVertex) {				// проходим по вектору вершин
				for (auto it = vertices.at(i).edgeList.begin();		// находим нужную вершину
					it != vertices.at(i).edgeList.end(); it++) {	// проходим по списку ребёр этого узла
					if (it->getDestinationVertexId() == fromVertex) { // 
						vertices.at(i).edgeList.erase(it);			// находим вторую нужную вершину
						//cout << "Второе удаление\n";				// удаляем ребро со второй вершины до первой
						break;
					}
				}
			}
		}
	}
	// обновить вершину
	void updateEdgeByID(int fromVertex, int toVertex, int newWeight, int newTraffic) {
		if (checkIfEdgeExistById(fromVertex, toVertex)) {
			for (int i = 0; i < vertices.size(); i++) {
				if (vertices.at(i).getID() == fromVertex) {
					for (auto it = vertices.at(i).edgeList.begin();
						it != vertices.at(i).edgeList.end(); it++) {
						if (it->getDestinationVertexId() == toVertex) {
							it->setWeight(newWeight);
							it->setTraffic(newTraffic);
							break;
						}
					}
				}
				else if (vertices.at(i).getID() == toVertex) {
					for (auto it = vertices.at(i).edgeList.begin();
						it != vertices.at(i).edgeList.end(); it++) {
						if (it->getDestinationVertexId() == fromVertex) {
							it->setWeight(newWeight);
							it->setTraffic(newTraffic);
							break;
						}
					}
				}
			}
		}
		else {
			cout << "Ребро между " << getVertexByID(fromVertex).getID() << " и " <<
				getVertexByID(toVertex).getID() << " не существует!\n";
		}
	}
	// удалить вершину
	void deleteVertexByID(int vid) {
		int vIndex = 0;
		for (int i = 0; i < vertices.size(); i++) {
			if (vertices.at(i).getID() == vid) {
				vIndex = i;
			}
		}

		for (int i = 0; i < vertices.size(); i++) {
			deleteEdgeByID(vertices.at(i).getID(), vid);
		}

		vertices.erase(vertices.begin() + vIndex);
		cout << "Вершина удалена.\n";
	}

	struct PairHash {
		template <class T1, class T2>
		std::size_t operator () (const std::pair<T1, T2>& p) const {
			auto h1 = std::hash<T1>{}(p.first);
			auto h2 = std::hash<T2>{}(p.second);

			// Простое комбинирование хешей
			return h1 ^ h2;
		}
	};

	struct PairEqual {
		template <class T1, class T2>
		bool operator () (const std::pair<T1, T2>& lhs, const std::pair<T1, T2>& rhs) const {
			return lhs.first == rhs.first && lhs.second == rhs.second;
		}
	};

	void saveGraphToFile(const string& filename) {
		ofstream file(filename);

		if (!file.is_open()) {
			cerr << "Ошибка открытия файла для записи.\n";
			return;
		}
		file << "graph G {\n";
		std::unordered_set<std::pair<int, int>, PairHash, PairEqual> addedEdges;//Множество для отслеживания уже добавленных рёбер
		Vertex temp;
		for (int i = 0; i < vertices.size(); i++) {
			for (auto it = vertices.at(i).edgeList.begin(); it != vertices.at(i).edgeList.end(); it++) {
				// Проверка, было ли уже добавлено такое ребро
				// создаём ребро с двумя вершинами
				pair<int, int> edge1 = { vertices.at(i).getID(),it->getDestinationVertexId() };
				pair<int, int> edge2 = { it->getDestinationVertexId(), vertices.at(i).getID() };
				// если нет этого ребра в unordered set то добавляем
				if (addedEdges.find(edge1) == addedEdges.end() && addedEdges.find(edge2) == addedEdges.end()) {

					file << "  " << vertices.at(i).getID() << " -- " << it->getDestinationVertexId() << " [label=\"" << it->getWeight() << ", " << it->getTraffic() << "\"];\n";
					addedEdges.insert(edge1);  // Добавляем ребро в множество
					_getch();
				}
			}
		}
		file << "}\n";
	}

	// алгоритмы
	// Очередь с приоритетами для получения ребра с минимальным весом

	void dijkstra(int fromVertex, int toVertex, list<int> accept_roads) {

		unordered_map<int, int> distance;
		unordered_map<int, bool> visited;

		for (Vertex vertex : vertices) {
			distance[vertex.getID()] = 777;
			visited[vertex.getID()] = false;
		}

		distance[fromVertex] = 0;

		// очередь с приоритетами неубываюшая
		priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
		pq.push({ 0, fromVertex });		// заносим в очередь начальную вершину

		// пока очередь не пуста
		while (!pq.empty()) {
			// рассматриваемая вершина берет с помощью pq.top().second вершину из очереди ( с наименьшим расстоянием до этой вершины)
			int currentVertex = pq.top().second;
			// вытаскиваем эту вершину, так как мы её рассматриваем в переменной currentVertex
			pq.pop();
			// если вершина посещена то переходим к следующей итерации
			if (visited[currentVertex]) {
				continue;
			}
			// помечаем вершину как помеченую (если мы сюда дошли то вершина до этого не посещалась)
			visited[currentVertex] = true;

			// перебираем все ребра рассматриваемой вершины
			for (Edge edge : getVertexByID(currentVertex).getEdgeList()) {
				// соседняя вершина - конечная вершина ребра с наименьшим весом, которая есть у рассматриваемой вершины
				int neighbor = edge.getDestinationVertexId();
				// считаем новое расстояние учитывая эту вершину
				int newDistance = distance[currentVertex] + edge.getWeight();

				if (find(accept_roads.begin(), accept_roads.end(), edge.getTraffic()) == accept_roads.end()) {
					continue;
				}

				// ослабляем соседей
				if (newDistance < distance[neighbor]) {
					distance[neighbor] = newDistance;
					pq.push({ distance[neighbor], neighbor });
				}
			}
		}
		sp = distance[toVertex];
		cout << "Кратчайший путь  с " << fromVertex << " до " << toVertex << ": " << distance[toVertex] << endl;

		printShortestPath(fromVertex, toVertex, distance, pathStr);
		cout << endl;
	}


	// печатает кратчайший путь
	void printShortestPath(int fromVertex, int toVertex, unordered_map<int, int>& distance, string& pathStr) {

		if (distance[toVertex] == 777) {
			cout << "Путь не найден";
			return;
		}

		// вектор для хранения вершин кратчайшего пути
		vector<int> path;
		// текущая рассматриваемая вершина(начинаем с конца)
		int currentVertex = toVertex;
		Vertex tempVertex;
		int checkDist;
		int tempDist;
		while (currentVertex != fromVertex) {
			tempVertex = getVertexByID(currentVertex);
			// перебираем ребра вершины (начинаем с конечной вершины)
			for (Edge edge : tempVertex.getEdgeList()) {
				// считаем расстояние между вершиной и предыдущей ей вершиной
				checkDist = distance[currentVertex] - edge.getWeight();
				// если расстояние до предыдущей совпадает с путем
				if (checkDist == distance[edge.getDestinationVertexId()]) {
					// то это нужная нам вершина, и мы с неё пришли!
					// обновляем текущую вершину
					currentVertex = edge.getDestinationVertexId();
					// добавляем её в вектор пути вершин
					path.push_back(currentVertex);

					// далее нет смысла смотреть другие вершины
					break;
				}
			}
		}
		reverse(path.begin(), path.end());

		pathStr.clear();
		for (int vertex : path) {
			pathStr += to_string(vertex) + "--";
		}
		pathStr += to_string(toVertex);

		for (int vertex : path) {
			cout << vertex;
			cout << "--";

		}
		cout << toVertex;
		cout << '\n';
	}

};

void printMenu() {
	cout << "Выберите опцию:" << endl;
	cout << "1. Добавить вершину" << endl;
	cout << "3. Удалить вершину" << endl;
	cout << "4. Добавить ребро" << endl;
	cout << "5. Редактировать ребро" << endl;
	cout << "6. Удалить ребро" << endl;
	cout << "d. Найти кратчайший путь" << endl;
	cout << "s. Показать граф" << endl;
	cout << "e. Выход" << endl;
}

void PrintSuccess() {
	cout << "\nУспешно.Нажмите любую клавишу для продолжения...\n";
}
void PrintFailure() {
	cout << "\nНеудачно. Нажмите любую клавишу для продолжения...\n";
}
void PrintWrong() {
	cout << "\nНеверный выбор. Нажмите любую клавишу для продолжения...\n";
}
