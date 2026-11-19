#include"employee.h"


employee::employee(int id, string name, int did)
{
	this->m_id = id;
	this->m_name = name;
	this->m_deptid = did;
}




//显示个人信息
void employee::showinfo()
{
	cout << "职工编号：" << this->m_id
		<< "\t职工姓名：" << this->m_name
		<< "\t岗位：" << this->getdeptname()
		<< "\t岗位职责：完成经理交给的任务" << endl;
}

//获取岗位名称
string employee::getdeptname()
{
	return string("员工");

}