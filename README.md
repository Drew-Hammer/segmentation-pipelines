# Chinese Text Segmentation Pipelines

This directory contains two main pipelines for processing Chinese text: Word Indexing and Syllable Indexing. Each pipeline consists of two sub-pipelines: preprocessing and transcription processing.

## Directory Structure

```
Segmentation/
├── stanford-segmenter-4.2.0/
│   ├── stanford-segmenter-4.2.0.jar
│   ├── segment.sh
│   └── [other segmenter files]
└── Pipelines/
    ├── Word Indexing/
    │   ├── preprocessing.sh
    │   ├── process_transcriptions.sh
    │   └── [other pipeline files]
    └── Syllable Indexing/
        ├── preprocessing.sh
        ├── process_transcriptions.sh
        └── [other pipeline files]
```

## Input Methods

The pipelines support two methods of input. The required directories/files should be created and placed in the pipeline directory before running:

1. **Directory of Text Files**
   - Create and place the `SLR38 target_directory/` in the pipeline directory
   - Each file should contain one utterance
   - Files should be named with unique identifiers (e.g., `20170001P00444A0063.txt`)
   - All files must be in UTF-8 encoding

2. **Single Transcription File**
   - Create and place `TRANS.txt` in the pipeline directory
   - Each line should contain one utterance
   - File must be in UTF-8 encoding
   - Example format:
     ```
     utterance1
     utterance2
     utterance3
     ```

## Pipeline Details

### 1. Word Indexing Pipeline

#### A. Preprocessing Pipeline (`preprocessing.sh`)

1. **Setup**:
   ```bash
   cd Word\ Indexing/
   chmod +x preprocessing.sh
   ```

2. **Input Requirements**:
   - Choose one of the two input methods:
     - Place `SLR38 target_directory/` in the current directory
     - OR place `TRANS.txt` in the current directory
   - Files should be in UTF-8 encoding
   - Each file/line should contain one utterance

3. **Execution**:
   ```bash
   ./preprocessing.sh
   ```

4. **What it does**:
   - Extracts text from input files using `textIsolatorForPreprocessing.cpp`
   - Prepends utterance IDs using `prependUtteranceID.cpp`
   - Combines transcriptions using `combineTranscriptions.cpp`
   - Performs post-segmentation processing using `preprocess_post_segmentation.cpp`

#### B. Transcription Processing Pipeline (`process_transcriptions.sh`)

1. **Setup**:
   ```bash
   chmod +x process_transcriptions.sh
   ```

2. **Execution**:
   ```bash
   ./process_transcriptions.sh
   ```

3. **What it does**:
   - Creates utterance arrays using `utteranceArrays.cpp`
   - Generates word-level indices
   - Creates CSV files for each word
   - Maintains original Chinese characters in directory names

### 2. Syllable Indexing Pipeline

#### A. Preprocessing Pipeline (`preprocessing.sh`)

1. **Setup**:
   ```bash
   cd Syllable\ Indexing/
   chmod +x preprocessing.sh
   ```

2. **Input Requirements**:
   - Choose one of the two input methods:
     - Place `SLR38 target_directory/` in the current directory
     - OR place `TRANS.txt` in the current directory
   - Files should be in UTF-8 encoding
   - Each file/line should contain one utterance

3. **Execution**:
   ```bash
   ./preprocessing.sh
   ```

4. **What it does**:
   - Extracts text from input files using `textIsolatorForPreprocessing.cpp`
   - Prepends utterance IDs using `prependUtteranceID.cpp`
   - Combines transcriptions using `combineTranscriptions.cpp`
   - Performs post-segmentation processing using `preprocess_post_segmentation.cpp`

#### B. Transcription Processing Pipeline (`process_transcriptions.sh`)

1. **Setup**:
   ```bash
   chmod +x process_transcriptions.sh
   ```

2. **Execution**:
   ```bash
   ./process_transcriptions.sh
   ```

3. **What it does**:
   - Creates syllable-level indices
   - Generates CSV files for each syllable
   - Maintains original Chinese characters in directory names

## Output Structure

### Word Indexing Output
```
Word_Indexing/
├── utterance_arrays.json
└── word_directories/
    ├── word_1/
    │   └── indices.csv
    ├── word_2/
    │   └── indices.csv
    └── ...
```

The `utterance_arrays.json` file contains an array of utterances with their word indices:
```json
[
  {
    "utterance": [
      {
        "index": 0,
        "word": "高"
      },
      {
        "index": 1,
        "word": "德"
      }
    ],
    "utterance_id": "37_5622_20170913203118.wav"
  }
]
```

### Syllable Indexing Output
```
Syllable_Indexing/
├── syllable_1/
│   └── indices.csv
├── syllable_2/
│   └── indices.csv
└── ...
```

## CSV File Format

### Syllable Indexing CSV Format
Each CSV file contains utterance IDs and indices with no header row:
```csv
20170001P00444A0063,1
20170001P00444A0064,2
```

## Common Components

### Core Files
- `textIsolator.cpp`: Extracts text from input files
- `textIsolatorForPreprocessing.cpp`: Preprocessing text isolator
- `prependUtteranceID.cpp`: Adds utterance IDs to text
- `combineTranscriptions.cpp`: Combines multiple transcriptions
- `preprocess_post_segmentation.cpp`: Post-segmentation processing

### Word Indexing Specific
- `utteranceArrays.cpp`: Creates arrays of utterances
- `innovation.py`: Python script for additional processing
- `utterance_arrays.json`: JSON file containing utterance arrays

## Troubleshooting Guide

### Common Issues and Solutions

1. **Permission Denied**
   ```bash
   chmod +x *.sh
   ```

2. **Compilation Errors**
   ```bash
   g++ -std=c++11 your_file.cpp -o your_file
   ```

3. **Encoding Issues**
   - Ensure all input files are UTF-8 encoded
   - Use `file -I filename` to check encoding
   - Convert if needed: `iconv -f original_encoding -t UTF-8 input_file > output_file`

4. **Stanford Segmenter Issues**
   - Verify segmenter installation
   - Check segmenter path in scripts
   - Ensure Java is installed and configured

## Best Practices

1. **Before Running**:
   - Backup your data
   - Verify file permissions
   - Check input file encoding
   - Compile all C++ files
   - Choose the appropriate input method based on your data format
   - Ensure input directories/files are in place

2. **During Processing**:
   - Monitor disk space
   - Check log files
   - Verify output structure

3. **After Processing**:
   - Validate CSV files
   - Check directory structure
   - Verify Chinese character preservation

## Contributing

Feel free to submit issues and enhancement requests! When contributing:
1. Fork the repository
2. Create a feature branch
3. Submit a pull request

## License

This project is licensed under the MIT License - see the LICENSE file for details. 