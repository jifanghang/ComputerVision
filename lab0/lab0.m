## Copyright (C) 2017 Fanghang Ji
## 
## This program is free software; you can redistribute it and/or modify it
## under the terms of the GNU General Public License as published by
## the Free Software Foundation; either version 3 of the License, or
## (at your option) any later version.
## 
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
## 
## You should have received a copy of the GNU General Public License
## along with this program.  If not, see <http://www.gnu.org/licenses/>.

## -*- texinfo -*- 
## Reads image and extract the RGB channels of the image.
## Plot the RGB histogram of the image.
## Compute the hue component.
## Plot histogram of hue component.

## Author: Fanghang Ji <Jamie@Fanghangs-Mac.wlan.jacobs-university.de>
## Created: 2017-09-13

pkg load image

input = imread('CV_lab_0_colors/peppers.png');
%imshow(input);

% extract RGB channels
R = input(:, :, 1);
G = input(:, :, 2);
B = input(:, :, 3);

% get histValues for each channel
[yRed, x] = imhist(R);
[yGreen, x] = imhist(G);
[yBlue, x] = imhist(B);

% plotting them together
plot(x, yRed, 'r', x, yGreen, 'g', x, yBlue, 'b'), legend('R', 'G', 'B');
%stem(x, yRed, 'r', x, yGreen, 'g', x, yBlue, 'b');

% RGB to HSV
input_hsv = rgb2hsv(input);







