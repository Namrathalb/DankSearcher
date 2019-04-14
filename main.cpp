#include <iostream>
#include <string>
#include <sstream>
#include <filesystem>

#define LOG(x) std::cout << x << std::endl;

#define ERROR_BADARG  1
#define ERROR_BADDF   1

#define DEFAULT_SEARCH "C:\\"
#define FLAG_PATH "-p"

namespace FileSystem = std::experimental::filesystem;

// Usage: danksearch filename [-p pathToSearch]
int main(int argc, char** argv)
{
	// Checking user input
	if (argc != 2 && argc != 4)
	{
		LOG("Usage: danksearch filename [-p pathToSearch]");
		return ERROR_BADARG;
	}

	std::string file = argv[1];
	FileSystem::path path(DEFAULT_SEARCH);

	// If we have 4 arguments and using the -p flag, set path
	if (argc == 4 && strncmp(argv[2], FLAG_PATH, 2) == 0)
	{
		path = argv[3];
	}

	// Check if directory exists
	if (!FileSystem::exists(path))
	{
		LOG("No such directory \"" << path << "\" exists.");
		return ERROR_BADDF;
	}

	// Get full file path
	std::stringstream ss;
	ss << path << "\\" << file;

	// Check if file exists
	if (!FileSystem::exists(ss.str()))
	{
		LOG("No such file \"" << file << "\" exists in specified directory.");
		return ERROR_BADDF;
	}

	LOG("Successfully found file \"" << file << "\" in directory \"" << path << "\".");

	return EXIT_SUCCESS;
}
