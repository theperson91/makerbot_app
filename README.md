The makerbot_app will take a list of rectangular inputs with width and height specified and place them in a way
such that they are centered around the origin of the 3d printer build plate. The input can be any csv file that contains
a list of width,height integers. The sample input.csv provided can be used as an example or modified to fit your needs.

Once you clone the repo, run the following commands to generate the list of positions:

g++ -std=c++11 makerbot_app.cpp -o ModelArranger.out
./ModelArranger.out input.csv 

The output will come to the console as a list of labels with associated X and Y coordinates of the top left of the model, and whether or not the model was rotated 90 degrees. The labels correspond to the zero indexed line of the model in the input csv file.

While this is the initial version of the code, there are a number of improvements that could be made with a little more time:
1. Input validation should be used to make sure the input csv file is formatted correctly
2. The ability to put a proper name label as a string associated with each model so that it can be more easily tracked in the output
3. A sorted output, ideally in alphabetical order of the names of each of the models
4. Identifying a more accurate algorithm for getting the models as close to the center as possible
