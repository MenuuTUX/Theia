// This script is used to blur the input image using either Gaussian or bilateral filter depending on the blur_amount.
// Made by: @MenuuTUX with ❤️ on GitHub
// Check out: https://github.com/MenuuTUX

#include <opencv2/opencv.hpp>

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

cv::Mat blur(const cv::Mat& img, int blur_amount = 5) {
    cv::Mat dst2, dst;
    if (blur_amount == 7) {
        // Applying Gaussian filter with kernel size of 7 and standard deviation of 0
        cv::GaussianBlur(img, dst2, cv::Size(7, 7), 0);
        // Applying bilateral filter with kernel size of 7, and the constant values of 80
        cv::bilateralFilter(dst2, dst, 7, 80, 80);
    } else {
        // Applying Gaussian filter with kernel size of 5 and standard deviation of 0
        cv::GaussianBlur(img, dst2, cv::Size(5, 5), 0);
        // Applying bilateral filter with kernel size of 7, and the constant values of 10 * blur_amount
        cv::bilateralFilter(dst2, dst, 7, 10 * blur_amount, 80);
    }
    // Return the blurred image after the blurring process
    return dst;
}
