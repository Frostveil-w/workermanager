#include "workermanager.h"

//构造函数
workermanager::workermanager()
{
	//1、文件不存在

	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	if (!ifs.is_open())
	{
		//初始化属性
		this->m_EmpNum = 0;
		this->m_Emparray = NULL;
		//初始化文件是否为空
		this->m_fileisempty = true;

		ifs.close();
		return;
	}

	//2、文件存在 数据为空
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//文件为空
		//初始化属性
		this->m_EmpNum = 0;
		this->m_Emparray = NULL;
		//初始化文件是否为空
		this->m_fileisempty = true;

		ifs.close();
		return;
	}

	//3、文件存在，且有数据
	int num = this->get_empnum();
	this->m_EmpNum = num; 
	this->m_Emparray = new worker * [num];
	this->init_emp();
	this->m_fileisempty = false;



}
//析构函数
workermanager ::~workermanager()
{
	if (this->m_EmpNum != 0)
	{
		for (int i = 0;i < this->m_EmpNum;++i)
		{
			delete this->m_Emparray[i];
		}
	}
	if (this->m_Emparray != NULL)
	{
		delete[] this->m_Emparray;
		this->m_Emparray = NULL;
	}

}
//菜单
void workermanager::show_Menu()
{
	cout << "欢迎使用职工管理系统" << endl;
	cout << "0.退出管理系统" << endl;
	cout << "1.添加职工信息" << endl;
	cout << "2.显示职工信息" << endl;
	cout << "3.删除离职职工" << endl;
	cout << "4.修改职工信息" << endl;
	cout << "5.查找职工信息" << endl;
	cout << "6.按照编号排序" << endl;
	cout << "7.清空所有文档" << endl;
	cout << endl;

}
//添加职工
void workermanager::add_emp()
{
	cout << "请输入要添加的人数：" << endl;
	int addnum = 0;
	cin >> addnum;
	vector<int> v;

	if (addnum > 0)
	{
		//添加
		//计算添加新空间大小
		int newsize = this->m_EmpNum + addnum; //新空间人数 = 原来记录人数 + 新增人数

		//开辟新空间
		worker ** newspace = new worker*[newsize];

		//将原来空间下数据，拷贝到新空间下
		if (this->m_Emparray != NULL)
		{
			for (int i = 0;i < this->m_EmpNum;i++)
			{
				newspace[i] = this->m_Emparray[i];
			}
		}
		
		//批量添加新数据
		for (int i = 0;i < addnum;i++)
		{
			worker* worker = NULL;
			int id;    //职工编号
			string name;   //姓名
			int dselect;   //部门选择
			cout << "请输入你要添加的第" << i + 1 << "个人的信息" << endl;
			cout << "职工编号：" << endl;
			cin >> id;
			
			int temp = 1;
			
			while (temp != 0)
			{
				while (this->idisexist(id) == -1)
				{
					cout << "编号已存在！请输入新的编号！" << endl;
					cin >> id;
				}
				if (this->idisexist(id) != -1)
				{
					int temp2 = 0;
					for (vector<int>::iterator it = v.begin();it != v.end();it++)
					{
						if ((*it) == id)
						{
							cout << "编号已存在！请输入新的编号！" << endl;
							cin >> id;
							temp2++;
							break;
						}
					}
					if (temp2 == 0)
					{
						temp = 0;
					}
				}
			}
			
			v.push_back(id);
			
			cout << "姓名：" << endl;
			cin >> name;
			cout << "请选择该职工岗位：" << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、总裁" << endl;
			cin >> dselect;
			switch (dselect)
			{
			case 1:
				worker = new employee(id, name, 1);
				break;
			case 2:
				worker = new manager(id, name, 2);
				break;
			case 3:
				worker = new boss(id, name, 3);
				break;
			default:
				break;
			}
			//将创建职工，保存到数组中
			newspace[this->m_EmpNum + i] = worker;
			


		}

		//释放原有空间

		delete[] this->m_Emparray;

		//更改新空间指向
		this->m_Emparray = newspace;

		//更新新的职工人数
		this->m_EmpNum = newsize;

		//更新职工不为空
		this->m_fileisempty = false;

		//提示添加成功
		cout << "成功添加" << addnum << "名员工" << endl;

		this->save();

	}
	else
	{
		cout << "输入有误！"<<endl;
	}

	//按任意键后 清屏 并返回主菜单
	system("pause");
	system("cls");


}
//退出
void workermanager::exitsystem()
{
	cout << "欢迎下次使用" << endl;
	return;

}


//保存文件
void workermanager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);
	 
	//将每个人数据写入到文件中
	for (int i = 0;i < this->m_EmpNum;i++)
	{
		ofs << this->m_Emparray[i]->m_id << " "
			<< this->m_Emparray[i]->m_name << " "
			<< this->m_Emparray[i]->m_deptid << endl;
	}

	//关闭文件
	ofs.close();
}


//获取文件中的人数
int workermanager::get_empnum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int did;
	int num = 0;

	while (ifs >> id && ifs >> name && ifs >> did)
	{
		//统计人数变量
		num++;
	}

	return num;
}
void workermanager::init_emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int did;

	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> did)
	{
		worker* worker = NULL;
		if (did == 1)
		{
			worker = new employee(id, name, 1);
		}
		else if (did == 2)
		{
			worker = new manager(id, name, 2);
		}
		else
		{
			worker = new boss(id, name, 3);
		}
		this->m_Emparray[index] = worker;
		index++;
	}
	ifs.close();
}

//显示职工信息
void workermanager::show_emp()
{
	//判断文件是否为空
	if (this->m_fileisempty)
	{
		cout << "文件为空或者不存在！" << endl;
	}
	else
	{
		for (int i = 0;i < this->m_EmpNum;i++)
		{
			//利用多态调用程序接口
			this->m_Emparray[i]->showinfo();
		}
	}
	//按任意键后清屏
	system("pause");
	system("cls");
}

//删除职工
void workermanager::del_emp()
{
	if (this->m_fileisempty)
	{
		cout << "文件不存在或记录为空" << endl;
	}
	else
	{
		cout << "请输入您要删除的职工信息的编号" << endl;
		int id;
		cin >> id;
		int index = this->isexist(id);
		if (index == -1)
		{
			cout << "成员不存在！";
		}
		else
		{
			this->m_Emparray[index]->showinfo();
			cout << "是否是您要删除的对象？(y/n)" << endl;
			char ch;
			cin >> ch;
			if (ch == 'n' || ch == 'N')
			{
				system("pause");
				system("cls");
				return;
			}
			else if (ch == 'y' || ch == 'Y')
			{
				delete this->m_Emparray[index];
				for (int i = index;i < this->m_EmpNum - 1;i++)
				{
					this->m_Emparray[i] = this->m_Emparray[i + 1];
				}
				this->m_EmpNum--;
				//数据同步更新到文件中
				this->save();
				cout << "删除成功！" << endl;
			}
		}
		system("pause");
		system("cls");
	}
	

}

//判断职工是否存在  如果存在返回职工所在数组中的位置，不存在返回-1
int workermanager::isexist(int id)
{
	int index = -1;
	for (int i = 0;i < this->m_EmpNum;i++)
	{
		if (this->m_Emparray[i]->m_id == id)
		{
			//找到职工
			index = i;

			break;
		}
	}

	return index;

}

//修改职工
void workermanager::mod_emp()
{
	if (this->m_fileisempty)
	{
		cout << "文件不存在或者为空" << endl;
	}
	else
	{
		int id;
		cout << "请输入您要修改的职工编号" << endl;
		cin >> id;
		int index = this->isexist(id);
		if (index != -1)
		{
			this->m_Emparray[index]->showinfo();
			cout << "请问是否是您要修改的对象？（y/n）" << endl;
			char ch;
			cin >> ch;
			if (ch == 'n' || ch == 'N')
			{
				system("pause");
				system("cls");
				return;
			}
			else if (ch == 'y' || ch == 'Y')
			{
				int n_id;
				string name;
				worker* worker = NULL;
				int select;
				cout << "请输入该职工新的编号" << endl;
				cin >> n_id;
				while (this->idisexist(n_id) == -1)
				{
					cout << "编号已存在！请输入新的编号！" << endl;
					cin >> n_id;
				}
				cout << "请输入该职工的新名字" << endl;
				cin >> name;
				cout << "请输入该职工的新岗位" << endl;
				cout << "1、普通职工" << endl;
				cout << "2、经理" << endl;
				cout << "3、总裁" << endl;
				cin >> select;
				switch (select)
				{
				case 1:
					worker = new employee(n_id, name, 1);
					break;
				case 2:
					worker = new manager(n_id, name, 2);
					break;
				case 3:
					worker = new boss(n_id, name, 3);
					break;
				default:
					break;
				}
				delete this->m_Emparray[index];
				this->m_Emparray[index] = worker;
				
			}
			this->save();
			cout << "修改成功！" << endl;
			
		}
		else
		{
			cout << "职工不存在！" << endl;
		}

	}
	system("pause");
	system("cls");
	
}
//判断职工编号是否已经存在，如果不存在返回编号本身，存在返回-1
int workermanager::idisexist(int id)
{
	int index = id;
	for (int i = 0;i < this->m_EmpNum;i++)
	{
		if (this->m_Emparray[i]->m_id == id)
		{
			index = -1;
		}
	}
	return index;

}

//查找职工
void workermanager::Find_Emp()
{
	if (this->m_fileisempty)
	{
		cout << "文件为空或者不存在！" << endl;
	}
	else
	{
		int select = 0;
		cout << "请输入您要选择的查找方式" << endl;
		cout << "1、按照编号查找" << endl;
		cout << "2、按照姓名查找" << endl;
		cin >> select;
		switch (select)
		{
		case 1:
		{
			int id;
			cout << "请输入要查找的员工编号：" << endl;
			cin >> id;
			int ret = this->isexist(id);
			if (ret!= -1)
			{
				this->m_Emparray[ret]->showinfo();
			}
			else
			{
				cout << "查无此人！" << endl;
			}
			break;
		}
		case 2:
		{
			string name;
			bool temp = false;
			cout << "请输入您要查找的员工姓名：" << endl;
			cin >> name;
			for (int i = 0;i < this->m_EmpNum;i++)
			{
				if (name == this->m_Emparray[i]->m_name)
				{
					this->m_Emparray[i]->showinfo();
					temp = true;
				}
			}
			if (temp == false)
			{
				cout << "查无此人！" << endl;
			}
			break;
		}
		default:
			cout << "输入有误！" << endl;
			break;

		}
		

	}
	system("pause");
	system("cls");
}
//按照编号进行排序
void workermanager::sort_emp()
{
	int select=0;
	cout << "请输入您希望的排序方式" << endl;
	cout << "1、按照编号进行升序排列" << endl;
	cout << "2、按照编号进行降序排列" << endl;
	cin >> select;
	if (select != 1 && select != 2)
	{
		cout << "输入有误！" << endl;
		system("pause");
		system("cls");
		return;
	}
	else
	{
		
		for (int i = 0;i < this->m_EmpNum;i++)
		{
			if (select == 1)
			{
				int min = i;
				for (int j = i;j < this->m_EmpNum;j++)
				{

					if (this->m_Emparray[min]->m_id > this->m_Emparray[j]->m_id)
					{
						min = j;
					}
				}
				worker* worker = this->m_Emparray[i];
				this->m_Emparray[i] = this->m_Emparray[min];
				this->m_Emparray[min] = worker;
			}
			if (select == 2)
			{
				int max = i;
				for (int j = i+1;j < this->m_EmpNum;j++)
				{
					if (this->m_Emparray[max]->m_id < this->m_Emparray[j]->m_id)
					{
						max = j;
					}
				}
				worker* worker = this->m_Emparray[i];
				this->m_Emparray[i] = this->m_Emparray[max];
				this->m_Emparray[max] = worker;
			}

		}
		this->save();
		cout << "重新排序成功！" << endl;
		this->show_emp();

	}

}


//清空文件
void workermanager::Clean_file()
{
	int select = 0;
	cout << "确认清空？" << endl;
	cout << "1、确认" << endl;
	cout << "2、返回" << endl;
	cin >> select;
	if (select != 1)
	{
		system("pause");
		system("cls");
		return;
	}
	else
	{
		if (this->m_Emparray != NULL)
		{
			for (int i = 0;i < this->m_EmpNum;i++)
			{
				if (this->m_Emparray[i] != NULL)
				{
					delete this->m_Emparray[i];
					this->m_Emparray[i] = NULL;
				}
			}
			delete[]this->m_Emparray;
			this->m_Emparray = NULL;
			this->m_EmpNum = 0;
		}
		ofstream ofs;
		ofs.open(FILENAME, ios::trunc);
		ofs.close();
		this->m_fileisempty = true;
		cout << "删除成功！" << endl;
		system("pause");
		system("cls");
	}

}