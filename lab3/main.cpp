/*
* by Fanghang Ji
* Read noisy points and fit a plane
*/
#include <iostream>
#include <fstream>
#include <memory>
#include "opencv2/core/core.hpp"
#include <math.h>
//#include "vec3.h"

//#define DEBUG
using namespace std;
using namespace cv;

void fit_plane (double &A, double &B, double &C, int m, Mat &points, 
                double x_average, double y_average, double z_average) {
    Mat m1(2, 2, CV_32FC1);
    Mat m2(2, 1, CV_32FC1);
    Mat m1_x(2, 2, CV_32FC1);
    double a11 = 0, a12 = 0, a21 = 0, a22 = 0;
    for(int i = 0; i < m; i++) {
        m1.at<double>(0,0) += (points.at<double>(i, 0) - x_average) * (points.at<double>(i, 0) - x_average);
        m1.at<double>(1,0) += (points.at<double>(i, 0) - x_average) * (points.at<double>(i, 1) - y_average);       
        m1.at<double>(0,1) += (points.at<double>(i, 0) - x_average) * (points.at<double>(i, 1) - y_average);
        m1.at<double>(1,1) += (points.at<double>(i, 1) - y_average) * (points.at<double>(i, 1) - y_average);

        m2.at<double>(0,0) += (points.at<double>(i, 0) - x_average) * (points.at<double>(i, 2) - z_average);
        m2.at<double>(1,0) += (points.at<double>(i, 1) - y_average) * (points.at<double>(i, 2) - z_average);
    }
#ifdef DEBUG
    cout << m1 << endl;
    cout << m2 << endl;
#endif
    //calculate inverse
    double det = points.at<double>(0,0) * points.at<double>(1,1) - points.at<double>(1,0) * points.at<double>(0,1);
    m1_x.at<double>(0,0) = m1.at<double>(0,0) / det;
    m1_x.at<double>(0,1) = m1.at<double>(0,1) / det;
    m1_x.at<double>(1,0) = m1.at<double>(1,0) / det;
    m1_x.at<double>(1,1) = m1.at<double>(1,1) / det;

    Mat AB = m1_x * m2;
    // double C = z_average - AB.at<double>(0,0) * x_average - AB.at<double>(1,0) * y_average;
    // result.at<double>(0,0) = AB.at<double>(0,0);
    // result.at<double>(1,0) = AB.at<double>(1,0);
    // result.at<double>(2,0) = z_average - AB.at<double>(0,0) * x_average - AB.at<double>(1,0) * y_average;

    A = AB.at<double>(0,0);
    B = AB.at<double>(1,0);
    C = z_average - AB.at<double>(0,0) * x_average - AB.at<double>(1,0) * y_average;

#ifdef DEBUG
    cout << m1_x << endl;
    cout << AB << endl;
    // cout << result << endl;
#endif
}

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
    cout << points.at<double>(100, 1) << endl;
#endif
    input.close( );

    //take average for all equations
    double x_average = 0.0;
    double y_average = 0.0;
    double z_average = 0.0;
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
    //z = Ax + By + C
    // Mat A(3, 1, CV_32FC1);
    // Mat B(3, 1, CV_32FC1);
    // Mat C(3, 1, CV_32FC1);
    Mat result(3, 1, CV_32FC1);
    double A, B, C;
    fit_plane(A, B, C, m, points, x_average, y_average, z_average);

    cout << "Plane: z = (" << A << ")x + (" << B << ")y + (" << C << ")" << endl;
    //convert to Ax + By + Cz = 1
    double A_x, B_y, C_z;
    A_x = -A/C;
    B_y = -B/C;
    C_z = 1/C;
    cout << "   (" << A_x << ")x + (" << B_y << ")y + (" << C_z << ")z" << " = 1" << endl;

    //distance from origin to plane
    double d = (-1.0) / sqrt(A_x*A_x + B_y*B_y + C_z*C_z);
    cout << "Distance: " << d << endl;
    return 0;
}
