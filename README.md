uptime-cgo

A small Go command-line utility that uses cgo/C to obtain system uptime on macOS and Linux.

Build and run
- From the project root:
  - Build: `go build`
  - Run: `go run .`
- Use `-json` to output uptime in JSON, e.g. `go run . -json`

Notes
- Requires a C compiler and cgo (default with Go toolchain).
- macOS uses `sysctl` and Linux uses `sysinfo`. The C code returns malloc'd strings which the Go code frees.
