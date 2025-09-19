#include <iostream>
#include <string>
#include <cstring>  // strcpy, strlen

void addStudent(char* name, double gpa, char* names[], double gpas[], int& size, int capacity);
void updateGPA(double* gpaPtr, double newGpa);
void printStudent(const char* name, const double& gpa);
double averageGPA(const double gpas[], int size);

void addStudent(char* name, double gpa, char* names[], double gpas[], int& size, int capacity) {
    if (size >= capacity) throw "Full";
    names[size] = name;  
    gpas[size]  = gpa;
    ++size;
}

void updateGPA(double* gpaPtr, double newGpa) {
    *gpaPtr = newGpa;
}

void printStudent(const char* name, const double& gpa) {
    std::cout << name << ": " << gpa << std::endl;
}

double averageGPA(const double gpas[], int size) {
    if (size == 0) throw "Empty";
    double sum = 0.0;
    for (int i = 0; i < size; ++i) sum += gpas[i];
    return sum / static_cast<double>(size);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: ./program <capacity>" << std::endl;
        return 1;
    }

    const int capacity = std::stoi(argv[1]);
    char** names = new char*[capacity];
    double* gpas = new double[capacity];
    int size = 0;
    for (int i = 0; i < capacity; ++i) names[i] = nullptr;

    int choice = 0;
    do {
        std::cout << "Menu:\n";
        std::cout << "1. Add student\n";
        std::cout << "2. Update GPA\n";
        std::cout << "3. Print all students\n";
        std::cout << "4. Compute average GPA\n";
        std::cout << "5. Quit\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string s; double g;
                std::cout << "Enter name and GPA: ";
                std::cin >> s >> g;
                char* c = new char[s.size() + 1];
                std::strcpy(c, s.c_str());
                try {
                    addStudent(c, g, names, gpas, size, capacity);
                } catch (const char* msg) {
                    std::cout << msg << std::endl;
                    delete[] c; // 失败时回收
                }
                break;
            }
            case 2: {
                int idx; double ng;
                std::cout << "Enter index and new GPA: ";
                std::cin >> idx >> ng;
                if (idx < 0 || idx >= size) {
                    std::cout << "Bad index" << std::endl;
                } else {
                    updateGPA(&gpas[idx], ng);
                }
                break;
            }
            case 3: {
                for (int i = 0; i < size; ++i) {
                    printStudent(names[i], gpas[i]);
                }
                break;
            }
            case 4: {
                try {
                    double avg = averageGPA(gpas, size);
                    std::cout << "Average=" << avg
                              << " rounded=" << static_cast<int>(avg) << std::endl;
                } catch (const char* msg) {
                    std::cout << msg << std::endl;
                }
                break;
            }
            case 5: {
                std::cout << "Goodbye!" << std::endl;
                break;
            }
            default: {
                std::cout << "Invalid choice" << std::endl;
            }
        }
    } while (choice != 5);

    // 释放内存
    for (int i = 0; i < size; ++i) delete[] names[i];
    delete[] names;
    delete[] gpas;
    return 0;
}
