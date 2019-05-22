//
//  main.cpp
//  MatrixDimaPonos
//
//  Created by MacBook Pro on 15/05/2019.
//  Copyright © 2019 MacBook Pro. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>






void enter(int**,int,int); // Функция ввода
int readFromFile(int **,int,int);
void change(int **, int,int);
void printMatrix(int **, int,int);
void writeToFile(int **, int,int);

int main()
{
    bool status = false;
    const uint size1 = 4;
    const uint size2 = 5;
    int** matrix = new int* [size1];
    for (int i = 0; i < (int)size1; i++)
    {
        matrix[i] = new int [size2];
    }
    
    while (true)
    {
        std::cout << "Choose: " << std::endl;
        std::cout << "1: Input the Matrix" << std::endl;
        std::cout << "2: Download Matrix from the file" << std::endl;
        std::cout << "3: Change the matrix" << std::endl;
        std::cout << "0: Exit" << std::endl;
        int x;
        std::cin >> x;
        
        if (x == 1)
        {
            enter(matrix,size1,size2);    // Выполняется функция ввода
            status = true;
        }
        else if (x == 2)
        {
            int statusOfError = readFromFile(matrix,size1,size2);
            if (statusOfError == 1)
            {
                getchar();
                return -1;
            }
            status = true;
        }
        else if(x == 3)
        {
            if (status == false)
            {
                std::cout << "You have to input the matrix" << std::endl;
            }
            
            else  change(matrix, size1, size2);
            
        }
        
        else if (x == 0)
        {
            break;    // Выход
        }
        
        
        
        
        
        else
        {
            std::cout << "Wrong input" << std::endl;
        }
    }
    
    if (status == true) writeToFile(matrix,size1,size2);
    
    for (int i = 0; i < (int)size1; i++)
    {
        delete  matrix[i];
        
    }
    
    delete[] matrix;
    getchar();
    return 0;
}

void  enter(int** matrix, int size1, int size2) // Функция ввода
{
    for (int i = 0; i< size1;i++)
    {
        for(int j = 0;j <size2;j++)
        {
            std::cout << "Input [" << i+1 << "][" << j+1 << "]:";
            std::cin >> *((*(matrix + i)) + j);
            std::cout << std::endl;
        }
    }
    
    printMatrix(matrix,size1,size2);
    
}

void change(int** matrix, int size1, int size2)
{
    int row = 0;
    int column = 0;
    int value = 0;
    std::cout << "The row of the elem is:";
    std::cin >> row;
    
    std::cout << std::endl << "The column of the elem is:";
    std::cin >> column;
    std::cout << std::endl << "The changed value is:";
    std::cin >> value;
    
    if ( row <= size1 && column <= size2 && row >= 1 && column >= 1)
    {
        
        (*((*(matrix + row - 1)) + column - 1)) = value;
        printMatrix(matrix,size1,size2);
    }
    else std::cout << "Wrong position of the elem" << std::endl;
}


void printMatrix(int** matrix, int size1, int size2)
{
    std::cout << "The Matrix is:" << std::endl << std::endl;
    
    for (int i = 0; i<size1;i++)
    {
        std::cout << std::setw(3) << *((*(matrix + i))) << " ";
        
        for(int j = 1;j<size2;j++)
        {
            std::cout << std::setw(3) << *((*(matrix + i)) + j) << " ";
        }
        
        std::cout << std::endl;
    }
}

int readFromFile(int** matrix, int size1, int size2)
{
    std::vector<int> elements;
    
    int tempValue = 0;
    std::ifstream file("input.txt");
    while (file >> tempValue ) elements.push_back(tempValue);
    
    if (file.bad())
    {
        std::cout << "I/O error\n";
        return 1;
    }
    if (!file.eof())
    {
        std::cout << "Invalid data\n";
        return 1;
    }
    
    if (elements.size() != size1*size2)
    {
        std::cout << "Wrong count of elements in file\n";
        return 1;
    }
    
    int countValue = 0;
    for (int i = 0; i< size1;i++)
    {
        for(int j = 0;j <size2;j++)
        {
            
            *((*(matrix + i)) + j) = *(&elements[0] + countValue);
            countValue++;
            
        }
    }
    printMatrix(matrix,size1,size2);
    
    return 0;
}

void writeToFile(int** matrix,int size1,int size2)
{
    std::ofstream file("output.txt");
    if (!file.is_open())
    {
        std::cout << "Can`t open the file\n";
    }
    else
    {
        for (int i = 0; i< size1;i++)
        {
            for(int j = 0;j <size2;j++)
            {
                
                file << (*((*(matrix + i)) + j)) << " ";
            }
            file << std::endl;
        }
    }
}
