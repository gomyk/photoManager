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
	if(part1.PhotoName == this->PhotoName)	// �����̸� ��
		return true;
	else 
		return false;
}

// '>' operator overloading
bool StringRecord::operator>(StringRecord &part1)
{
	if(this->PhotoName > part1.PhotoName)		// �����̸� ��
		return true;
	else 
		return false;
}

// '<' operator overloading


bool StringRecord::operator <(StringRecord &part1)
{
	if(this->PhotoName < part1.PhotoName)		// �����̸� ��
		return true;
	else 
		return false;
}


// '=' operator overloading
StringRecord StringRecord::operator =(StringRecord &part2)
{
	this->PhotoName = part2.PhotoName;			// ���� �̸�Ȯ��
	return *this;
}
