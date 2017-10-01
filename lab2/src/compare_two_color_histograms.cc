
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

void load(path& p, vector<LuvColorHistogram>& hist_vector){
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
		}
	}
}

void compare_hist_vectors(const vector<LuvColorHistogram>& h1, const vector<LuvColorHistogram>& h2){

	vector<LuvColorHistogram>::const_iterator it1= h1.begin();
	int c1(0);
	for (; it1 != h1.end(); ++it1){
		vector<LuvColorHistogram>::const_iterator it2= h2.begin();
		int c2(0);
		// Fill-in: iterate over h2 and compare it1 and it2
                // For each histogram in h1, find the closest two in h2.
                // Ideally, you should also show the corresponding images, or at least the file-names for quick verification.
		
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

	load(p_train, histograms_train);
	cout<< "*** loaded "<< histograms_train.size()<< " training samples."<< endl;

	load(p_test, histograms_test);
	cout << "*** loaded " << histograms_test.size() << " testing samples." << endl;

	cout<< "Comparing histograms"<< endl;
	compare_hist_vectors(histograms_train, histograms_test);

	cout<< endl<< endl;


}
