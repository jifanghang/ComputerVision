/*
* by Fanghang Ji
*/
using namespace std;
using namespace cv;

class SaturatedColorHistogram {
private:
	int histSize[3];
	int nr_samples;
	//the range for the h, s, v values
	float hue[2];
	float saturation[2];
	float value[2];
	Mat hist;
	Mat color_hsv;

public:
	SaturatedColorHistogram();
	void normalize();
	//load image and convert from BGR to HSV
	bool load(const string& path);
	bool load(const Mat& image, const Mat& mask);
	double compare(const SaturatedColorHistogram& other) const;

	//getters
	Mat& get_histogram() {
        return hist;
    }

    int get_nr_bins_h() {
        return histSize[0];
    }

    int get_nr_bins_s() {
        return histSize[1];
    }

    int get_nr_bins_v() {
        return histSize[2];
    }

    int get_nr_of_bins() {
        return (histSize[0]*histSize[1]*histSize[2]);
    }

};