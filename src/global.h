#pragma once
#define UPDATE_OPEN_DATABASE 0x01          //打开数据库消息
#define UPDATE_CREATE_TABLE 0x02           //创建表消息
#define UPDATE_EDIT_TABLE 0x03             //修改表消息
#define UPDATE_ADD_FIELD 0x04              //添加字段消息
#define UPDATE_OPEN_TABLE 0x05             //查询记录消息
#define UPDATE_INSERT_RECORD 0x06          //插入记录消息
#define MENU_DATABASE 1                    //数据库菜单编号
#define MENU_TABLE 2                       //表菜单编号
#define MENU_FIELD 3                       //字段菜单编号
#define MENU_RECORD 4                      //记录菜单编号
#define MENU_OTHER -1                      //其他菜单编号

#include <vector>
using namespace std;
