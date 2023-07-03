// Assignment 3
// Student ID: 10138372
// Organising galaxies and satellites into classes
#include<iostream>
#include<string>
#include<cmath>
#include<vector>
class galaxy
{
private:
	std::string name{ "none" };
	std::string type{ "none" };
	std::string hubble_type{ "none" };
	double redshift{ 0.0 };
	double total_mass{ 0.0 };
	double stellar_mass{ 0.0 };
	double stellar_mass_fraction_calc{ 0.0 };
	std::vector<galaxy> satellites;
public:
	// Default constructor
	galaxy() = default;
	// Parameterized constructor
	galaxy(std::string galaxy_name, std::string hubble_type, double galaxy_mass, double star_mass, double z) :
		name{ galaxy_name }, type{ hubble_type }, total_mass{ galaxy_mass }, stellar_mass{ star_mass },
		stellar_mass_fraction_calc{ stellar_mass / total_mass }, redshift{ z }
	{
		// Validate the hubble_type
		std::vector<std::string> allowed_types = { "E0", "E1", "E2", "E3", "E4", "E5", "E6", "E7",
												  "S0", "Sa", "Sb", "Sc", "SBa", "SBb", "SBc", "Irr" };
		if (std::find(allowed_types.begin(), allowed_types.end(), hubble_type) == allowed_types.end()) {
			throw std::invalid_argument("Invalid Hubble type!");
		}
		// Validation checks for redshift, total mass and stellar mass fraction
		if (z < 0.0 || z > 10.0) {
			throw std::invalid_argument("Redshift must be between 0 and 10!");
		}
		redshift = z;
		if (total_mass < 1e7 || total_mass > 1e12) {
			throw std::invalid_argument("Total mass must be between 1e7 and 1e12 solar masses!");
		}
		if (stellar_mass_fraction_calc < 0.0 || stellar_mass_fraction_calc > 0.05) {
			throw std::invalid_argument("Stellar mass fraction must be within 0 and 0.05");
		}
	}
	// Destructor
	~galaxy() {}
	//Public member function that returns the stellar mass fraction
	double stellar_mass_fraction() { return stellar_mass_fraction_calc; }
	// Public member function that changes the type Hubble type
	void change_type(std::string new_type) { type.clear(); type = new_type; }
	// Public member function that prints the data
	void print_data();
	// Member function to add a satellite galaxy
	void add_satellite(galaxy satellite) {
		satellites.push_back(satellite);
	}
};
// Function that prints the Galaxys' and satellites properties
void galaxy::print_data()
{
	std::cout.precision(3); 
	std::cout << "Galaxy: = [" << name << "," << type << "," << total_mass
		<< "," << stellar_mass << "," << stellar_mass_fraction_calc << "," << redshift << "]" << std::endl;
	// Check if there are any satellites for this galaxy object
	if (!satellites.empty()) {
		std::cout << "Number of satellites: " << satellites.size() << std::endl;
		std::cout << "Satellite properties:" << std::endl;
		for (const auto& sat : satellites) {
			std::cout << "\t[" << sat.name << "," << sat.type << "," << sat.total_mass
				<< "," << sat.stellar_mass << "," << sat.stellar_mass_fraction_calc << "," << sat.redshift << "]" << std::endl;
		}
	}
	return;
}
int main()
{
	try {
		std::vector<galaxy> galaxies;
		galaxies.push_back(galaxy("Galaxy 1", "S0", 10e10, 10e8, 8));
		galaxies.push_back(galaxy("Galaxy 2", "Irr", 10e11, 10e9, 3));
		// add satellites to the first galaxy object
		galaxies[0].add_satellite(galaxy("Satellite 1", "Sa", 10e9, 10e7, 8));
		galaxies[0].add_satellite(galaxy("Satellite 2", "Sb", 10e8, 10e6, 8));
		// Changing hubble type for second galaxy object
		galaxies[1].change_type("E0");
		// Prints galaxy and satellite objects
		for (std::vector<galaxy>::iterator it = galaxies.begin(); it != galaxies.end(); ++it) {
			it->print_data();
		}
	}
	catch (const std::invalid_argument& e) {
		std::cout << e.what() << std::endl;
	}
	return 0;
}