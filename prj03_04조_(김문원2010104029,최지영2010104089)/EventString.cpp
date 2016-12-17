#include "EventString.h"


StringRecord::StringRecord(void)
{
}


StringRecord::~StringRecord(void)
{
}

// '==' operator overloading
bool StringRecord::operator==(StringRecord &part1)
{	
	if(part1.PhotoName == this->PhotoName)	// 사진이름 비교
		return true;
	else 
		return false;
}

// '>' operator overloading
bool StringRecord::operator>(StringRecord &part1)
{
	if(this->PhotoName > part1.PhotoName)		// 사진이름 비교
		return true;
	else 
		return false;
}

// '<' operator overloading


bool StringRecord::operator <(StringRecord &part1)
{
	if(this->PhotoName < part1.PhotoName)		// 사진이름 비교
		return true;
	else 
		return false;
}


// '=' operator overloading
StringRecord StringRecord::operator =(StringRecord &part2)
{
	this->PhotoName = part2.PhotoName;			// 사진 이름확인
	return *this;
}
