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

// NOTE: There are small differences between the HLS Book 2d filter output
// and OpenCV 2d filter output.  The differences are due to the
// quantization error.
//
int main(int argc, char** argv) {
    if (argc != 3) {
        cout << "Usage: " << argv[0] << " <Image1> <Image2>" << endl;
        return -1;
    }

    // Load the two images
    Mat img1 = imread(argv[1], IMREAD_GRAYSCALE);
    Mat img2 = imread(argv[2], IMREAD_GRAYSCALE);

    // Zero out the edges of the images
    // This is done to ignore any differences in the edges of the images
    // The opencv 2d filter can filter up to the edge of the image.  The HLS
    // Book example skips this edge case.
    //
    zeroOutEdges(img1);
    zeroOutEdges(img2);

    // send the images to std::out
    cout << "Image 1:" << endl;
    cout << img1 << endl;
    cout << "Image 2:" << endl;
    cout << img2 << endl;

    if (img1.empty() || img2.empty()) {
        cout << "Could not open or find one of the images" << endl;
        return -1;
    }

    // Ensure the images are of the same size and type
    if (img1.size() != img2.size() || img1.type() != img2.type()) {
        cout << "The images have different sizes or types and cannot be compared" << endl;
        return -1;
    }

    // Calculate the absolute difference
    Mat diff;
    absdiff(img1, img2, diff);

    // send the diff to std::out
    cout << diff << endl;

    // Sum the differences
    //Scalar sumOfDifferences = sum(diff);
    //double sumOfDifferences = sum(diff)[0] / (diff.rows * diff.cols * diff.channels());
    double sumOfDifferences = sum(diff)[0];

    // Output the sum of the absolute differences
    cout << "Sum of absolute differences: " << sumOfDifferences << endl;

    return 0;
}