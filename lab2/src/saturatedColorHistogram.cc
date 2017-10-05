/*
* by Fanghang Ji
*/

#include <iostream>
#include <string>
#include <boost/filesystem.hpp>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "saturatedColorHistogram.hh"

using namespace boost;
using namespace std;
using namespace cv;

SaturatedColorHistogram::SaturatedColorHistogram() : nr_samples(0) {
    histSize[0] = 30;
    histSize[1] = 32;
    histSize[2] = 30;

    //setting the ranges for HSV
    hue[0] = 0.0;
    hue[1] = 179.0 + 0.1;

    saturation[0] = 0.0;
    saturation[1] = 255.0 + 0.1;

    value[0] = 0.0;
    value[1] = 255.0 + 0.1;
}

/*void SaturatedColorHistogram::normalize() {
    if (nr_samples == 0) return;
    for (int i_h = 0; i_h < get_nr_bins_h(); ++i_h) {
        for (int i_s = 0; i_s < get_nr_bins_s(); ++i_s) {
            for (int i_v = 0; i_v < get_nr_bins_v(); ++i_v) {
                hist.at<float>(i_h, i_s, i_v) /= float(nr_samples);
            }
        }
    }
}*/

bool SaturatedColorHistogram::load(const Mat &color_img, const Mat &mask) {
    nr_samples = 0;
    nr_samples += color_img.total();

    Mat color_img_float(color_img.size(), CV_32FC3);
    color_img.convertTo(color_img_float, CV_32F, 1.0 / 255.0); // Each channel BGR is between 0.0 and 1.0 now

    color_hsv.create(color_img_float.size(), CV_32FC3); // The destination should be preallocated.

    // Read the documentation of cvtColor:
    // http://docs.opencv.org/2.4/modules/imgproc/doc/miscellaneous_transformations.html#cvtcolor
    cvtColor(color_img, color_hsv, CV_BGR2HSV);

    int channels[] = {0, 1, 2};
    const float *ranges[] = {hue, saturation, value};

    // Read the documentation at:
    // http://docs.opencv.org/2.4/modules/imgproc/doc/histograms.html

    //for(int i=)
    calcHist(&color_hsv, 1, channels, mask /* Mat() if no mask */,
             hist, 3, histSize, ranges, true, false);

    // cv::normalize() does not work for dim > 3.
    // cv::normalize( _hist, _normailzed_hist, 0, 1, cv::NORM_MINMAX, -1, Mat());
    // Look at: http://opencv.willowgarage.com/documentation/cpp/basic_structures.html
    // void normalizeColorHist(MatND& hist)
    // cout<< "\t normalized color histogram"<< endl;
    // For CV_COMP_BHATTACHARYYA, normalization is not needed.

    // Explicitly normalize, so that the hist bins add to unity.

    //normalize();
    return true;
}

bool SaturatedColorHistogram::load(const string &image_path_name) {
    Mat color_img = imread(image_path_name.c_str());
    if (!color_img.data) {
        cerr << "could not open " << image_path_name << endl;
        return false;
    }

    return load(color_img, Mat());
}

double SaturatedColorHistogram::compare(const SaturatedColorHistogram &other) const{
    double result = 0.0;
    result = compareHist(hist, other.hist, CV_COMP_BHATTACHARYYA);
    return result;
}





