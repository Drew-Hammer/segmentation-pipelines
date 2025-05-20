# Makefile

.PHONY: run server client clean

# Run both server and client
run:
	@echo "▶️  Starting full system (Docker server + client)..."
	./run.sh

# Build and run just the Docker server
server:
	docker build -t mel-server .
	docker run --rm -p 5050:5050 mel-server

# Run just the CPP client
client:
	g++ ../Client/main.cpp -o client -lcurl && ./client

# Clean up any stopped containers/images
clean:
	docker system prune -f
