#pragma once
#include<iostream>
#include"worker.h"
using namespace std;

//经理类
class manager :public worker
{
public:

	//构造函数
	manager(int id, string name, int did);

	//显示个人信息
	virtual void showinfo();

	//获取岗位名称
	virtual string getdeptname();

	//析构函数
	virtual ~manager();


};