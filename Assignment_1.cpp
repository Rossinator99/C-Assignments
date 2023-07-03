/*
10/02/23
Student Number: 10138372
Assignment 1
// Program that calculates transition energy using simple Bohr formula
*/
#include<iostream>
#include<math.h>
#include<iomanip> 

// Constants for energy calculation
const double energy_constant = 13.6;
const double ev_to_j = 1.60218 * pow(10, -19);
// Functions to check input validity
bool check_conditions(int initial_quantum_number, int final_quantum_number, int atomic_number);
// Functions for energy calcluation in eV
double calculate_energy_in_ev(int initial_quantum_number, int final_quantum_number, int atomic_number);
// Functions for energy calcluations in Joules
double calculate_energy_in_joules(int initial_quantum_number, int final_quantum_number, int atomic_number);

int main()
{
    // Variable used for repeating the process
    std::string response;
    do {
        int atomic_number;
        int initial_quantum_number;
        int final_quantum_number;
        std::string convert_to_joules;
        std::cout << "Enter the atomic number: ";
        std::cin >> atomic_number;
        if (std::cin.fail()) {
            std::cout << "Error: Atomic number has to be an integer." << std::endl;
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            break;
        }
        std::cout << "Enter the initial quantum number: ";
        std::cin >> initial_quantum_number;
        if (std::cin.fail()) {
            std::cout << "Error: Initial quantum number has to be an integer." << std::endl;
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            break;
        }
        std::cout << "Enter the final quantum number: ";
        std::cin >> final_quantum_number;
        if (std::cin.fail()) {
            std::cout << "Error: Final quantum number has to be an integer." << std::endl;
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            break;
        }
        try
        {
            // Checks input validity by calling check conditions
            if (!check_conditions(initial_quantum_number, final_quantum_number, atomic_number))
            {
                // Throws an exception with a message "Invalid input" if the inputs are invalid
                throw std::invalid_argument("Invalid input");
            }
            std::cout << "Do you want to convert the energy from ev to joules? (y for yes, n for no): ";
            std::cin >> convert_to_joules;
            // Loops until valid input
            while (convert_to_joules.length() != 1 || convert_to_joules[0] != 'y' && convert_to_joules[0] != 'n') {
                std::cout << convert_to_joules << " is not a valid option. Try again" << std::endl;
                std::cout << "Do you want to convert the energy from ev to joules? (y for yes, n for no): " << std::endl;
                std::cin >> convert_to_joules;
            }
            // Calculates energy in Joules and displays the result
            if (convert_to_joules[0] == 'y')
            {
                double energy = calculate_energy_in_joules(initial_quantum_number, final_quantum_number, atomic_number);
                std::cout << "Energy: " << std::setprecision(3) << energy << " J" << std::endl;
            }
            // Calculates energy in ev and displays the result
            else
            {
                double energy = calculate_energy_in_ev(initial_quantum_number, final_quantum_number, atomic_number);
                std::cout << "Energy: " << std::setprecision(3) << energy << " eV" << std::endl;
            }
        }
        // Catches the exception thrown by the try block
        catch (const std::invalid_argument& e)
        {
            // Prints the error message associated with the exception
            std::cout << "Error: " << e.what() << std::endl;
        }
        // Prompts user whether they want to repeat process
        std::cout << "Do you want to repeat the process? (y for yes, n for no): " << std::endl;
        std::cin >> response;

        // Loops until valid input
        while (response.length() != 1 || response[0] != 'y' && response[0] != 'n') {
            std::cout << response << " is not a valid option. Try again" << std::endl;
            std::cout << "Do you want to repeat the process? (y for yes, n for no): " << std::endl;
            std::cin >> response;
        }
    } while (response[0] == 'y');
    return 0;
}

// Check conditions for input validity
bool check_conditions(int initial_quantum_number, int final_quantum_number, int atomic_number) {
    if (initial_quantum_number < final_quantum_number) {
        std::cout << "Error: The initial quantum number has to be greater than final quantum number." << std::endl;
        return false;
    }
    if (atomic_number <= 0) {
        std::cout << "Error: Atomic number has to be greater than zero." << std::endl;
        return false;
    }
    if (initial_quantum_number <= 0) {
        std::cout << "Error: Initial quantum number has to be greater than zero." << std::endl;
        return false;
    }
    if (final_quantum_number <= 0) {
        std::cout << "Error: Final quantum number has to be greater than zero." << std::endl;
        return false;
    }
    return true;
}
// Energy value functions
double calculate_energy_in_ev(int initial_quantum_number, int final_quantum_number, int atomic_number) {
    // Returns value for energy in ev
    return energy_constant * pow(atomic_number, 2) * (1 / pow(final_quantum_number, 2) - 1 / pow(initial_quantum_number, 2));
}
double calculate_energy_in_joules(int initial_quantum_number, int final_quantum_number, int atomic_number) {
    // Returns value for energy in joules
    return energy_constant * pow(atomic_number, 2) * (1 / pow(final_quantum_number, 2) - 1 / pow(initial_quantum_number, 2)) * ev_to_j;
}