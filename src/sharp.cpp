// This sharpens the blurred image using a 3x3 kernel.
// Made by: @MenuuTUX with ❤️ on GitHub
// Check out: https://github.com/MenuuTUX

#include <opencv2/opencv.hpp>

/**

Applies a sharpening filter to the input image using a 3x3 kernel.

@param img The input image to be sharpened.

@param sharp_point The sharpening point value to be used in the center of the kernel.

@param sharp_low The low sharpening value to be used in the other parts of the kernel.

@return The sharpened image after the sharpening process.
*/

cv::Mat sharp(cv::Mat img, float sharp_point, float sharp_low) {
// Create a 3x3 sharpening kernel with the given sharp_point and sharp_low values
cv::Mat s_kernel = (cv::Mat_<float>(3, 3) << 0, sharp_low, 0, sharp_low,
sharp_point, sharp_low, 0, sharp_low, 0);

// Apply the filter to the input image using the created kernel
cv::Mat sharpened;
cv::filter2D(img, sharpened, -1, s_kernel);

// Return the sharpened image after the sharpening process
return sharpened;
}
