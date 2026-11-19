#pragma once   //防止头文件重复包含
#include<iostream>
#include"worker.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"
#include<fstream>
#define FILENAME "empfile.txt"

using namespace std;
#include<vector>



class workermanager
{
public:
	workermanager();

	void show_Menu();

	void exitsystem();

	~workermanager();
	
	//记录职工人数
	int m_EmpNum;

	//职工数组指针
	worker** m_Emparray;

	//添加职工
	void add_emp();

	//保存
	void save();

	//判断文件是否为空 标志
	bool m_fileisempty;

	//统计文件中的人数
	int get_empnum();

	//初始化员工
	void init_emp();

	//展示职工信息
	void show_emp();

	//删除职工
	void del_emp();

	//判断职工是否存在  如果存在返回职工所在数组中的位置，不存在返回-1
	int isexist(int id);

	//修改职工
	void mod_emp();

	//判断职工编号是否已经存在，如果不存在返回编号本身，存在返回-1
	int idisexist(int id);

	//查找职工
	void Find_Emp();

	//按照编号进行排序
	void sort_emp();

	//清空文件
	void Clean_file();

};