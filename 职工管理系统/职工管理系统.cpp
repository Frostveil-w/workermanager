#include<iostream>
#include"workermanager.h"
using namespace std;

#include"worker.h"
#include"manager.h"
#include"employee.h"
#include"boss.h"




int main()
{


	//实例化管理者对象
	workermanager wm;
	int choice;
	int sympol = 1;
	while (sympol !=0)
	{
		wm.show_Menu();
		cout << "请输入您的选择：" << endl;
		cin >> choice;
		switch (choice)
		{
		case 0: //退出系统
			wm.exitsystem();
			sympol = 0;
			break;
		case 1:    //增加职工
			wm.add_emp();
			break;
		case 2:    //显示职工
			wm.show_emp();
			break;
		case 3:    //删除职工
			wm.del_emp();
			break;
		case 4:    //修改职工
			wm.mod_emp();
			break;
		case 5:    //查找职工
			wm.Find_Emp();
			break;
		case 6:    //排序职工
			wm.sort_emp();
			break;
		case 7:    //清空文档
			wm.Clean_file();
			break;
		default:
			system("cls");
			break;




		}



	}

	
	
	

	

	



	system("pause");

	return 0;


}



