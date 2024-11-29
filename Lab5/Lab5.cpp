#include <iostream>
#include <string>
#include <algorithm>

//Структура данных для хранения информации о студентах
struct Student 
{
    int id;
    std::string name;
    int course;
    std::string enrollmentDate;
    std::string contactInfo;

    Student(int id, const std::string& name, int course, const std::string& enrollmentDate, const std::string& contactInfo)
        : id(id), name(name), course(course), enrollmentDate(enrollmentDate), contactInfo(contactInfo) {}
};

//Узел АВЛ-дерева
struct AVLNode 
{
    Student student;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(const Student& student)
        : student(student), left(nullptr), right(nullptr), height(1) {}
};

//Функции для работы с АВЛ-деревом
class AVLTree 
{
public:
    AVLTree() : root(nullptr) {}

    void insert(const Student& student) 
    {
        root = insert(root, student);
    }

    void display() const
    {
        display(root, 0);
    }

    void clear()
    {
        clear(root);
        root = nullptr;
    }

    Student* search(int id) const 
    {
        return search(root, id);
    }

    void remove(int id) 
    {
        root = remove(root, id);
    }

private:
    AVLNode* root;

    int height(AVLNode* node) {
        return node ? node->height : 0;
    }

    int balanceFactor(AVLNode* node) {
        return node ? height(node->left) - height(node->right) : 0;
    }

    void updateHeight(AVLNode* node) {
        if (node) {
            node->height = 1 + std::max(height(node->left), height(node->right));
        }
    }

    AVLNode* rotateRight(AVLNode* y) 
    {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    AVLNode* rotateLeft(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    AVLNode* insert(AVLNode* node, const Student& student) 
    {
        if (!node) 
        {
            return new AVLNode(student);
        }

        if (student.id < node->student.id) 
        {
            node->left = insert(node->left, student);
        }
        else if (student.id > node->student.id) 
        {
            node->right = insert(node->right, student);
        }
        else 
        {
            return node; // Копирование ID не допустимо
        }

        updateHeight(node);

        int balance = balanceFactor(node);

        if (balance > 1 && student.id < node->left->student.id)
        {
            return rotateRight(node);
        }

        if (balance < -1 && student.id > node->right->student.id) 
        {
            return rotateLeft(node);
        }

        if (balance > 1 && student.id > node->left->student.id) 
        {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (balance < -1 && student.id < node->right->student.id) 
        {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    void display(AVLNode* node, int indent) const
    {
        if (node) 
        {
            display(node->right, indent + 4);
            std::cout << std::string(indent, ' ') << node->student.id << ": " << node->student.name << std::endl;
            display(node->left, indent + 4);
        }
    }

    void clear(AVLNode* node)
    {
        if (node)
        {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

    Student* search(AVLNode* node, int id) const 
    {
        if (!node || node->student.id == id) 
        {
            return node ? &node->student : nullptr;
        }

        if (id < node->student.id) 
        {
            return search(node->left, id);
        }
        else
        {
            return search(node->right, id);
        }
    }

    AVLNode* minValueNode(AVLNode* node) 
    {
        AVLNode* current = node;
        while (current->left)
        {
            current = current->left;
        }
        return current;
    }

    AVLNode* remove(AVLNode* node, int id) 
    {
        if (!node)
        {
            return node;
        }

        if (id < node->student.id) 
        {
            node->left = remove(node->left, id);
        }
        else if (id > node->student.id) 
        {
            node->right = remove(node->right, id);
        }
        else 
        {
            if (!node->left || !node->right) 
            {
                AVLNode* temp = node->left ? node->left : node->right;

                if (!temp) {
                    temp = node;
                    node = nullptr;
                }
                else {
                    *node = *temp;
                }
                delete temp;
            }
            else 
            {
                AVLNode* temp = minValueNode(node->right);

                node->student = temp->student;

                node->right = remove(node->right, temp->student.id);
            }
        }

        if (!node)
        {
            return node;
        }

        updateHeight(node);

        int balance = balanceFactor(node);

        if (balance > 1 && balanceFactor(node->left) >= 0)
        {
            return rotateRight(node);
        }

        if (balance > 1 && balanceFactor(node->left) < 0)
        {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (balance < -1 && balanceFactor(node->right) <= 0)
        {
            return rotateLeft(node);
        }

        if (balance < -1 && balanceFactor(node->right) > 0)
        {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }
};


int main()
{
    setlocale(LC_ALL, "RU");
    AVLTree tree;
    int choice;

    do {
        std::cout << "=========Меню=========\n";
        std::cout << "1. Добавление студента\n";
        std::cout << "2. Вывод информации о студентах\n";
        std::cout << "3. Удаление информации о студентах\n";
        std::cout << "4. Поиск студента\n";
        std::cout << "5. Удаление студента\n";
        std::cout << "6. Выход из программы\n";
        std::cout << "Выберите действие: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            int id;
            std::string name, enrollmentDate, contactInfo;
            int course;
            std::cout << "Введите номер студенческого билета: ";
            std::cin >> id;
            std::cout << "Введите ФИО студента: ";
            std::cin.ignore();
            std::getline(std::cin, name);
            std::cout << "Введите курс: ";
            std::cin >> course;
            std::cout << "Введите дату зачисления: ";
            std::cin.ignore();
            std::getline(std::cin, enrollmentDate);
            std::cout << "Введите контактную информацию: ";
            std::getline(std::cin, contactInfo);
            tree.insert(Student(id, name, course, enrollmentDate, contactInfo));
            break;
        }
        case 2:
            tree.display();
            break;
        case 3:
            tree.clear();
            break;
        case 4: {
            int id;
            std::cout << "Введите номер студенческого билета для поиска: ";
            std::cin >> id;
            Student* student = tree.search(id);
            if (student) {
                std::cout << "Студент найден:\n";
                std::cout << "Номер студенческого билета: " << student->id << "\n";
                std::cout << "ФИО: " << student->name << "\n";
                std::cout << "Курс: " << student->course << "\n";
                std::cout << "Дата зачисления: " << student->enrollmentDate << "\n";
                std::cout << "Контактная информация: " << student->contactInfo << "\n";
            }
            else {
                std::cout << "Студент не найден.\n";
            }
            break;
        }
        case 5: {
            int id;
            std::cout << "Введите номер студенческого билета для удаления: ";
            std::cin >> id;
            tree.remove(id);
            break;
        }
        case 6:
            std::cout << "Выход из программы.\n";
            break;
        default:
            std::cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 6);
    return 0;
}

