run: 
	go run .

build:
	go build -o uptime-cgo && sudo movebin uptime-cgo