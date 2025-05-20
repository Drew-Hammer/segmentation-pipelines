# server.py
from flask import Flask, request, jsonify
import librosa
import numpy as np

app = Flask(__name__)

@app.route('/mel', methods=['POST'])

# Here is where we're calling the python mel specttrogram function generator for simplicity 
def get_mel():
    file = request.files['file']
    y, sr = librosa.load(file, sr=16000)
    mel = librosa.feature.melspectrogram(y=y, sr=sr, n_mels=128)
    mel_db = librosa.power_to_db(mel, ref=np.max)

    return jsonify(mel_db.tolist())  

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5050)
