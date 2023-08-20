// Marrero_ProjectTwo.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Name: Brandon Marrero
// CS300 - Project Two
// 08-13-2023

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// Define a Course struct to store course information
struct Course {
    string courseNumber;
    string courseTitle;
    string prerequisite1;
    string prerequisite2;
    string prerequisite3;
    Course* left;
    Course* right;
};

// Define a BinarySearchTree class to store Course objects
class BinarySearchTree {
public:
    BinarySearchTree() {
        root = nullptr;
    }
    void insert(Course* course) {
        root = insertHelper(root, course);
    }
    void inorderTraversal() {
        inorderTraversalHelper(root);
    }
    Course* search(string courseNumber) {
        return searchHelper(root, courseNumber);
    }
private:
    Course* root;
    Course* insertHelper(Course* node, Course* course) {
        if (node == nullptr) {
            node = course;
        }
        else if (node->courseNumber > course->courseNumber) {
            node->left = insertHelper(node->left, course);
        }
        else {
            node->right = insertHelper(node->right, course);
        }
        return node;
    }
    void inorderTraversalHelper(Course* node) {
        if (node != nullptr) {
            inorderTraversalHelper(node->left);
            cout << node->courseNumber << ", " << node->courseTitle << endl;
            inorderTraversalHelper(node->right);
        }
    }
    Course* searchHelper(Course* node, string courseNumber) {
        if (node == nullptr || node->courseNumber == courseNumber) {
            return node;
        }
        else if (node->courseNumber > courseNumber) {
            return searchHelper(node->left, courseNumber);
        }
        else {
            return searchHelper(node->right, courseNumber);
        }
    }
};

// Define a function to parse a line of input and create a Course object
Course* parseCourse(string line) {
    Course* course = new Course;
    size_t commaPos1 = line.find(",");
    size_t commaPos2 = line.find(",", commaPos1 + 1);
    size_t commaPos3 = line.find(",", commaPos2 + 1);
    course->courseNumber = line.substr(0, commaPos1);
    course->courseTitle = line.substr(commaPos1 + 1, commaPos2 - commaPos1 - 1);
    course->prerequisite1 = line.substr(commaPos2 + 1, commaPos3 - commaPos2 - 1); // Fix prerequisites
    course->prerequisite2 = line.substr(commaPos3 + 1); // Fix prerequisites
    course->prerequisite3 = ""; // Initialize prerequisite3
    course->left = nullptr;
    course->right = nullptr;
    return course;
}

// Function to load data structure from a file
void loadDataStructure(BinarySearchTree& courseBST) {
    ifstream inputFile("courses.txt");
    if (!inputFile.is_open()) {
        cout << "Unable to open the file." << endl;
        return;
    }

    string line;
    while (getline(inputFile, line)) {
        Course* course = parseCourse(line);
        courseBST.insert(course);
    }

    inputFile.close();
    cout << "Data loaded successfully." << endl;
}

// Function to print the course list in alphanumeric order
void printCourseList(BinarySearchTree& courseBST) {
    courseBST.inorderTraversal();
}

// Function to print the course information
void printCourseInfo(BinarySearchTree& courseBST) {
    string courseNumber;
    cout << "What course do you want to know about? ";
    cin >> courseNumber;

    Course* course = courseBST.search(courseNumber);

    if (course != nullptr) {
        cout << course->courseNumber << ", " << course->courseTitle << endl;
        cout << "Prerequisites: ";
        if (!course->prerequisite1.empty()) {
            cout << course->prerequisite1;
            if (!course->prerequisite2.empty() || !course->prerequisite3.empty()) {
                cout << ", ";
            }
        }
        if (!course->prerequisite2.empty()) {
            cout << course->prerequisite2;
            if (!course->prerequisite3.empty()) {
                cout << ", ";
            }
        }
        if (!course->prerequisite3.empty()) {
            cout << course->prerequisite3;
        }
        cout << endl;
    }
    else {
        cout << "Course not found." << endl;
    }
}


// Function to display the menu and handle user input
void displayMenu(BinarySearchTree& courseBST) {
    int choice = 0;
    while (choice != 9) {
        cout << endl;
        cout << "1. Load Data Structure." << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course." << endl;
        cout << "9. Exit" << endl;
        cout << endl;
        cout << "What would you like to do? ";
        cin >> choice;

        // If input fails (non-numeric input)
        if (cin.fail()) {
            cout << "Invalid input. Please enter a valid numeric choice." << endl;
            cin.clear(); // Clear the fail state
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
            continue;
        }

        switch (choice) {
        case 1:
            loadDataStructure(courseBST);
            break;
        case 2:
            printCourseList(courseBST);
            break;
        case 3:
            printCourseInfo(courseBST);
            break;
        case 9:
            cout << "Thank you for using the course planner!" << endl;
            break;
        default:
            cout << choice << " is not a valid option." << endl;
            break;
        }
    }
}


int main() {
    // Create a BinarySearchTree to store the courses
    BinarySearchTree courseBST;
    // Display the menu and handle user input
    displayMenu(courseBST);

    return 0;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
