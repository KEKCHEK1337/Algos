#include <iostream>
#include <vector>

class Item                                  //реализация класса Item
{
private:
    std::string name;
    int price;
    int code;

public:
    Item(std::string name, int price, int code)
    {
        this->name = name;
        this->price = price;
        this->code = code;
    }

    void setName(std::string name)          //реализация методов класса Item
    {
        this->name = name;
    }
        
    void setPrice(int price)
    {
        this->price = price;
    }

    void setCode(int code)
    {
        this->code = code;
    }

    std::string getName()
    {
        return name;
    }

    int getPrice()
    {
        return price;
    }

    int getCode()
    {
        return code;
    }

    void printItem()
    {
        std::cout << this->name << '\n';
        std::cout << this->price << '\n';
        std::cout << this->code << '\n';
    }

};

class Items                                                            //реализация класса Items
{
private:
    std::vector<Item> items;
public:
    void addItem(Item item)                                            //Добавление экземпляра в вектор Items
    {
        items.push_back(item);
    }

    void printItems()                                                  //Вывод элементов из вектора
    {
        std::cout << "================" << std::endl;
        for (std::vector<Item>::iterator it = items.begin(); it != items.end(); ++it)
        {
            (*it).printItem();
            std::cout << "================" << std::endl;
        }
    }

    void insertionSort()                                                //сортировка вставками
    {
        int countersr = 0;
        int countersw = 0;
        for (int step = 1; step < items.size(); step++)
        {
            Item key = items[step];
            int j = step - 1;

            // Compare key with each element on the left of it until an element smaller than
            // it is found.
            // For descending order, change key<array[j] to key>array[j].
            while (j >= 0 && key.getPrice() < items[j].getPrice())
            {
                countersr++;
                items[j + 1] = items[j];
                countersw++;
                --j;
            }
            items[j + 1] = key;
        }
        std::cout << "Колчество сравнений: " << countersr << std::endl;             //вывод кол-ва сравнений
        std::cout << "Колчество перестановок: " << countersw << std::endl;          //вывод кол-ва обменов
    }

     void bubbleSort()                                          //реализация метода сортировки пузырьком
    {
        int countersr = 0;
        int countersw = 0;

        int itemslength = items.size();

        while (itemslength--)
        {
            bool swapped = false;

            for (int i = 0; i < itemslength; i++)
            {
                countersr++;
                if (items[i].getPrice() > items[i + 1].getPrice())
                {
                    std::swap(items[i], items[i + 1]);
                    swapped = true;
                    countersw++;
                }
            }

            if (swapped == false)
                break;
        }
        std::cout << "Колчество сравнений: " << countersr << std::endl;
        std::cout << "Колчество перестановок: " << countersw << std::endl;
    }

     void shellSort()                                                   //реализация сортировки Шелла
     {
         int countersr = 0;
         int countersw = 0;

         int itemslength = items.size();

         for (int step =  itemslength / 2; step > 0; step /= 2)
         {
             for (int i = step; i < itemslength; i += 1)
             {
                 int j = i;
                 while (j >= step)
                 {
                     countersr++;
                     if (items[j - step].getPrice() > items[j].getPrice())
                     {
                         std::swap(items[j], items[j - step]);
                         countersw++;
                     }
                     j -= step;
                 }
             }
         }
         std::cout << "Колчество сравнений: " << countersr << std::endl;
         std::cout << "Колчество перестановок: " << countersw << std::endl;
     }

     void heapify(int root, int lenghtlist, int& countersr, int& countersw)             //реализация метода пирамидальной сортировки
     {
         int largest = root;
         int l = 2 * root + 1;
         int r = 2 * root + 2;

         // Сравниваем левый дочерний элемент с корнем
         if (l < lenghtlist)
         {
             countersr++; // Увеличиваем счетчик сравнений
             if (items[l].getPrice() > items[largest].getPrice())
             {
                 largest = l;
             }
         }

         // Сравниваем правый дочерний элемент с корнем
         if (r < lenghtlist)
         {
             countersr++; // Увеличиваем счетчик сравнений
             if (items[r].getPrice() > items[largest].getPrice())
             {
                 largest = r;
             }
         }

         // Если самый большой элемент не корень
         if (largest != root)
         {
             std::swap(items[root], items[largest]);
             countersw++; // Увеличиваем счетчик обменов
             heapify(largest, lenghtlist, countersr, countersw);
         }
     }

     void heapSort()
     {
         int countersw = 0;
         int countersr = 0;

         int listLength = items.size();

         // Построение кучи (heap)
         for (int i = listLength / 2 - 1; i >= 0; i--)
         {
             heapify(i, listLength, countersr, countersw);
         }

         // Извлечение элементов из кучи
         for (int i = listLength - 1; i >= 0; i--)
         {
             std::swap(items[0], items[i]);
             countersw++; // Увеличиваем счетчик обменов
             heapify(0, i, countersr, countersw);
         }

         std::cout << "Колчество сравнений: " << countersr << std::endl;
         std::cout << "Колчество перестановок: " << countersw << std::endl;
     }

     void linearSearch(int price)                                   //реализация прямого поиска
     {
         bool flag = false;
         for (int i = 0; i < items.size(); ++i) 
         {
             if (items[i].getPrice() == price)
             {
                 std::cout << "=====Найден элемент=====" << std::endl; // Вывод найденого элемента
                 std::cout << "Название: " << items[i].getName() << std::endl;
                 std::cout << "Цена: " << items[i].getPrice() << std::endl;
                 std::cout << "Код: " << items[i].getCode() << std::endl;
                 std::cout << "=====================" << std::endl;
                 flag = true;
             }
         }
         if (flag = false)
         {
             std::cout << "Такой товар не найден" << std::endl;
         }
     }

     void binarySearch(int price)                               // реализация бинарного поиска
     {
         int left = 0;
         int right = items.size() - 1;
         bool flag = false;

         while (left <= right) 
         {
             int mid = left + (right - left) / 2;

             if (items[mid].getPrice() == price) 
             {
                 std::cout << "=====Товар найден=====" << std::endl; // Элемент найден
                 std::cout << "Название: " << items[mid].getName() << std::endl;
                 std::cout << "Код :" << items[mid].getCode() << std::endl;
                 std::cout << "Цена: " << items[mid].getPrice() << std::endl;
                 std::cout << "=============" << std::endl;
                 flag = true;
             }

             if (items[mid].getCode() < price) 
             {
                 left = mid + 1; // Игнорируем левую половину
             }
             else 
             {
                 right = mid - 1; // Игнорируем правую половину
             }

             if (flag = false)
             {
                 std::cout << "Товар не найден" << std::endl;
             }
         }

     }
};

int main()
{
    setlocale(LC_ALL, "Rus");

    int choice;                                         // Обьявление переменных
    bool flag = true;
    std::string name;
    int code, price;
    Items goods_save;
    Items goods;
    Items goods_rec;
    int cost;

    do
    {
        std::cout << "============Меню===============" << std::endl;                    //создания меню через конструкцию switch
        std::cout << "1. Ввести товары" << std::endl;
        std::cout << "2. Сортировать товары по возрастанию цены" << std::endl;
        std::cout << "3. Вывод списка товаров" << std::endl;
        std::cout << "4. Перезапись" << std::endl;
        std::cout << "5. Поиск элемента" << std::endl;
        std::cout << "6. Выход" << std::endl;

        std::cin >> choice;
        switch (choice)
        {

        case 1:
            std::cout << "Введите код товара, название и цену, если хотите остановить ввод товаров, введите код товара 0" << std::endl;
            while (flag = true)
            {
                std::cin >> code;
                if (code == 0)
                {
                    flag = false;
                    break;
                }
                else
                {
                    std::cin >> name;
                    std::cin >> price;
                    std::cout << "================" << std::endl;
                    Item product(name, price, code);
                    goods_save.addItem(product);
                }
            }
            goods = goods_save;
            goods_rec = goods_save;
            break;

        case 2:
            do
            {
                std::cout << "Выберите метод которым хотите отсортировать товары" << std::endl;
                std::cout << "1. Обменом" << std::endl;
                std::cout << "2. Вставками" << std::endl;
                std::cout << "3. Шелла" << std::endl;
                std::cout << "4. Пирамидальным" << std::endl;
                std::cout << "5. Назад" << std::endl;

                std::cin >> choice;
                switch (choice)
                {
                case 1:
                    std::cout << "При сортировке обменом: " << std::endl;
                    goods_save.bubbleSort();
                    break;

                case 2:
                    std::cout << "При сортировке  вставками" << std::endl;
                    goods_save.insertionSort();
                    break;
                case 3:
                    std::cout << "При сортировке Шелла" << std::endl;
                    goods_save.shellSort();
                    break;
                case 4:
                    std::cout << "При Пирамидальной сортировке" << std::endl;
                    goods_save.heapSort();
                    break;
                }
            } while (choice != 5);
            {
                break;
            }

        case 3:
            do
            {
                std::cout << "Выберите какой список хотите вывести" << std::endl;
                std::cout << "1. Исходный" << std::endl;
                std::cout << "2. Отсортированный" << std::endl;
                std::cout << "3. Назад" << std::endl;

                std::cin >> choice;
                switch (choice)
                {
                case 1:
                    goods.printItems();
                    break;
                case 2:
                    goods_save.printItems();
                    break;
                }
            } while (choice != 3);
            {
                break;
            }

        case 4:
            goods_save = goods_rec;
            break;

        case 5:
            do
            {
                std::cout << "Выберите как хотите осущетвить поиск товара по цене" << std::endl;
                std::cout << "1. Прямой поиск" << std::endl;
                std::cout << "2. Бинарный поиск" << std::endl;
                std::cout << "3. назад" << std::endl;

                std::cin >> choice;
                switch (choice)
                {
                case 1:
                    std::cout << "Введите стоимость товара" << std::endl;
                    std::cin >> cost;
                    goods_save.linearSearch(cost);
                    break;
                case 2:
                    std::cout << "Введите стоимость товара" << std::endl;
                    std::cin >> cost;
                    goods_save.binarySearch(cost);
                    break;
                }
            } while (choice != 3);
            {
                break;
            }
        }
    } while (choice != 6);
    {
        return 0;
    }
}