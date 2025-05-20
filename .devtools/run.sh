#!/bin/bash

# Exit immediately if a command exits with a non-zero status
set -e

echo "🛠️  Building Docker image for server..."
docker build -t mel-server .

echo "🚀 Starting Flask server in Docker (port 5050)..."
# Run server in background with automatic removal
docker run -d --rm -p 5050:5050 --name mel_server_container mel-server &
SERVER_PID=$!

# Wait for server to start (adjust if needed)
echo "⏳ Waiting for server to start..."
sleep 2

echo ""
echo ""
echo "Running C++ client script..."
# Replace with the right client script 
g++ ../Client/main.cpp -o client -lcurl && ./client

# Optionally stop the server container (if not --rm or you want manual control)
echo "🧼 Stopping Flask server container..."
docker stop mel_server_container > /dev/null || echo "Container already stopped."

echo "🧹 Removing client binary..."
rm -f client

echo "✅ Done."
