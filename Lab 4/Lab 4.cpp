#include <iostream>
#include <vector>

// Структура узла дерева
struct TreeNode
{
    int value;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

// Функция для вставки узла в дерево
TreeNode* insert(TreeNode* root, int value)
{
    if (root == nullptr) 
    {
        return new TreeNode(value);
    }
    if (value < root->value) 
    {
        root->left = insert(root->left, value);
    }
    else
    {
        root->right = insert(root->right, value);
    }
    return root;
}

// Функция для прямого обхода дерева
void preOrderTraversal(TreeNode* root)
{
    if (root != nullptr) {
        std::cout << root->value << " ";
        preOrderTraversal(root->left);
        preOrderTraversal(root->right);
    }
}

// Функция для симметричного обхода дерева
void inOrderTraversal(TreeNode* root)
{
    if (root != nullptr) {
        inOrderTraversal(root->left);
        std::cout << root->value << " ";
        inOrderTraversal(root->right);
    }
}

// Функция для обратного обхода дерева
void postOrderTraversal(TreeNode* root)
{
    if (root != nullptr) {
        postOrderTraversal(root->left);
        postOrderTraversal(root->right);
        std::cout << root->value << " ";
    }
}

// Функция для ввода элементов множества
std::vector<int> inputSet()
{
    int n;
    std::cout << "Введите количество элементов множества: ";
    std::cin >> n;
    std::vector<int> set(n);
    std::cout << "Введите элементы множества: ";
    for (int i = 0; i < n; ++i) {
        std::cin >> set[i];
    }
    return set;
}

// Функция для построения дерева на основе множества
TreeNode* buildTree(const std::vector<int>& set)
{
    TreeNode* root = nullptr;
    for (int value : set) {
        root = insert(root, value);
    }
    return root;
}

int main() 
{
    setlocale(LC_ALL, "Rus");
    std::vector<int> set;
    TreeNode* root = nullptr;
    int choice;

    while (true) 
    {
        std::cout << "==========Меню==========\n";
        std::cout << "1. Ввод элементов множества\n";
        std::cout << "2. Построение и вывод на экран бинарного дерева\n";
        std::cout << "3. Выход из программы\n";
        std::cout << "Выберите пункт меню: ";
        std::cin >> choice;

        switch (choice) 
        {
        case 1:
            set = inputSet();
            break;
        case 2:
            if (set.empty()) 
            {
                std::cout << "Сначала введите элементы множества.\n";
            }
            else 
            {
                root = buildTree(set);
                std::cout << "Прямой обход: ";
                preOrderTraversal(root);
                std::cout << "\n";
                std::cout << "Симметричный обход: ";
                inOrderTraversal(root);
                std::cout << "\n";
                std::cout << "Обратный обход: ";
                postOrderTraversal(root);
                std::cout << "\n";
            }
            break;
        case 3:
            return 0;
        default:
            std::cout << "Неверный выбор. Попробуйте снова.\n";
        }
    }

    return 0;
}
