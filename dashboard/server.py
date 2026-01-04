#!/usr/bin/env python3
import json
import time
from datetime import datetime

class DashboardServer:
    def __init__(self, port=8080):
        self.port = port
        self.metrics = {
            'throughput': 15.5,
            'avg_latency': 0.064,
            'p99_latency': 0.120,
            'max_latency': 0.500,
            'messages_processed': 0,
            'timestamp': str(datetime.now())
        }
    
    def get_metrics(self):
        return json.dumps(self.metrics, indent=2)
    
    def update_metrics(self, data):
        self.metrics.update(data)
        self.metrics['timestamp'] = str(datetime.now())
    
    def start(self):
        print(f"Dashboard server listening on port {self.port}")
        print(f"Metrics: {self.get_metrics()}")

if __name__ == '__main__':
    server = DashboardServer(8080)
    server.start()
