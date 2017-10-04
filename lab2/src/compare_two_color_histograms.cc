
#include <iostream>
#include <string>
#include "boost/filesystem.hpp"
#include "luv_color_histogram.hh"

using namespace std; 
using namespace jir;
using namespace boost; 
using namespace boost::filesystem;

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

//have to add two additional path vectors in order to show the images later on
void compare_hist_vectors(const vector<LuvColorHistogram>& h1, const vector<LuvColorHistogram>& h2,
                            const vector<path>& file_paths1, const vector<path>& file_paths2){

    vector<LuvColorHistogram>::const_iterator it1= h1.begin();
    vector<path>::const_iterator f1 = file_paths1.begin();
    int c1(0);
    for (; it1 != h1.end(); ++it1){
        vector<LuvColorHistogram>::const_iterator it2= h2.begin();
        vector<path>::const_iterator f1 = file_paths1.begin();
        int c2(0);
        // Fill-in: iterate over h2 and compare it1 and it2
                // For each histogram in h1, find the closest two in h2.
                // Ideally, you should also show the corresponding images, or at least the file-names for quick verification.
        double min = INT_MAX;
        double min2 = INT_MAX;
        //file paths
        path min_path, min_path2;

        //iterates over h2
        for( ; it2 != h2.end(); ++it2) {
            double cmp = it1->compare( (*it2) );
            if(cmp < min) {
                min_path2 = min_path;
                min2 = min;
                min = cmp;
                min_path = *f2;
            } else if (cmp < min2) {
                min2 = cmp;
            }
        }
    }
}

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
