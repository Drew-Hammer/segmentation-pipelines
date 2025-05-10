# Dataset Processing Workflow

This project processes a dataset transcription file through a series of steps to generate segmented utterance arrays. Follow the instructions below to use the provided tools.


## Disclaimer
The easiest way to process the dataset is to:

1. Place `TRANS.txt` format: `UtteranceID SpeakerID Transcription` in the Convident Tools directory and run the following command in the terminal:
```bash
./process_transcriptions.sh
```
This will automatically execute all the steps and generate the final output file, `utterance_arrays.json`.

2. Place a transcription directory (each utterance as a txt file, filename UtteranceID.txt) in the Convident Tools directory and run the following command in the terminal:
```bash
./preprocessing.sh
```
This will automatically execute all the steps and generate the final output file, `utterance_arrays.json`.

## Detailed Steps
If you prefer to run the steps manually, follow the sytem below and customize your parsing tools:

1. **Pass `TRANS.txt` to `textIsolator.cpp`**
   - Compile and run `textIsolator.cpp` to process `TRANS.txt` and generate `isolated.utf8`.
   - Example:
     ```bash
     g++ textIsolator.cpp -o textIsolator
     ./textIsolator TRANS.txt isolated.utf8
     ```
   - Output: `isolated.utf8`

2. **Segment the Isolated File**
   - Use the `segment.sh` script to segment the `isolated.utf8` file.
   - Command:
     ```bash
     ./segment.sh pku isolated.utf8 UTF-8 0 > isolated_and_segmented.txt
     ```
   - Output: `isolated_and_segmented.txt`

3. **Pass `isolated_and_segmented.txt` and `TRANS.txt` to `prependUtteranceID.cpp`**
   - Compile and run `prependUtteranceID.cpp` to process the segmented file and add utterance IDs.
   - Example:
     ```bash
     g++ prependUtteranceID.cpp -o prependUtteranceID
     ./prependUtteranceID TRANS.txt isolated_and_segmented.txt segmented_with_ids.txt
     ```
   - Output: `segmented_with_ids.txt`

4. **Pass `segmented_with_ids.txt` to `utteranceArrays.cpp`**
   - Compile and run `utteranceArrays.cpp` to process the file and generate the final JSON output.
   - Example:
     ```bash
     g++ utteranceArrays.cpp -o utteranceArrays
     ./utteranceArrays segmented_with_ids.txt utterance_arrays.json
     ```
   - Output: `utterance_arrays.json`

## Output
- The final output will be a JSON file (`utterance_arrays.json`) containing the processed utterance arrays.

## Notes
- Ensure all required files and scripts are in the same directory.
- The `segment.sh` script requires the `pku  {or ctb (for Chinese Treebank)}` segmentation model to function correctly.