#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void zeroOutEdges(cv::Mat& image) {
    // Assuming image is a valid cv::Mat object
    int thickness = 1; // Thickness of the edge to be zeroed out

    // Set top edge to zero
    cv::rectangle(image, cv::Point(0, 0), cv::Point(image.cols, thickness - 1), cv::Scalar(0, 0, 0), cv::FILLED);

    // Set bottom edge to zero
    cv::rectangle(image, cv::Point(0, image.rows - thickness), cv::Point(image.cols, image.rows), cv::Scalar(0, 0, 0), cv::FILLED);

    // Set left edge to zero
    cv::rectangle(image, cv::Point(0, 0), cv::Point(thickness - 1, image.rows), cv::Scalar(0, 0, 0), cv::FILLED);

    // Set right edge to zero
    cv::rectangle(image, cv::Point(image.cols - thickness, 0), cv::Point(image.cols, image.rows), cv::Scalar(0, 0, 0), cv::FILLED);
}

void applyCustom2DFilter(const Mat& inputImage, Mat& outputImage, cv::BorderTypes borderType, int borderConstantValue) {
    // Define the kernel. Note that OpenCV expects a floating point matrix for the filter2D function.
    Mat kernel = (Mat_<float>(3,3) << 1, 2, 1,
                                       2, 4, 2,
                                       1, 2, 1);
    // Normalize the kernel to ensure the brightness of the output image is similar to the input image.
    kernel = kernel / 16.0;

    // Apply the custom 2D filter
    if (borderType == cv::BORDER_CONSTANT) {
        filter2D(inputImage, outputImage, -1, kernel, Point(-1, -1), borderConstantValue, borderType);
    } else {
        filter2D(inputImage, outputImage, -1, kernel, Point(-1, -1), 0, borderType);
    }
}

int main(int argc, char** argv) {
    cv::BorderTypes borderType = cv::BORDER_DEFAULT;
    int borderConstantValue = 0;

    if (argc < 3 or argc > 6) {
        cout << "Usage: " << argv[0] << " <InputImage> <OutputImage>  [<BorderType>] [<BorderConstantValue>]" << endl;
        return -1;
    }

    // If a border type is provided, use it.  Otherwise, use the default border type.
    // Convert the string to cv::BorderTypes value.
    if (argc == 4) {
        string borderTypeString = argv[3];
        if (borderTypeString == "BORDER_CONSTANT") {
            borderType = cv::BORDER_CONSTANT;
            if (argc == 5) {
                // convert argv[4] to an integer
                borderConstantValue = atoi(argv[4]);
            } else {
                borderConstantValue = 0;
            }
        } else if (borderTypeString == "BORDER_REPLICATE") {
            borderType = cv::BORDER_REPLICATE;
        } else if (borderTypeString == "BORDER_REFLECT") {
            borderType = cv::BORDER_REFLECT;
        } else if (borderTypeString == "BORDER_REFLECT_101") {
            borderType = cv::BORDER_REFLECT_101;
        } else if (borderTypeString == "BORDER_TRANSPARENT") {
            borderType = cv::BORDER_TRANSPARENT;
        } else if (borderTypeString == "BORDER_REFLECT101") {
            borderType = cv::BORDER_REFLECT_101;
        } else if (borderTypeString == "BORDER_DEFAULT") {
            borderType = cv::BORDER_DEFAULT;
        } else if (borderTypeString == "BORDER_ISOLATED") {
            borderType = cv::BORDER_ISOLATED;
        } else if (borderTypeString == "BORDER_WRAP") {
            borderType = cv::BORDER_WRAP;
        } else {
            cout << "Invalid border type.  Using default border type." << endl;
        }
    }

    // Read the image file
    Mat image = imread(argv[1]);
    if (image.empty()) {
        cout << "Could not open or find the image" << endl;
        return -1;
    }

    Mat filteredImage;
    applyCustom2DFilter(image, filteredImage, borderType, borderConstantValue);

    // Zero out the edges of the filtered image
    // This is done to ignore any differences in the edges of the images
    // The opencv 2d filter can filter up to the edge of the image.  The HLS
    // Book example skips this edge case.
    //
    //zeroOutEdges(filteredImage);

    // Write the filtered image to disk
    bool writeSuccess = imwrite(argv[2], filteredImage);
    if (!writeSuccess) {
        cout << "Failed to write the image" << endl;
        return -1;
    }

    cout << "Image processed and saved successfully" << endl;
    return 0;
}