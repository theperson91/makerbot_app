#ifndef MODEL_ARRANGER_HPP
#define MODEL_ARRANGER_HPP

#include "Model.hpp"
#include "BinPack2D.hpp"

/**
* This class takes a container of type container_model_type
* full of Models and sets the optimal top left coordinate
* and rotation for each model
*/
template<typename container_model_type>
class ModelAranger
{
public:
	/**
	* Default constructor of the model arranger class
	*/
	ModelAranger()
	{
	}

	/**
	* Arranges the models on a build plate and sets the
	* top left x and y coordinates and rotation of each
	* model depending on its final position
	*/
	void arrange()
	{
		static const int NUM_BUILD_PLATES = 1;

		BinPack2D::ContentAccumulator<Model<int> > input_content;

		for (size_t i = 0; i < input_model_container.size(); ++i)
		{
			input_content += BinPack2D::Content<Model<int> >(
				input_model_container[i],
				BinPack2D::Coord(),
				BinPack2D::Size(input_model_container[i].get_width(), input_model_container[i].get_height()),
				false
				);
		}
		input_content.Sort();

		bool success = false;
		int build_plate_side = 1;
		BinPack2D::CanvasArray<Model<int> > canvas_array = BinPack2D::UniformCanvasArrayBuilder<Model<int> >(build_plate_side, build_plate_side, NUM_BUILD_PLATES).Build();
		while (!success)
		{
			// create only 1 bin since there's only 1 build plate, and with side equal
			// to build plate side. Keep increasing build plate side until we get the
			// smallest size that works. This class would support optimizing printing on
			// separate plates/iterations if you ever wanted to go that direction.
			canvas_array = BinPack2D::UniformCanvasArrayBuilder<Model<int> >(build_plate_side, build_plate_side, NUM_BUILD_PLATES).Build();

			BinPack2D::ContentAccumulator<Model<int> > remainder;

			success = canvas_array.Place(input_content, remainder);
			++build_plate_side;
		}

		// Once we got a successful size, then process the results
		BinPack2D::ContentAccumulator<Model<int> > output_content;
		canvas_array.CollectContent(output_content);
		typedef BinPack2D::Content<Model<int> >::Vector::iterator binpack2d_iterator;
		for (binpack2d_iterator itor = output_content.Get().begin(); itor != output_content.Get().end(); itor++) {

			BinPack2D::Content<Model<int> > &content = *itor;

			// retreive your data.
			Model<int> my_content = content.content;
			Model<int>* content_output = new Model<int>(
				my_content.get_label(),
				my_content.get_width(),
				my_content.get_height(),
				// the coordinates are all positive, so need to center the coordinates over the origin
				content.coord.x - build_plate_side / 2.0F,
				// this algorithm uses an inverter y coordinate (y goes downwards), need to inverse
				-content.coord.y + build_plate_side / 2.0F,
				content.rotated
			);
			output_model_container.push_back(*content_output);
		}

		// For some reason this line won't build when using gcc. Unfortunately, I
		// ran out of time debugging this but I would like to fix this in the future.
		// Not having this line means the output returns out of order, but is labeled to
		// show the correct order.
		//std::sort(output_model_container.begin(), output_model_container.end());
	}

	/**
	* Sets the models as the input to be arranged
	*/
	void set_modles(container_model_type& models)
	{
		input_model_container = models;
	}

	/**
	* Gets the models. Arrange must be called before this function
	* to get an arranged set of models.
	*/
	container_model_type& get_models()
	{
		return output_model_container;
	}

private:
	/**
	* The container holding the models to be arranged
	*/
	container_model_type input_model_container;

	/**
	* The container holding the arranged output models
	*/
	container_model_type output_model_container;

};
#endif
