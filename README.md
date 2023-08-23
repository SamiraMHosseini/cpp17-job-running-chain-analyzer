# cpp-job-running-chain-analyzer
This program reads job data from a string and analyzes the relationship between the jobs to generate summary reports.
The jobs are represented by three values: job ID, runtime in seconds, and next job ID. Various functions are employed to parse, convert, analyze, and output the data, demonstrating modular programming practices. 
The use of standard library features like std::format, std::unordered_map, std::string_view and std::span showcases modern C++ capabilities.

# The code provided utilizes several features introduced in C++17 and C++20. Here are some brief notes on those features:

Structured Bindings: This allows the convenient unpacking of elements from tuples, pairs, arrays, or other aggregate data types. It's used in the code to extract multiple values from a pair or tuple and bind them to variable names, e.g., auto [runtime_in_seconds, possible_next_job_id] = pair.second;.

std::string_view: std::string_view provides a non-owning reference to a string or a substring. It's used to enable efficient parsing of the CSV input without unnecessary copying of substrings.

std::span: This C++20 feature provides a view over a contiguous sequence of objects. It's used in the parse_jobs function to accept a view of a vector of integers, offering more flexibility in calling the function with different kinds of contiguous containers.

std::unordered_map: While not new in C++17, the code snippet makes extensive use of unordered maps to store and organize job data. It's a useful data structure for efficient lookup operations.

std::format: This C++20 feature provides a type-safe and extensible way to format text, similar to printf. The code uses it to construct human-readable strings representing job summaries, e.g., std::format("{:02}:{:02}:{:02}", hrs, mins, secs).

Class Template Argument Deduction (CTAD): This allows the compiler to deduce class template arguments from the constructor or aggregate initialization, enabling cleaner syntax. It is implicitly used in the code with standard containers like std::vector and std::pair.

Copy Elision/Mandatory Return Value Optimization (RVO): The code is written in such a way that it can benefit from return value optimization, a compiler optimization technique that avoids unnecessary copy or move operations for return values. It's mentioned in the comments related to functions returning vectors and unordered_maps.

These features help make the code more expressive, concise, and efficient. C++17's enhancements support modern programming practices, facilitating both readability and performance.
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
