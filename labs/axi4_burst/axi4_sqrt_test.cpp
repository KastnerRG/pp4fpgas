#include "axi4_sqrt.hpp"
#include<iostream>
int main()
{
float in[50],out[50];
int ct=0;
int length=30;
for(int i=0;i<length;i++)
	in[i]=(float)(i*i);
axi4_sqrt(in,out,30);
for(int i=0;i<length;i++)
{
	if(out[i]==(float)i)
		ct++;
}
	if(ct==length)
	std::cout<<"PASS"<<std::endl;
else
	std::cout<<"FAIL"<<std::endl;
	return 0;
}
