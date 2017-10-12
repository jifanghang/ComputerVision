/*
* by Fanghang Ji
* Read noisy points and fit a plane
*/
#include <iostream>
#include <fstream>
#include <memory>
#include "opencv2/core/core.hpp"
//#include "vec3.h"

//#define DEBUG
using namespace std;
using namespace cv;

int main( int argc, char* argv[] ) {
    // read data
    if ( argc < 2 ) {
        cerr << "No data provided!" << endl;
        return 1;
    }
    ifstream input;
    input.open( argv[ 1 ] );
    if ( !input.is_open( ) ) {
        cerr << "Fail to open file!" << endl;
        return 1;
    }
    int m;  //number of points
    input >> m;
    vector< float > points_buffer( m * 3, 0 );
    for ( int i = 0; i < points_buffer.size( ); i++ ) {
        input >> points_buffer[ i ];
    }
    //load points
    Mat points( m, 3, CV_32FC1, &points_buffer[ 0 ] );
#ifdef DEBUG
    cout << points.at<double>(1, 1) << endl;
#endif
    input.close( );

    //take average for all equations
    float x_average = 0.0;
    float y_average = 0.0;
    float z_average = 0.0;
    for(int i = 0; i < m; i++) {
        x_average += points.at<double>(i, 0);
        y_average += points.at<double>(i, 1);
        z_average += points.at<double>(i, 2);
    }
    x_average = x_average / m;
    y_average = y_average / m;
    z_average = z_average / m;
#ifdef DEBUG
    cout << x_average << ", " << y_average << ", " << z_average << endl;
#endif












/*
    // calculate r_g (1, 3)
    Mat r_g( 1, 3, CV_32FC1, float(0));
    for ( int i = 0; i < m; i++ ) {
        r_g += points.row(i);
    }
    r_g /= m;

    // calculate A (3, 3)
    Mat A(3, 3, CV_32FC1, float(0));
    for ( int i = 0; i < m; i++) {
        Mat diff(1, 3, CV_32FC1, float(0));
        Mat diff_t(3, 1, CV_32FC1, float(0));
        diff = points.row(i) - r_g;
        transpose(diff, diff_t);
        A += diff_t * diff;
    }
#ifdef DEBUG
    cout << A << endl;
#endif

    // calculate n (1, 3)
    Mat eigenvalues(1, 3, CV_32FC1, float(0));
    Mat eigenvectors(3, 3, CV_32FC1, float(0));
    eigen(A, eigenvalues, eigenvectors);
#ifdef DEBUG
    cout << eigenvalues << endl;
    cout << eigenvectors << endl;
#endif
    Mat n(1, 3, CV_32FC1, float(0));
    normalize(eigenvectors.row(2), n);
    cout << "normal vector n: " << n << endl;

    // calculate d
    Mat n_t(3, 1, CV_32FC1, float(0));
    transpose(n, n_t);
    Mat d_matrix(1, 1, CV_32FC1, float(0));
    d_matrix = r_g * n_t;
    float d = d_matrix.at<float>(0, 0);
    cout << "d: " << d << endl;
*/
    return 0;
}
