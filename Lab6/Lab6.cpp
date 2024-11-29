#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class DisciplinePlanner {
public:
    DisciplinePlanner(int numDisciplines);
    void addDependency(int discipline, int prerequisite);
    bool checkFeasibility();
    void printOrder();

private:
    int numDisciplines;
    vector<vector<int>> dependencies;
    vector<int> inDegree;
    vector<int> order;
};

DisciplinePlanner::DisciplinePlanner(int numDisciplines)
    : numDisciplines(numDisciplines), dependencies(numDisciplines), inDegree(numDisciplines, 0) {}

void DisciplinePlanner::addDependency(int discipline, int prerequisite) {
    dependencies[prerequisite].push_back(discipline);
    inDegree[discipline]++;
}

bool DisciplinePlanner::checkFeasibility() {
    queue<int> q;
    order.clear();

    // Инициализация очереди с дисциплинами, которые не имеют предварительных условий
    for (int i = 0; i < numDisciplines; ++i) {
        if (inDegree[i] == 0) {
            q.push(i);
        }
    }

    // Топологическая сортировка
    while (!q.empty()) {
        int current = q.front();
        q.pop();
        order.push_back(current);

        for (int neighbor : dependencies[current]) {
            inDegree[neighbor]--;
            if (inDegree[neighbor] == 0) {
                q.push(neighbor);
            }
        }
    }

    // Проверка, что все дисциплины были добавлены в порядок
    return order.size() == numDisciplines;
}

void DisciplinePlanner::printOrder() {
    for (int discipline : order) {
        cout << discipline << " ";
    }
    cout << endl;
}

int main() 
{
    setlocale(LC_ALL, "RU");
    int choice, numDisciplines, numEdges, v, w;
    DisciplinePlanner* planner = nullptr;

    while (true) {
        cout << "=========Меню=========\n";
        cout << "1. Ввод данных о связанных дисциплинах\n";
        cout << "2. Проверка возможности корректного размещения дисциплин в учебном плане\n";
        cout << "3. Выход из программы\n";
        cout << "Выберите пункт меню: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Введите количество дисциплин: ";
            cin >> numDisciplines;
            planner = new DisciplinePlanner(numDisciplines);

            cout << "Введите количество связей между дисциплинами: ";
            cin >> numEdges;

            for (int i = 0; i < numEdges; ++i) {
                cout << "Введите пару связанных дисциплин (например, 2 1): ";
                cin >> v >> w;
                planner->addDependency(v, w);
            }
            break;

        case 2:
            if (planner == nullptr) {
                cout << "Сначала введите данные о связанных дисциплинах.\n";
            }
            else {
                if (planner->checkFeasibility()) {
                    cout << "Корректное размещение дисциплин в учебном плане возможно. Порядок освоения дисциплин:\n";
                    planner->printOrder();
                }
                else {
                    cout << "Невозможно корректно разместить все дисциплины в учебном плане (есть циклы).\n";
                }
            }
            break;

        case 3:
            delete planner;
            return 0;

        default:
            cout << "Неверный выбор. Попробуйте снова.\n";
        }
    }

    return 0;
}
