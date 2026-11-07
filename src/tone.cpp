// This script removes screentones from the input image.
// Made by: @MenuuTUX with ❤️ on GitHub
// Check out: https://github.com/MenuuTUX

#include <blur.hpp>
#include <log.hpp>
#include <opencv2/opencv.hpp>
#include <sharp.hpp>
#include <string>
#include <vector>

using namespace std;
using namespace cv;

/**
 * Applies a blur filter to the input image using either Gaussian or bilateral filter depending on the blur_amount.
 *
 * @param img The input image to be blurred.
 * @param blur_amount The amount of blurring to be applied to the input image.
 * If the value is 7, bilateral filter is applied after Gaussian filter with the kernel size of 7 and the constant values of 80.
 * Otherwise, bilateral filter is applied with the kernel size of 7 and the constant values of 10 * blur_amount after Gaussian filter with the kernel size of 5.
 *
 * @return The blurred image after the blurring process.
 */

void remove_screentones(string dir_i, string dir_o, int blur_amount,
                        float sh_point = 5.56, float sh_low = -1.14) {
    // Check if the input directory is empty
    if (dir_i.empty()) {
        log("No input directory");
        return;
    }
    // Check if the output directory is empty
    if (dir_o.empty()) {
        log("No output directory");
        return;
    }
    // Check if the input image is empty
    vector<String> inputs;
    glob(dir_i + "/*.*", inputs);

    // If the input image is empty, return
    if (inputs.empty()) {
        log("No images file found");
        return;
    }

    // Check if the blur amount is valid
    log("Removing tone");

    // Check if the sharpness point is valid
    sh_point = static_cast<float>(sh_point);
    sh_low = static_cast<float>(sh_low);

    // Check if the blur amount is valid
    int bs_amount = 0;

    // If the blur amount is 0, apply Gaussian filter with the kernel size of 5
    if (blur_amount == 1) {
        bs_amount = 3;
    }
    // If the blur amount is 1, apply bilateral filter with the kernel size of 7 and the constant values of 80
    if (blur_amount == 2) {
        bs_amount = 5;
    }
    // If the blur amount is 2, apply bilateral filter with the kernel size of 7 and the constant values of 10 * blur_amount
    if (blur_amount == 3) {
        bs_amount = 7;
    }

    // Create the blur filter
    for (auto i : inputs) {
        // Check if the input image is empty
        Mat img = imread(i);
        // If the input image is empty, return
        Mat blurred = img.clone();
        // Apply the blur filter
        medianBlur(img, blurred, bs_amount);
        // Write the blurred image
        Mat ret = Mat::zeros(img.size(), img.type());
        // Apply the sharp filter
        sharp(blur(img, blur_amount), sh_point, sh_low)
            .copyTo(ret, blurred > 0);
        // Write the blurred image
        bool success =
            imwrite(dir_o + "/" + i.substr(i.find_last_of("/") + 1), ret);
        // If the image is not written successfully, return
        if (!success) {
            log("An error occurred");
        }
    }
    // Finish the process
    log("ToneRemover has done running");
}