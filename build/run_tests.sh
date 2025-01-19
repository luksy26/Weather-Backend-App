#!/bin/bash

# Output file location
output_file=~/Desktop/times_non_patterns.txt

# Loop over num_clients from 10 to 10000, multiplying by 10 each time
for num_clients in 10 100 1000 10000; do
    # Loop over num_updates from 100 to 100000, multiplying by 10 each time
    for num_updates in 1000 10000 100000; do
        echo Running for $num_clients - $num_updates
        echo 'Running latency...'
        # Run test_latency and capture its output
        latency_result=$(./test_latency $num_clients $num_updates)

        echo 'Running throughput...'
        # Run test_throughput and capture its output
        throughput_result=$(./test_throughput $num_clients $num_updates)

        # Write results to the output file with num_clients, num_updates, test_latency output, and test_throughput output
        echo "$num_clients $num_updates $latency_result $throughput_result" >> $output_file
    done
done
