#include"Stack.h"

#include <iostream>


int main()
{
    try {
        // 1. Тестирование создания стека
        std::cout << "=== Создание стеков ===" << std::endl;
        TStack<int> stack1; // пустой стек
        TStack<int> stack2(5); // стек размером 5

        std::cout << "stack1 размер: " << stack1.GetLen() << std::endl;
        std::cout << "stack2 размер: " << stack2.GetLen() << std::endl;

        // 2. Тестирование добавления элементов
        std::cout << "\n=== Добавление элементов ===" << std::endl;
        stack2.Push(10);
        stack2.Push(20);
        stack2.Push(5);
        stack2.Push(15);
        stack2.Push(3);

        std::cout << "Добавлено 5 элементов в stack2" << std::endl;

        // 3. Тестирование поиска минимального элемента
        std::cout << "\n=== Поиск минимального элемента ===" << std::endl;
        int minVal = stack2.FindMin();
        std::cout << "Минимальный элемент: " << minVal << std::endl;

        // 4. Тестирование извлечения элементов
        std::cout << "\n=== Извлечение элементов ===" << std::endl;
        std::cout << "Извлечен: " << stack2.Pop() << std::endl;
        std::cout << "Извлечен: " << stack2.Pop() << std::endl;
        std::cout << "Осталось элементов: " << stack2.GetLen() << std::endl;

        // 5. Тестирование сохранения в файл
        std::cout << "\n=== Сохранение в файл ===" << std::endl;
        stack2.SaveToFile("stack_data.txt");
        std::cout << "Стек сохранен в файл 'stack_data.txt'" << std::endl;

        // 6. Тестирование загрузки из файла
        std::cout << "\n=== Загрузка из файла ===" << std::endl;
        TStack<int> stack3;
        stack3.LoadFromFile("stack_data.txt");
        std::cout << "Загружен стек размером: " << stack3.GetLen() << std::endl;

        // 7. Проверка загруженных данных
        std::cout << "\n=== Проверка загруженных данных ===" << std::endl;
        minVal = stack3.FindMin();
        std::cout << "Минимальный элемент в загруженном стеке: " << minVal << std::endl;

        // 8. Тестирование операторов сравнения
        std::cout << "\n=== Операторы сравнения ===" << std::endl;
        TStack<int> stack4(stack2); // копирующий конструктор

        if (stack2 == stack4) {
            std::cout << "stack2 и stack4 равны" << std::endl;
        }

        if (stack2 != stack3) {
            std::cout << "stack2 и stack3 не равны" << std::endl;
        }

        // 9. Тестирование перемещающей семантики
        std::cout << "\n=== Перемещающая семантика ===" << std::endl;
        TStack<int> stack5(std::move(stack4));
        std::cout << "stack5 размер после перемещения: " << stack5.GetLen() << std::endl;

        // 10. Тестирование исключений
        std::cout << "\n=== Тестирование исключений ===" << std::endl;
        try {
            TStack<int> emptyStack;
            emptyStack.Pop(); // попытка извлечь из пустого стека
        }
        catch (const std::exception& e) {
            std::cout << "Поймано исключение: " << e.what() << std::endl;
        }

        try {
            TStack<int> fullStack(2);
            fullStack.Push(1);
            fullStack.Push(2);
            fullStack.Push(3); // попытка добавить в полный стек
        }
        catch (const std::exception& e) {
            std::cout << "Поймано исключение: " << e.what() << std::endl;
        }

        // 11. Простая версия сохранения/загрузки
        std::cout << "\n=== Простая версия файловых операций ===" << std::endl;
        stack2.SaveToFile("stack_simple.txt");
        std::cout << "Стек сохранен простым методом" << std::endl;

        TStack<int> stack6;
        stack6.LoadFromFile("stack_simple.txt");
        std::cout << "Загружен стек размером: " << stack6.GetLen() << std::endl;

        std::cout << "\n=== Все тесты завершены успешно ===" << std::endl;

    }
    catch (const std::exception& e) 
    {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
