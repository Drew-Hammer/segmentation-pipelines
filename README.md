# Chinese Text Segmentation and Indexing Pipelines

This repository contains a set of pipelines for processing Chinese text, including word segmentation, syllable indexing, and word indexing. The pipelines are designed to work with the Stanford Chinese Segmenter and provide structured output in CSV format.

## Project Structure

```
.
├── Word Parsing/
│   ├── Segmentation/
│   │   ├── Pipelines/
│   │   │   ├── Word Indexing/
│   │   │   └── Syllable Indexing/
│   │   └── stanford-segmenter-4.2.0/
│   └── DATASETS/
```

## Prerequisites

- C++ compiler (g++ or clang++)
- Python 3.x
- Stanford Chinese Segmenter 4.2.0
- Make sure you have the required dependencies installed:
  - nlohmann/json (included in the repository)
  - Standard C++ libraries

## Pipeline Components

### 1. Word Indexing Pipeline

The Word Indexing pipeline processes Chinese text to create word-level indices and corresponding CSV files.

#### Usage:

1. Place your input text files in the appropriate directory
2. Run the preprocessing script:
   ```bash
   cd Word\ Indexing/
   ./preprocessing.sh
   ```
3. Process the transcriptions:
   ```bash
   ./process_transcriptions.sh
   ```

#### Output:
- Creates a directory structure organized by words
- Generates CSV files containing utterance IDs and word indices
- Maintains original Chinese characters in directory names

### 2. Syllable Indexing Pipeline

The Syllable Indexing pipeline processes Chinese text to create syllable-level indices and corresponding CSV files.

#### Usage:

1. Place your input text files in the appropriate directory
2. Run the preprocessing script:
   ```bash
   cd Syllable\ Indexing/
   ./preprocessing.sh
   ```
3. Process the transcriptions:
   ```bash
   ./process_transcriptions.sh
   ```

#### Output:
- Creates a directory structure organized by syllables
- Generates CSV files containing utterance IDs and syllable indices
- Maintains original Chinese characters in directory names

## File Descriptions

### Common Components

- `preprocessing.sh`: Initial preprocessing script for text files
- `process_transcriptions.sh`: Main processing script for transcriptions
- `textIsolator.cpp`: Extracts text from input files
- `textIsolatorForPreprocessing.cpp`: Preprocessing text isolator
- `prependUtteranceID.cpp`: Adds utterance IDs to text
- `combineTranscriptions.cpp`: Combines multiple transcriptions
- `preprocess_post_segmentation.cpp`: Post-segmentation processing

### Word Indexing Specific

- `utteranceArrays.cpp`: Creates arrays of utterances
- `innovation.py`: Python script for additional processing
- `utterance_arrays.json`: JSON file containing utterance arrays

## Output Format

The pipelines generate CSV files with the following structure:
- Each word/syllable has its own directory
- CSV files contain:
  - Utterance ID
  - Index information
  - Additional metadata

## Notes

- Make sure to compile the C++ files before running the scripts
- The Stanford Segmenter must be properly configured
- Input files should be in UTF-8 encoding
- Original Chinese characters are preserved in directory names

## Troubleshooting

If you encounter any issues:
1. Check file permissions on the shell scripts
2. Verify that all C++ files are compiled
3. Ensure the Stanford Segmenter is properly installed
4. Check input file encoding (should be UTF-8)

## Contributing

Feel free to submit issues and enhancement requests! 