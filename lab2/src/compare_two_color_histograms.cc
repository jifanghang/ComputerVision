/*
* by Fanghang Ji
* Read images from two folders and compare them, showing the closest match and the second closest match
*/
#include <iostream>
#include <string>
#include "boost/filesystem.hpp"
#include "luv_color_histogram.hh"
#include "saturatedColorHistogram.hh"

using namespace std; 
using namespace jir;
using namespace boost; 
using namespace boost::filesystem;
using namespace cv;

bool verify_folder(path& p){
    if (!exists(p)){
        cerr<< "Folder "<< p.c_str()<< " does not exist"<< endl;
        return false;
    }
    if (!(is_directory(p))){
        cerr<< p.c_str()<< " is not a folder."<< endl;
        return false;
    }
    return true;
}

//have to add file path for showing images
void load(path& p, vector<LuvColorHistogram>& hist_vector, vector<path>& file_paths){
    // Shows you how to iterate over a folder using boost.
    directory_iterator it(p);
    directory_iterator end_it;
    for (; it != end_it; it++) {
        path pf(it->path());
        if (is_directory(pf)) continue;
        cout << "loading " << pf.c_str() << "..." << endl;
        LuvColorHistogram hist;
        if (hist.load(pf.c_str())) {
            hist_vector.push_back(hist);
            hist_vector.back().load(it->path().string(), false);
            file_paths.push_back(it -> path());
        }
    }
}

/*void load(path& p, vector<SaturatedColorHistogram>& hist_vector, vector<path>& file_paths){
    // Shows you how to iterate over a folder using boost.
    directory_iterator it(p);
    directory_iterator end_it;
    for (; it != end_it; it++) {
        path pf(it->path());
        if (is_directory(pf)) continue;
        cout << "loading " << pf.c_str() << "..." << endl;
        SaturatedColorHistogram hist;
        if (hist.load(pf.c_str())) {
            hist_vector.push_back(hist);
            hist_vector.back().load(it->path().string());
            file_paths.push_back(it -> path());
        }
    }
}*/

//have to add two additional path vectors in order to show the images later on
void compare_hist_vectors(const vector<LuvColorHistogram>& h1, const vector<LuvColorHistogram>& h2,
                            const vector<path>& file_paths1, const vector<path>& file_paths2){

    vector<LuvColorHistogram>::const_iterator it1= h1.begin();
    vector<path>::const_iterator f1 = file_paths1.begin();
    for (; it1 != h1.end(); ++it1, ++f1){
        vector<LuvColorHistogram>::const_iterator it2= h2.begin();
        vector<path>::const_iterator f2 = file_paths2.begin();
        // Fill-in: iterate over h2 and compare it1 and it2
                // For each histogram in h1, find the closest two in h2.
                // Ideally, you should also show the corresponding images, or at least the file-names for quick verification.
        double min = INT_MAX;
        double min2 = INT_MAX;
        //file paths
        path min_path, min_path2;

        //iterates over h2
        for( ; it2 != h2.end(); ++it2, ++f2) {
            double cmp = it1->compare( (*it2) );
            if(cmp < min) {
                min_path2 = min_path;
                min2 = min;
                min = cmp;
                min_path = *f2;
            } else if (cmp < min2) {
                min2 = cmp;
                min_path2 = *f2;
            }
        }

        //output the mins
        cout << "\nmin: " << min << "\nmin2: " << min2 << endl;

        //showing images
        //Sequences:
        //im1: Test image; im2: closest match; im3: second closest match
        Mat im1 = imread(f1->string());
        Mat im2 = imread(min_path.string());
        Mat im3 = imread(min_path2.string());

        Mat res( im1.size( ).height, im1.size( ).width + im2.size( ).width + im3.size( ).width, CV_8UC3 );
        Mat left( res, Rect( 0, 0, im1.size( ).width, im1.size( ).height ) );
        im1.copyTo( left );
        Mat mid( res, Rect( im1.size( ).width, 0, im2.size( ).width, im2.size( ).height ) );
        im2.copyTo( mid );
        Mat right( res, Rect( im1.size( ).width + im2.size( ).width, 0, im3.size( ).width, im3.size( ).height ) );
        im3.copyTo( right );
        imshow( "Result", res );
        waitKey(0);
    }
}

/*void compare_hist_vectors(const vector<SaturatedColorHistogram>& h1, const vector<SaturatedColorHistogram>& h2,
                            const vector<path>& file_paths1, const vector<path>& file_paths2){

    vector<SaturatedColorHistogram>::const_iterator it1= h1.begin();
    vector<path>::const_iterator f1 = file_paths1.begin();
    for (; it1 != h1.end(); ++it1, ++f1){
        vector<SaturatedColorHistogram>::const_iterator it2= h2.begin();
        vector<path>::const_iterator f2 = file_paths2.begin();
        // Fill-in: iterate over h2 and compare it1 and it2
                // For each histogram in h1, find the closest two in h2.
                // Ideally, you should also show the corresponding images, or at least the file-names for quick verification.
        double min = INT_MAX;
        double min2 = INT_MAX;
        //file paths
        path min_path, min_path2;

        //iterates over h2
        for( ; it2 != h2.end(); ++it2, ++f2) {
            double cmp = it1->compare( (*it2) );
            if(cmp < min) {
                min_path2 = min_path;
                min2 = min;
                min = cmp;
                min_path = *f2;
            } else if (cmp < min2) {
                min2 = cmp;
                min_path2 = *f2;
            }
        }

        //output the mins
        cout << "\nmin: " << min << "\nmin2: " << min2 << endl;

        //showing images
        //Sequences:
        //im1: Test image; im2: closest match; im3: second closest match
        Mat im1 = imread(f1->string());
        Mat im2 = imread(min_path.string());
        Mat im3 = imread(min_path2.string());

        Mat res( im1.size( ).height, im1.size( ).width + im2.size( ).width + im3.size( ).width, CV_8UC3 );
        Mat left( res, Rect( 0, 0, im1.size( ).width, im1.size( ).height ) );
        im1.copyTo( left );
        Mat mid( res, Rect( im1.size( ).width, 0, im2.size( ).width, im2.size( ).height ) );
        im2.copyTo( mid );
        Mat right( res, Rect( im1.size( ).width + im2.size( ).width, 0, im3.size( ).width, im3.size( ).height ) );
        im3.copyTo( right );
        imshow( "Result", res );
        waitKey(0);
    }
}*/

int main(int argc, const char* argv[]) {

    if (argc < 3){
        cerr<< "Usage: \n"<< argv[0]<< " [training folder name] [test folder name]"<< endl;
        return -1;
    }

    path p_train (argv[1]);
    if (!verify_folder(p_train)) return -1;

    path p_test(argv[2]);
    if (!verify_folder(p_test)) return -1;


    vector<LuvColorHistogram> histograms_train;
    vector<LuvColorHistogram> histograms_test;

    //vector<SaturatedColorHistogram> histograms_train;
    //vector<SaturatedColorHistogram> histograms_test;

    vector<path> paths_train;
    vector<path> paths_test;

    load(p_train, histograms_train, paths_train);
    cout<< "*** loaded "<< histograms_train.size()<< " training samples."<< endl;

    load(p_test, histograms_test, paths_test);
    cout << "*** loaded " << histograms_test.size() << " testing samples." << endl;

    cout<< "Comparing histograms"<< endl;
    compare_hist_vectors(histograms_train, histograms_test, paths_train, paths_test);

    cout<< endl<< endl;

}
