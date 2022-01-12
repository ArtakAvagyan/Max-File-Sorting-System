#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

#include "utility.h"
#include "sortingMaxFile.h"

MaxSort::MaxSort ()
{
	m_fileName += Utility::roomPath ;
	m_fileName += Utility::fileName ;
	m_fin.open( m_fileName , std::ios::in );
}


MaxSort::MaxSort (const std::string& fileName) 
	: m_fileName {fileName}
{
	m_fin.open( m_fileName , std::ios::in );
}

MaxSort::~MaxSort ()
{
	clear();
}

void MaxSort::clear()
{
	for (auto& it : m_tmpFile)
	{
		it.close();
	}
	m_tmpFile.clear();
}
void MaxSort::setFileName (const std::string& fileName)
{
	m_fileName = fileName;
	m_fin.open( m_fileName , std::ios::in );
}

std::string MaxSort::getFileName()const
{
	return m_fileName ;
}

void MaxSort::sortFile()
{
	if(!m_fin.is_open())
	{
		std::cout<< "in Class File don't open " << std::endl;
		return ;
	}
	
	char ch = Utility::firstTmpFileName;

	while(!m_fin.eof())
	{
		std::vector<size_t>vec;
		vec.reserve(Utility::for200MbFileSize);
		std::string tmpFileName;
		tmpFileName.push_back(ch);
		tmpFileName += Utility::extencion ;
		int index = ch - Utility::firstTmpFileName ;
		m_tmpFile.push_back(std::fstream(tmpFileName,std::ios::out));
		for (size_t i = 0 ; i < Utility::for200MbFileSize && (!m_fin.eof()) ; ++i )
		{
			std::string str;
			m_fin >> str;
			if (str == "" ) { break; }
			vec.push_back(std::stoll(str));
		}
		std::sort(vec.begin(),vec.end());
		for (size_t i = 0 ; i < vec.size() ; ++i )
		{
			 m_tmpFile[index] << vec[i];
			 m_tmpFile[index] << " ";
		}
		ch++;
	}
	m_countFile = m_tmpFile.size();
	clear();
	marg();

}

void MaxSort::marg()
{
	m_fin.close();
	m_fin.open( m_fileName , std::ios::out );
	char ch = Utility::firstTmpFileName;
	for (size_t i = 0 ; i < m_countFile ; ++i )
	{
		std::string tmpFileName ;
		tmpFileName.push_back(ch) ;
		tmpFileName += Utility::extencion ;
		m_tmpFile.push_back(std::fstream(tmpFileName,std::ios::in));
		++ch;
	}
	std::vector<size_t>vec;
	vec.resize(m_countFile);
	for ( size_t i = 0 ; i < m_countFile ; ++i )
	{
		std::string str;
		m_tmpFile[i] >> str;
		if (str == "") { continue; }
		vec[i] = std::stoll(str);
	}
	while(endAllFile())
	{
		size_t maxElemIndex = findMaxIndex(vec);
		m_fin << vec[maxElemIndex] ;
		m_fin << " " ;
		vec[maxElemIndex] = 0 ;
		if(!m_tmpFile[maxElemIndex].eof())
		{
			std::string str;
			m_tmpFile[maxElemIndex] >> str;
			if(str != "")
			{
				vec[maxElemIndex] = std::stoll(str);
			}
		}
		
	}

}

size_t MaxSort::findMaxIndex(std::vector<size_t>vec)
{
	size_t index = 0 ;
	for (size_t i = 1 ; i < vec.size() ; ++i)
	{
		if (vec[i] > vec[index])
		{
			index = i ;
		}
	}
	return index ;

}

bool MaxSort::endAllFile()
{
	bool result = false ;
	for (size_t i = 0 ; i < m_countFile ; ++i)
	{
		if(!m_tmpFile[i].eof())
		{
			result = true ;
		}
	}
	return result ;
}

int main()
{
	MaxSort maxFile;
	maxFile.sortFile();
}
