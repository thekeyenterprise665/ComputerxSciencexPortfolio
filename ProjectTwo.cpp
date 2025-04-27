
Keyneisha Davion Mcnealey
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

// Class to hold course information
class Course {
public:
    std::string courseNumber;
    std::string courseName;
    std::vector<std::string> prerequisites;

    // Constructor for the Course class
    Course(std::string number, std::string name) : courseNumber(number), courseName(name) {}

     Course(std::string number, std::string name, const std::vector<std::string>& prereqs)
        : courseNumber(number), courseName(name), prerequisites(prereqs) {}

    // Function to print course information, including prerequisites
    void printCourseInfo() const {
        std::cout << courseNumber << ", " << courseName << std::endl;
        if (!prerequisites.empty()) {
            std::cout << "Prerequisites: ";
            for (size_t i = 0; i < prerequisites.size(); ++i) {
                std::cout << prerequisites[i];
                if (i < prerequisites.size() - 1) {
                    std::cout << ", ";
                }
            }
            std::cout << std::endl;
        } else {
            std::cout << "No prerequisites" << std::endl;
        }
    }

    // Overload the less-than operator for sorting courses
    bool operator<(const Course& other) const {
        return courseNumber < other.courseNumber;
    }
};

// Function to split a string by commas
std::vector<std::string> splitString(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Function to load course data from a file into a map
void loadCourseData(const std::string& filename, std::map<std::string, Course>& courses) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return; // Exit the function if the file cannot be opened
    }

    std::string line;
    while (std::getline(file, line)) {
        std::vector<std::string> tokens = splitString(line, ',');
        if (tokens.size() < 2) {
            std::cerr << "Error: Invalid data format in file. Skipping line: " << line << std::endl;
            continue; // Skip to the next line if the format is invalid
        }
        std::string courseNumber = tokens[0];
        std::string courseName = tokens[1];
        std::vector<std::string> prerequisites;
        for (size_t i = 2; i < tokens.size(); ++i) {
            if (!tokens[i].empty()) { // Only add non-empty prerequisites
                 prerequisites.push_back(tokens[i]);
            }
        }
        // Check if the course number already exists.
        if (courses.find(courseNumber) != courses.end()) {
            std::cerr << "Error: Duplicate course number " << courseNumber << ". Skipping." << std::endl;
        }
        else{
           courses[courseNumber] = Course(courseNumber, courseName, prerequisites);
        }
    }
    file.close();
    std::cout << "Data loaded successfully." << std::endl;
}

// Function to print an alphanumeric list of all courses
void printCourseList(const std::map<std::string, Course>& courses) {
    if (courses.empty()) {
        std::cout << "No courses loaded." << std::endl;
        return;
    }
    std::vector<Course> courseList;
    for (const auto& pair : courses) {
        courseList.push_back(pair.second);
    }
    std::sort(courseList.begin(), courseList.end()); // Sort the courses

    std::cout << "Here is the course list:" << std::endl;
    for (const auto& course : courseList) {
        std::cout << course.courseNumber << ", " << course.courseName << std::endl;
    }
}

// Function to print the course title and prerequisites for a given course number
void printCourseInformation(const std::map<std::string, Course>& courses) {
    if (courses.empty()) {
        std::cout << "No courses loaded." << std::endl;
        return;
    }

    std::string courseNumber;
    std::cout << "Enter the course number: ";
    std::cin >> courseNumber;
    std::transform(courseNumber.begin(), courseNumber.end(), courseNumber.begin(), ::toupper); // Convert to uppercase

    auto it = courses.find(courseNumber);
    if (it != courses.end()) {
        it->second.printCourseInfo();
    } else {
        std::cout << "Course " << courseNumber << " not found." << std::endl;
    }
}

// Function to display the main menu
void displayMenu() {
    std::cout << "1. Load Data Structure" << std::endl;
    std::cout << "2. Print Course List" << std::endl;
    std::cout << "3. Print Course" << std::endl;
    std::cout << "9. Exit" << std::endl;
    std::cout << "What would you like to do? ";
}

int main() {
    std::map<std::string, Course> courses; // Use a map to store courses for efficient lookup
    int choice = 0;
    std::string filename;

    while (choice != 9) {
        displayMenu();
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cout << "Invalid input. Please enter a number." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            choice = 0; // Reset choice to redisplay menu
            continue;
        }
        switch (choice) {
            case 1:
                std::cout << "Enter the filename: ";
                std::cin >> filename;
                loadCourseData(filename, courses);
                break;
            case 2:
                printCourseList(courses);
                break;
            case 3:
                printCourseInformation(courses);
                break;
            case 9:
                std::cout << "Exiting program." << std::endl;
                break;
            default:
                std::cout << choice << " is not a valid option." << std::endl;
        }
    }
    return 0;
}

