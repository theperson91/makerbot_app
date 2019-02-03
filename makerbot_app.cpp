#include "BinPack2D.hpp"
#include "ModelAranger.hpp"
#include "Model.hpp"
#include <iostream>
#include <fstream>

// The model arranger with models with integer labels. For
// now, we'll just label the models with their index, in the future
// it could help to have actual names tied to the models.
ModelAranger<std::vector<Model<int> > > model_arranger;

// Vector to hold the models as input/output to the model arranger
std::vector<Model<int> > model_container;

int main(int argc, char**argv)
{
	std::ifstream input_file (argv[1]);
	std::string input_value;
	int input_width;
	int input_height;
	int model_index = 0;

	while (input_file.good())
	{
		// process the inuput csv file
		std::getline(input_file, input_value, ',');
		input_width = std::stoi(input_value);
		std::getline(input_file, input_value);
		input_height = std::stoi(input_value);

		// create an array of Models
		Model<int> next_model(model_index, input_width, input_height);
		model_container.push_back(next_model);
		++model_index;
	}

	// process the models
	model_arranger.set_modles(model_container);
	model_arranger.arrange();
	model_container = model_arranger.get_models();

	// output the results to the console
	for (size_t i = 0; i < model_container.size(); ++i)
	{
		Model<int> results = model_container[i];
		std::cout << "Label: " << results.get_label();
		std::cout << "; X Coordinate: " << results.get_top_left_coordinate_x();
		std::cout << "; Y Coordinate: " << results.get_top_left_coordinate_y();
		std::cout << "; Rotated: " << results.get_rotated();
		std::cout << "\n";
	}
}
