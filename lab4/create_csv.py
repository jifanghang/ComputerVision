# Retrieved from 'https://docs.opencv.org/2.4/modules/contrib/doc/facerec/facerec_tutorial.html#appendixft'
# Modified by Fanghang Ji on Oct 18th 2017
#!/usr/bin/env python

import sys
import os.path
import re

# This is a tiny script to help you creating a CSV file from a face
# database with a similar hierarchie:
#
#  philipp@mango:~/facerec/data/at$ tree
#  .
#  |-- README
#  |-- s1
#  |   |-- 1.pgm
#  |   |-- ...
#  |   |-- 10.pgm
#  |-- s2
#  |   |-- 1.pgm
#  |   |-- ...
#  |   |-- 10.pgm
#  ...
#  |-- s40
#  |   |-- 1.pgm
#  |   |-- ...
#  |   |-- 10.pgm
#

if __name__ == "__main__":

    if len(sys.argv) != 2:
        print ("usage: create_csv <base_path>")
        sys.exit(1)

    BASE_PATH=sys.argv[1]
    SEPARATOR=";"

    label = 0
    for dirname, dirnames, filenames in os.walk(BASE_PATH):
        for subdirname in dirnames:
            subject_path = os.path.join(dirname, subdirname)
            for filename in os.listdir(subject_path):
                abs_path = "%s/%s" % (subject_path, filename)
                s = ''.join(x for x in filename if x.isdigit())+'0'
                label = int(s)/10
                print ("%s%s%d" % (abs_path, SEPARATOR, label))
            #label = label + 1


