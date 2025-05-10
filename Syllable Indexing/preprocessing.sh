#!/bin/bash

# Step 0: Compile the C++ programs
echo "Compiling..."
g++ -std=c++17 combineTranscriptions.cpp -o combine_transcriptions
g++ -o textIsolator textIsolatorForPreprocessing.cpp
g++ -o postSegmentation preprocess_post_segmentation.cpp
g++ -std=c++17 -o generateCSV generateCSV.cpp

# Check if compilation was successful
if [ $? -ne 0 ]; then
    echo "Compilation failed. Exiting."
    exit 1
fi

# Step 1: Combine transcriptions
echo "--- Combining transcriptions... ---"
./combine_transcriptions ./SLR38\ target_directory 

# Step 2: Run the text isolator
echo "--- Running text isolator... ---"
./textIsolator combined_transcriptions.txt isolated.utf8

# Step 3: Run the segmenter
echo "--- Running segmenter... ---"
../../segment.sh pku isolated.utf8 UTF-8 0 > isolated_and_segmented.txt

# Step 4: Prepend Utterance IDs
echo "--- Prepending Utterance IDs... ---"
./postSegmentation combined_transcriptions.txt isolated_and_segmented.txt segmented_with_ids.txt

# Step 5: Generate CSV files
echo "--- Generating CSV files... ---"
./generateCSV segmented_with_ids.txt

# Step 6: Clean up intermediate files
echo "--- Cleaning Up... ---"
find . -maxdepth 1 -type f -name '*.txt' ! -name 'TRANS.txt' -exec rm -f {} +
find . -maxdepth 1 -type f -name '*.utf8' -exec rm -f {} +
rm -f combine_transcriptions textIsolator postSegmentation generateCSV

echo " "
echo "Processing complete. Output saved to 'output/' directory."