#ifndef __DIRECTORY_HXX__
#define __DIRECTORY_HXX__

#include <dirent.h>
#include <cstdio>
#include <fstream>
#include <string>
#include <stdexcept>

class DirectoryException: public std::runtime_error {
public:
	DirectoryException(std::string what) : runtime_error(what){}
};

class Directory {
public:
	Directory(char* path);
	Directory(std::string path);

	// Member functions
	void open();
	void close();
	void rename();

	// Member variables
	std::string path;
	DIR* dir = NULL;
	struct dirent* props = NULL;

protected:
	static std::string ext(std::string fn);
	static bool exists(std::string fn);
	static std::string name(int count);
};

Directory::Directory(char* path) {
	this->path = path;	
}

Directory::Directory(std::string path) {
	this->path = path;
}

std::string Directory::ext(std::string fn) {
	size_t pos = fn.rfind('.');
	if(pos != std::string::npos)
		return fn.substr(pos);
	else
		return "";
}

std::string Directory::name(int count) {
	char filename[256];
	snprintf(filename, 255, "%04d", count);
	return std::string(filename);
}

bool Directory::exists(std::string fn) {
		std::ifstream handle(fn);
		return handle.good();
}

void Directory::open() {
	this->dir = opendir(this->path.c_str());
	if(this->dir == NULL)
		throw DirectoryException("Opening directory failed.");
}

void Directory::close() {
	closedir(this->dir);
}

void Directory::rename() {
	int count = 0;
	int success = 0;
	int fail = 0;

	while((this->props = readdir(this->dir)) != NULL) {
		std::string name = this->props->d_name;

		if(name == "." or name == "..")
			continue;

		std::string suffix = this->ext(name);
		std::string old = (this->path + "/" + name);
		std::string newf = (this->path + "/" + this->name(count) + suffix);

		if(this->exists(newf)) {
			++fail;
			continue;
		}

		if(std::rename(old.c_str(), newf.c_str()) == 0) {
			printf("%s -> %s [OK]\n",old.c_str(), newf.c_str());
			++success;
		}

		else {
			printf("%s -> %s [FAIL - %d]\n",old.c_str(), newf.c_str(), errno);
			++fail;
		}

		++count;
	}

	printf("Operated on %d files.\n", count);
	printf("%d successes, %d failures.\n", success, fail);
}

#endif
