#ifndef MODEL_HPP
#define MODEL_HPP

/**
* This is the model class used to hold information about models.
* The class is templated so that different types can be used
* to label each model, depending on if you want a name for the model
* or just label it with a number.
*/
template<typename model_label_type>
class Model
{
public:
	Model(model_label_type label,
		int width,
		int height) :
	label(label),
	width(width),
	height(height),
	top_left_position_x(0),
	top_left_position_y(0),
	rotated(false)
	{
	}

	Model(model_label_type label,
		int width,
		int height,
		int top_left_position_x,
		int top_left_position_y,
		bool rotated) :
	label(label),
	width(width),
	height(height),
	top_left_position_x(top_left_position_x),
	top_left_position_y(top_left_position_y),
	rotated(rotated)
	{
	}

	/**
	* Sets the coordinates of the top left position of the model
	*/
	void set_top_left_coordinates(int x_position, int y_position)
	{
		top_left_position_x = x_position;
		top_left_position_y = y_position;
	}

	/**
	* Sets whether or not the model is rotated 90 degrees. 
	* True means that it is rotated, false means it is not rotated.
	*/
	void set_rotated(bool is_rotated)
	{
		rotated = is_rotated;
	}

	/**
	* Gets the label of the model
	*/
	model_label_type get_label()
	{
		return label;
	}

	/**
	* Gets the width of the model
	*/
	int get_width()
	{
		return width;
	}

	/**
	* Gets the height of the model
	*/
	int get_height()
	{
		return height;
	}

	/**
	* Gets the X coordinate of the top left of the model
	*/
	int get_top_left_coordinate_x()
	{
		return top_left_position_x;
	}

	/**
	* Gets the Y coordinate of the top left of the model
	*/
	int get_top_left_coordinate_y()
	{
		return top_left_position_y;
	}

	/**
	* Returns whether or not the model was rotated 90 degrees
	*/
	bool get_rotated()
	{
		return rotated;
	}

	/**
	* Creating a less than operator so the list can be sorted after the models
	* are all arranged
	*/
	bool operator< (const Model<model_label_type> &current_model)
	{
		return label < current_model.label;
	}

private:
	/** The label to identify this model */
	model_label_type label;

	/** The width of this model in the x direction */
	int width;

	/** The height of the model in the y direction */
	int height;

	/** The top left position x coordinate of the model */
	float top_left_position_x;

	/** The top left position y coordinate of the model */
	float top_left_position_y;

	/** Boolean storing whether or not the model was rotated 90 degrees */
	bool rotated;
};
#endif