# APUE学习

## 本项目说明

本项目是个人学习apue所记录的所有相关资料和代码,仅限学习使用,如有笔误,请指出


## 目录结构说明

- apue
	- include 所需的头文件 包含apue.h及其他头文件
	- lib apue.h所需的链接文件及其他文件
	- 各章节的unit 包含了对各章节代码的理解 以代码形式展现
		- md 包含了对各章节的看法 以文字形式展现
		- img 对各章节理解的图示
	- Make.defines.*
	- systype.sh


## 其他相关

### 开发工具

linux平台使用vim

windows平台使用sublime



### 所使用系统

使用windows 10 自带的 wsl 

linux版本为Ubuntu 安装了gcc与gdb 


### apue代码编译

没有直接编译所有的apue代码,其中编译了
- lib apue.h所依赖的库文件
- include 包含了apue.h 及其他相关头文件

首先在lib目录中执行`make`生成所有的链接文件,然后再单独的章节目录中运行make即可


### apue所附带的代码下载地址

`http://www.apuebook.com/`
