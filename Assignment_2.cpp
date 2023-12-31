// Assignment 2.cpp : 
// 24/02/23
// Student Id: 10138372
// A program which outputs the standard deviation, average grade and standard error for all years and
// chosen year from a selected .dat file. It also prints the data for chosen year.

#include <iostream>
#include<iomanip>
#include<fstream>
#include<cmath>
#include<vector>
#include<string>
#include <numeric>
#include <sstream>
#include<algorithm>

// Declare function prototypes for average, standard deviation, and standard error.
template<typename T>
double calculate_average(std::vector<T> const& v);
template<typename D>
double calculate_standard_deviation(std::vector<D> const& v, double avg);
template<typename F>
double calculate_standard_error(std::vector<F> const& v, double stand);
// Declaring result vector as a global variable
std::vector<std::string> result;
// Function to combine columns with "PHYS" added to the start of the first column
void combine_columns(std::vector<std::pair<int, std::string>> const& v) {
    // Clear the result vector before adding new elements
    result.clear(); 
    // Loop through the input vector and append "PHYS" to the course ID
    for (auto const& d : v) {
        result.push_back("PHYS" + std::to_string(d.first) + " " + d.second);
    }
}
int main() {
    // Declare variables
    std::vector<std::pair<float, std::pair<int, std::string>>> data;
    float grade;
    int course_id;
    int input;
    int year;
    std::string data_file;
    std::string course_name;
    std::vector<float> grade_list;
    std::vector<std::string> combined_data;
    std::vector<float> grades;
    std::ifstream file("courselist.dat");
    // Check if the file was opened successfully
    if (!file) {
        std::cerr << "Error: Was unable to open the file" << std::endl;
        return 1;
    }
    // Read the data from the file into the vector
    while (file >> grade) {
        file >> course_id;
        // file.ignore();
        getline(file, course_name);
        data.push_back(make_pair(grade, make_pair(course_id, course_name)));
        grade_list.push_back(grade);
    }
    // Close the file
    file.close();

    // Get user input to sort the data via alphabetical order or by course code
    std::cout << "Do you want to sort the data via alphabetical order or by course code (1 for alphabetical order or 0 for course code): ";
    std::cin >> input;
    // Sort the data by the chosen criteria
    if (input==1)
    std::sort(data.begin(), data.end(),
        [](const auto& lhs, const auto& rhs) {
            return lhs.second.second < rhs.second.second;
        });
    else
    std::sort(data.begin(), data.end(),
        [](const auto& lhs, const auto& rhs) {
            return lhs.second.first < rhs.second.first;
        });
    // Calculates the average grade, standard deviation and standard error for all years.
    double average_all = calculate_average(grade_list);
    double standard_deviation_all = calculate_standard_deviation(grade_list, average_all);
    double standard_error_all = calculate_standard_error(grade_list, standard_deviation_all);
    std::cout << "The average for all years is " << std::setprecision(3)  << average_all << " +/- " << std::setprecision(2)  << standard_error_all << std::endl;
    std::cout << "The standard deviation for all years is " << std::setprecision(2) << standard_deviation_all << std::endl;
    std::cout << "The .dat file contains " << data.size()<< " data files." << std::endl;
    
    // Combine the columns with Phys added to the start of the first column
    for (auto& d : data) {
        std::ostringstream oss;
        oss << "Phys" << d.second.first << d.second.second;
        combined_data.push_back(oss.str());
    }
    // Get the year for the data selection
    std::cout << "Enter the year you would like to view (1-4): ";
    std::cin >> year;
    // Print out the data for the specified year
    std::copy_if(combined_data.begin(), combined_data.end(), std::ostream_iterator<std::string>(std::cout, "\n"),
        [year](const std::string& str) {
            return std::stoi(str.substr(4, 1)) == year;
        });
    // Segment the data for the specified year
    for (const auto& d : data) {
        int year_number = d.second.first;
        // Extract the first digit of the year
        int first_digit = year_number / 10000; 
        if (first_digit == year) {
            grades.push_back(d.first);
        }
    }
    // Calculates average grade, standard deviation and standard error for chosen year
    double average_grade_year = calculate_average(grades);
    double standard_deviation_grade = calculate_standard_deviation(grades, average_grade_year);
    double standard_error_year = calculate_standard_error(grades, standard_deviation_grade);
    // Output results for the chosen year
    std::cout << "The average grade for year " << year  << " is " << std::setprecision(3) << average_grade_year << " +/- " << std::setprecision(2) << standard_error_year << " and the standard deviation was " << std::setprecision(2) << standard_deviation_grade << "." << std::endl;
    return 0;
}

template<typename T>
double calculate_average(std::vector<T> const& v) {

    double sum = 0.0;
    for (const T& i : v) {
        sum += (double)i;
    }
    return sum / v.size();
}
template<typename D>
double calculate_standard_deviation(std::vector<D> const& v, double avg) {
    double var = 0.0;
    for (int i = 0; i < v.size(); ++i) {
        var += (v[i] - avg) * (v[i] - avg);
    }
    var /= v.size();
    return sqrt(var);
}
template<typename F>
double calculate_standard_error(std::vector<F> const& v, double stand) {
    return stand / sqrt(v.size());
}
