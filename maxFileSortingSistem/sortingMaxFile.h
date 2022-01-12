#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "utility.h"

#ifndef MAXFILESORTING_H
#define MAXFILESORTING_H

class MaxSort
{
public:
	MaxSort () ;
	MaxSort (const std::string&) ;
	~MaxSort ();
	MaxSort (const MaxSort&) = delete ;
	MaxSort operator= (const MaxSort&) = delete ;
	MaxSort operator= (const MaxSort&&) = delete ;
	MaxSort (const MaxSort&&) = delete ;
public:
	void setFileName(const std::string&);
	std::string getFileName()const;
	void sortFile();
private:
	void marg();
	bool endAllFile();
	size_t findMaxIndex(const std::vector<size_t>&);
	void clear();
private:
	std::string m_fileName ;
	size_t m_countFile ;
	std::vector<std::fstream> m_tmpFile ;
	std::fstream m_fin;
};

#endif /*MAXFILESORTING_H*/
