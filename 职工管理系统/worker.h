#pragma once
#include<iostream>
#include<string>
using namespace std;


class worker
{
public:

	//显示个人信息
	virtual void showinfo() = 0;

	//获取岗位名称
	virtual string getdeptname() = 0;




	//职工编号
	int m_id;
	//name
	string m_name;
	//部门编号
	int m_deptid;

	virtual ~worker()=default;


};
