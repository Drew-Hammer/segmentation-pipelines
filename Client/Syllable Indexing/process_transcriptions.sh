#!/bin/bash

# Step 0: Compile the C++ programs
echo "Compiling..."
g++ -o textIsolator textIsolator.cpp
g++ -o prependUtteranceID prependUtteranceID.cpp
g++ -std=c++17 -o generateCSV generateCSV.cpp

# Check if compilation was successful
if [ $? -ne 0 ]; then
    echo "Compilation failed. Exiting."
    exit 1
fi

# Step 1: Run the text isolator
echo "--- Running text isolator... ---"
./textIsolator TRANS.txt isolated.utf8

# Step 2: Run the segmenter
echo "--- Running segmenter... ---"
../../segment.sh pku isolated.utf8 UTF-8 0 > isolated_and_segmented.txt

# Step 3: Prepend Utterance IDs
echo "--- Prepending Utterance IDs... ---"
./prependUtteranceID TRANS.txt isolated_and_segmented.txt segmented_with_ids.txt

# Step 4: Generate utterance CSV
echo "--- Generating utterance CSV... ---"
./generateCSV segmented_with_ids.txt

# Step 5: Clean up intermediate files
echo "--- Cleaning Up... ---"
find . -type f ! -name 'TRANS.txt' \( -name '*.txt' -o -name 'textIsolator' -o -name 'prependUtteranceID' -o -name 'generateCSV' -o -name '*.utf8' \) -exec rm -f {} +

echo " "
echo "Processing complete. Output saved to 'output/' directory."
