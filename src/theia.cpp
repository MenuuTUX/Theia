// Main function of the program
// Made by: @MenuuTUX with ❤️ on GitHub
// Check out: https://github.com/MenuuTUX


#include <filesystem>
#include <blur.hpp>
#include <iostream>
#include <log.hpp>
#include <sharp.hpp>
#include <string>
#include <tone.hpp>

using namespace std;
using namespace cv;

/**

The main function of the program, which reads image files from an input directory, applies image processing filters (blur, sharpen, tone removal), and saves the processed images as PNG files in an output directory.

@param argc The number of command line arguments.

@param argv An array of strings representing the command line arguments.

@return 0 if the program runs successfully, otherwise an error code.
**/

int main(int argc, char argv[]) {
// Path to input and output directories
string input_dir = "./input/";
string outputDir = "./output/";


// Create folders, nothing happens if they already exist
// v would crash the application otherwise
std::filesystem::create_directories(input_dir);
// v would silently fail otherwise
std::filesystem::create_directories(outputDir);

// Set image processing filter values
int blur_amount = 2;
float sharpness_point = 5.56;
float sharpness_low = -1.14;

// Remove screentones from input images using blur and sharpening filters
remove_screentones(input_dir, input_dir, blur_amount, sharpness_point, sharpness_low);

// Read all image files in the input directory
vector<string> filenames;
glob(input_dir + "*", filenames);

// Loop through each file and convert it to PNG
for (size_t i = 0; i < filenames.size(); i++) {
// Load image from file
Mat image = imread(filenames[i], IMREAD_COLOR);

 // Check if image was loaded successfully
 if (image.empty()) {
     // Print error message and continue with next image
     cerr << "Error: Unable to load image " << filenames[i] << endl;
     continue;
 }

 // Create output filename by replacing extension with .png
 string outputFilename =
     outputDir + filenames[i].substr(filenames[i].find_last_of("/") + 1);
 outputFilename =
     outputFilename.substr(0, outputFilename.find_last_of(".")) + ".png";

 // Save image as PNG
 imwrite(outputFilename, image);

 // Print status message
 log("Converted " + filenames[i] + " to " + outputFilename);
}

return 0;
}
