# cpp-job-running-chain-analyzer
This program reads job data from a string and analyzes the relationship between the jobs to generate summary reports.
The jobs are represented by three values: job ID, runtime in seconds, and next job ID. Various functions are employed to parse, convert, analyze, and output the data, demonstrating modular programming practices. 
The use of standard library features like std::format, std::unordered_map, std::string_view and std::span showcases modern C++ capabilities.

# Key Features

# CSV Parsing: 

The program can accept a raw CSV string of jobs and convert it into a structured data format.
Job Chain Analysis: Utilizes an algorithm to analyze the sequence of jobs, identifying starting and ending points, total runtime, and average time per job in the chain.

# Time Formatting: 
Converts raw seconds into a human-readable time format (hours, minutes, seconds).

# Report Generation: 
Creates comprehensive summaries of each job chain, sorted in a specific order, ready for easy analysis or visualization.

# Exception Handling: 
Implementing robust error handling to deal with incorrect or malformed input.

This repository offers a comprehensive solution for anyone needing to analyze a complex sequence of interdependent jobs or tasks. 
The clear structuring of the code and usage of modern C++ features makes it a great example for learning or adaptation into larger systems.
