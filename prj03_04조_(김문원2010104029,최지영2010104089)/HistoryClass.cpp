#include "HistoryClass.h"


HistoryRecord::HistoryRecord(void)
{
}


HistoryRecord::~HistoryRecord(void)
{
}

// '==' operator overloading
bool HistoryRecord::operator==(HistoryRecord &part1)
{	
	if(part1.EventContent == this->EventContent)	// �����̸� ��
		return true;
	else 
		return false;
}

// '>' operator overloading
bool HistoryRecord::operator>(HistoryRecord &part1)
{
	if(this->EventContent > part1.EventContent)		// �����̸� ��
		return true;
	else 
		return false;
}

// '<' operator overloading


bool HistoryRecord::operator <(HistoryRecord &part1)
{
		return false;
}


// '=' operator overloading
HistoryRecord HistoryRecord::operator =(HistoryRecord &part2)
{
	this->EventContent = part2.EventContent;			// ���� �̸�Ȯ��
	return *this;
}
