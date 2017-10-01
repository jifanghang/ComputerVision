/** Example code on using the boost library folder-iterator
*/
bool verify_folder(path& p) {
	if (!exists(p)) {
		cerr << "Folder " << p.c_str() << " does not exist" << endl;
		return false;
	}
	if (!(is_directory(p))) {
		cerr << p.c_str() << " is not a folder." << endl;
		return false;
	}
	return true;
}

void load(path& p, vector<LuvColorHistogram>& hist_vector) {
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

/**
This function shows the usage of LuvColorHistogram::compare
*/
void compare_hist_vectors(const vector<LuvColorHistogram>& h1, const vector<LuvColorHistogram>& h2) {

	vector<LuvColorHistogram>::const_iterator it1 = h1.begin();
	int c1(0);
	for (; it1 != h1.end(); ++it1) {
		vector<LuvColorHistogram>::const_iterator it2 = h2.begin();
		int c2(0);
		for (; it2 != h2.end(); ++it2) {
			cout << c1 << "<->" << c2 << " : " << it1->compare(*it2) << endl;
			++c2;
		}
		++c1;
	}
}


/** H is in interval [0, 360), S and V are within (0,1].
* RGB are within [0,255] as usual.
* if s == 0, then h = -1 (undefined)
*/
void RGBtoHSV(unsigned char rc, unsigned char gc, unsigned char bc,
	float& h, float& s, float& v) {

	float r = float(rc) / 255.0;
	float g = float(gc) / 255.0;
	float b = float(bc) / 255.0;

	float min_rgb, max_rgb;
	float min, max, delta;
	max_rgb = ((rc >= gc) && (rc >= bc)) ? rc : (((gc >= rc) && (gc >= bc)) ? gc : bc);
	min_rgb = ((rc <= gc) && (rc <= bc)) ? rc : (((gc <= rc) && (gc <= bc)) ? gc : bc);

	min = float(min_rgb) / 255.0;
	max = float(max_rgb) / 255.0;

	v = max;				// v
	delta = max - min;

	if (max_rgb != 0)
		s = delta / max;		// s
	else {
		// r = g = b = 0		// s = 0, v is undefined
		s = 0.;
		h = -1.;
		return;
	}

	if (rc == max_rgb)
		h = (g - b) / delta;		// between yellow & magenta
	else if (gc == max_rgb)
		h = 2.0 + (b - r) / delta;	// between cyan & yellow
	else
		h = 4.0 + (r - g) / delta;	// between magenta & cyan

	h *= 60.0;				// degrees
	if (h < 0)
		h += 360.0;
}

