
#if 1
#include <string_view>
#include <string>
#include <vector>
#include <iostream>
#include <span>
#include <unordered_map>
#include <format>
#include <algorithm>
#include <exception>

// Function to parse a CSV string into a vector of strings, useful for breaking down the input string
// C++17 feature - std::string_view 
std::vector<std::string> parse_csv(std::string_view str)
{

	std::vector<std::string> vect_of_string;
	size_t start{ 0 };
	size_t end = str.find(",");
	while (end != std::string_view::npos)
	{

		auto data = str.substr(start, (end - start));
		start = end + 1;
		end = str.find(",", start);
		vect_of_string.emplace_back(data);
	}
	vect_of_string.emplace_back(str.substr(start, (end - start)));

	// Enable it for debugging purposes
#if 0 
	// Raw data (jobs)
	std::cout << "Raw data (jobs):\n";
	for (const auto& str : vect_of_string)
	{
		std::cout << str << " ";
	}
	std::cout << '\n';
#endif
	return vect_of_string; // Return the vector of parsed strings (RVO: Return Value Optimization)
}

// Function to convert strings into integers, necessary for numeric calculations

std::vector<int> convert_strings_to_integers(const std::vector<std::string>& vect_of_string)
{
	std::vector<int> vect_of_int;
	for (const auto& item : vect_of_string)
	{
		try
		{
			vect_of_int.emplace_back(std::stoi(item));
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << '\n';
			throw; // re-throwing the exception for outer-scope handling
		}
	}

	// Enable it for debugging purposes
#if 0 
	for (const auto& item : vect_of_int)
	{
		std::cout << item << " ";
	}
	std::cout << '\n';
#endif
	return vect_of_int; // copy/move elision -  C++17 feature
}
// Function to parse jobs into a mapping structure, organizes the data into a usable format
// C++20 feature std::span
std::unordered_map<int, std::pair<int, int>> parse_jobs(std::span<int> vect)
{
	std::unordered_map<int, std::pair<int, int>> map_jobs; // IDs are unique so we don't need to have unordered_multimap

	for (size_t i = 0; i <= vect.size() - 3; i += 3)
	{
		map_jobs.emplace(vect[i], std::make_pair(vect[(i + 1)], vect[(i + 2)]));
	}

	// Enable it for debugging purposes
#if 0 

	for (const auto& pair : map_jobs)
	{
		auto output = std::format("job_id {}, runtime_in_seconds {}, next_job_id {}", pair.first, pair.second.first, pair.second.second);
		std::cout << output << '\n';
	}

#endif
	return map_jobs; // copy/move elision -  C++17 feature
}
// Function to convert seconds into a time format, ensures consistent time representation

std::string calculate_time_units(int seconds)
{
	if (seconds < 0)
		throw std::runtime_error("Time can't be negative!");
	auto temp = seconds / 60;
	auto secs = seconds % 60;
	auto mins = temp % 60;
	auto hrs = temp / 60;
	// C++20 feature std::format
	return (std::format("{:02}:{:02}:{:02}", hrs, mins, secs));  // copy/move elision -  C++17 feature

}
// Function to generate job chain reports, processes the job data to produce summary information

std::vector<std::pair<int, std::string>> generate_job_chain_report(std::unordered_map<int, std::pair<int, int>>& map_jobs)
{
	// An unordered_map is used for efficient lookup of job chain elements, 
	using JobType = std::unordered_map<int, std::pair<int, int>>;
	std::vector<std::pair<int, std::string>> vect_report;

	// Process each job and check if there's a chain
	for (auto& pair : map_jobs)
	{

		auto start_job = pair.first;
		int  last_job{};

		// C++17 feature - structured binding
		auto [runtime_in_seconds, possible_next_job_id] = pair.second; 

		auto numer_of_jobs{ 1 };
		int job_chain_runtime{ runtime_in_seconds };
		int average_job_time{};
		if (possible_next_job_id != 0)
		{
			do
			{
				JobType::iterator it = map_jobs.find(possible_next_job_id);
				if (it != map_jobs.end()) // There is a chain
				{
					
					auto next_job_id = it->first;
					auto runtime_in_seconds = it->second.first;
					possible_next_job_id = it->second.second;
	
					++numer_of_jobs;
					job_chain_runtime += runtime_in_seconds;
					last_job = next_job_id;
				}
				else
					break;
			} while (possible_next_job_id != 0);

			average_job_time = job_chain_runtime / numer_of_jobs;
			auto report_summary = std::format
			("-\nstart_job: {}\nlast_job: {}\nnumer_of_jobs: {}\njob_chain_runtime: {}\naverage_job_time: {}",
				start_job, last_job, numer_of_jobs, calculate_time_units(job_chain_runtime), calculate_time_units(average_job_time));
			// std::cout << report_summary << '\n';
			vect_report.emplace_back(average_job_time, report_summary);
		}
	}
	// Sorting jobs in descending order based on job_chain_runtime
	std::sort(vect_report.begin(), vect_report.end(), std::greater<>());

	// Enable it for debugging purposes
#if 0 
	for (const auto& job : final_result)
	{
		std::cout << job.second << '\n';
	}

#endif
	return vect_report; // copy/move elision -  C++17 feature
}

// Function to output job reports, prints the summaries to the console
void output_jobs_report_summary(const std::vector<std::pair<int, std::string>>& vect_report)
{
	std::cout << "Job running summary reports:\n";
	// C++17 feature - structured binding
	for (const auto& [_,second] : vect_report)
	{
		std::cout << second << '\n';
	}
}

// Main function to execute the program, includes exception handling for robust error management

int main() {

	std::string str = "1,60,23,2,23,3,3,12,0,23,30,0,4,51,2,5,120,3";

	// Sample input and output

	/*
	Raw jobs:
	#job_id,runtime_in_seconds,next_job_id
	1,60,23
	2,23,3
	3,12,0
	23,30,0
	4,51,2
	5,120,3

	Job running summary reports:
	-
	start_job: 5
	last_job: 3
	numer_of_jobs: 2
	job_chain_runtime: 00:02:12
	average_job_time: 00:01:06
	-
	start_job: 1
	last_job: 23
	numer_of_jobs: 2
	job_chain_runtime: 00:01:30
	average_job_time: 00:00:45
	-
	start_job: 4
	last_job: 3
	numer_of_jobs: 3
	job_chain_runtime: 00:01:26
	average_job_time: 00:00:28
	-
	start_job: 2
	last_job: 3
	numer_of_jobs: 2
	job_chain_runtime: 00:00:35
	average_job_time: 00:00:17
	*/
	//std::string str = "1,60,23,2,23,3,3,12,0,23,30,0";
	std::cout << "Raw jobs: \n" << str << '\n';
	try
	{
		std::vector<std::string> vect_of_string = parse_csv(str);
		std::vector<int> vect_of_int = convert_strings_to_integers(vect_of_string);
		std::unordered_map<int, std::pair<int, int>> map_jobs = parse_jobs(vect_of_int);
		std::vector<std::pair<int, std::string>> vect_report = generate_job_chain_report(map_jobs);
		output_jobs_report_summary(vect_report);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << '\n';
	}
	return 0;

}


#endif
