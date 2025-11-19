#include "TStack.h"

#include <gtest.h>

// Тесты для конструкторов
TEST(TStackTest, DefaultConstructor) {
    TStack<int> stack;
    EXPECT_EQ(stack.GetLen(), 0);
    EXPECT_TRUE(stack.IsEmpty());
}

TEST(TStackTest, ParameterizedConstructor) {
    TStack<int> stack(5);
    EXPECT_EQ(stack.GetLen(), 5);
    EXPECT_TRUE(stack.IsEmpty());
}

TEST(TStackTest, ParameterizedConstructorNegativeSize) {
    EXPECT_THROW(TStack<int> stack(-1), std::invalid_argument);
}

TEST(TStackTest, CopyConstructor) {
    TStack<int> stack1(3);
    stack1.Push(1);
    stack1.Push(2);

    TStack<int> stack2(stack1);
    EXPECT_EQ(stack2.GetLen(), 3);
    EXPECT_FALSE(stack2.IsEmpty());
}

TEST(TStackTest, MoveConstructor) {
    TStack<int> stack1(2);
    stack1.Push(10);
    stack1.Push(20);

    TStack<int> stack2(std::move(stack1));
    EXPECT_EQ(stack2.GetLen(), 2);
    EXPECT_FALSE(stack2.IsEmpty());
    // stack1 должен быть в валидном, но пустом состоянии
}

// Тесты для методов управления стеком
TEST(TStackTest, PushAndPop) {
    TStack<int> stack(3);

    stack.Push(10);
    stack.Push(20);
    stack.Push(30);

    EXPECT_EQ(stack.Pop(), 30);
    EXPECT_EQ(stack.Pop(), 20);
    EXPECT_EQ(stack.Pop(), 10);
    EXPECT_TRUE(stack.IsEmpty());
}

TEST(TStackTest, PushFullStack) {
    TStack<int> stack(2);
    stack.Push(1);
    stack.Push(2);

    EXPECT_THROW(stack.Push(3), std::logic_error);
}

TEST(TStackTest, PopEmptyStack) {
    TStack<int> stack;
    EXPECT_THROW(stack.Pop(), std::logic_error);
}

TEST(TStackTest, IsEmptyAndIsFull) {
    TStack<int> stack(2);
    EXPECT_TRUE(stack.IsEmpty());
    EXPECT_FALSE(stack.isFull());

    stack.Push(1);
    EXPECT_FALSE(stack.IsEmpty());
    EXPECT_FALSE(stack.isFull());

    stack.Push(2);
    EXPECT_FALSE(stack.IsEmpty());
    EXPECT_TRUE(stack.isFull());
}

// Тесты для операторов
TEST(TStackTest, AssignmentOperator) {
    TStack<int> stack1(3);
    stack1.Push(1);
    stack1.Push(2);

    TStack<int> stack2;
    stack2 = stack1;

    EXPECT_EQ(stack2.GetLen(), 3);
    EXPECT_FALSE(stack2.IsEmpty());
}

TEST(TStackTest, MoveAssignmentOperator) {
    TStack<int> stack1(2);
    stack1.Push(10);
    stack1.Push(20);

    TStack<int> stack2;
    stack2 = std::move(stack1);

    EXPECT_EQ(stack2.GetLen(), 2);
    EXPECT_FALSE(stack2.IsEmpty());
}

TEST(TStackTest, EqualityOperator) {
    TStack<int> stack1(3);
    stack1.Push(1);
    stack1.Push(2);

    TStack<int> stack2(stack1);

    EXPECT_TRUE(stack1 == stack2);

    stack2.Pop();
    EXPECT_FALSE(stack1 == stack2);
}

TEST(TStackTest, InequalityOperator) {
    TStack<int> stack1(2);
    stack1.Push(1);

    TStack<int> stack2(2);
    stack2.Push(2);

    EXPECT_TRUE(stack1 != stack2);
}

// Тесты для поиска минимального элемента
TEST(TStackTest, FindMin) {
    TStack<int> stack(5);
    stack.Push(10);
    stack.Push(5);
    stack.Push(20);
    stack.Push(3);
    stack.Push(15);

    EXPECT_EQ(stack.FindMin(), 3);
}

TEST(TStackTest, FindMinEmptyStack) {
    TStack<int> stack;
    EXPECT_THROW(stack.FindMin(), std::logic_error);
}

TEST(TStackTest, FindMinSingleElement) {
    TStack<int> stack(1);
    stack.Push(42);
    EXPECT_EQ(stack.FindMin(), 42);
}

// Тесты для работы с файлами
TEST(TStackTest, SaveAndLoadToFile) {
    TStack<int> stack1(4);
    stack1.Push(100);
    stack1.Push(200);
    stack1.Push(300);

    stack1.SaveToFile("test_stack.txt");

    TStack<int> stack2;
    stack2.LoadFromFile("test_stack.txt");

    EXPECT_FALSE(stack2.IsEmpty());
    EXPECT_EQ(stack2.GetLen(), 3); // Размер должен быть равен количеству элементов
}

TEST(TStackTest, SaveEmptyStackToFile) {
    TStack<int> stack1;
    stack1.SaveToFile("empty_stack.txt");

    TStack<int> stack2;
    stack2.LoadFromFile("empty_stack.txt");

    EXPECT_TRUE(stack2.IsEmpty());
}

TEST(TStackTest, LoadFromNonExistentFile) {
    TStack<int> stack;
    EXPECT_THROW(stack.LoadFromFile("non_existent_file.txt"), std::runtime_error);
}



// Тесты для операторов ввода/вывода
TEST(TStackTest, StreamOutputOperator) {
    TStack<int> stack(2);
    stack.Push(1);
    stack.Push(2);

    std::stringstream ss;
    ss << stack;

    std::string output = ss.str();
    EXPECT_FALSE(output.empty());
    EXPECT_NE(output.find("TStack"), std::string::npos);
}

TEST(TStackTest, StreamInputOperator) {
    std::stringstream ss;
    ss << "3 1 2 3"; // размер 3, элементы 1, 2, 3

    TStack<int> stack;
    ss >> stack;

    EXPECT_EQ(stack.GetLen(), 3);
    EXPECT_FALSE(stack.IsEmpty());
    EXPECT_EQ(stack.FindMin(), 1);
}

// Тесты для методов Resize и SetData
TEST(TStackTest, Resize) 
{
    TStack<int> stack(2);
    stack.Push(1);
    stack.Push(2);

    stack.Resize(4);
    EXPECT_EQ(stack.GetLen(), 4);
    EXPECT_FALSE(stack.IsEmpty());

    // Можем добавить еще элементы
    stack.Push(3);
    stack.Push(4);
    EXPECT_TRUE(stack.isFull());
}

TEST(TStackTest, ResizeToZero) {
    TStack<int> stack(2);
    stack.Push(1);
    stack.Push(2);

    stack.Resize(0);
    EXPECT_EQ(stack.GetLen(), 0);
    EXPECT_TRUE(stack.IsEmpty());
}

TEST(TStackTest, ResizeNegative) {
    TStack<int> stack;
    EXPECT_THROW(stack.Resize(-1), std::invalid_argument);
}

// Тест на самоприсваивание
TEST(TStackTest, SelfAssignment) {
    TStack<int> stack(2);
    stack.Push(1);
    stack.Push(2);

    stack = stack; // самоприсваивание
    // Не должно быть краша или утечек памяти
    EXPECT_FALSE(stack.IsEmpty());
}
