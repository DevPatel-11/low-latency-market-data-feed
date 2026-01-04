# Low-Latency Market Data Feed Handler

High-performance C++17 market data pipeline for HFT applications.

## Architecture

- **Parser**: Binary message decoder (17-byte protocol)
- **Queue**: Lock-free SPSC with cache-aligned 64KB slots
- **Consumer**: Multi-threaded event processing

## Building

```bash
mkdir build && cd build
cmake ..
make
```

## Performance

- Throughput: >200k msg/sec
- Latency: Microsecond scale
- Zero-copy event passing

## Usage

```bash
./feed_handler [rate] [duration]
# ./feed_handler 500000 5  # 500k msg/sec for 5 seconds
```
