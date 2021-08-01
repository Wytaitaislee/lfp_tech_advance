# lfp documents

在工作、优秀开源代码的阅读过程中，时常会遇到一些比较亮眼的编码方式，编码技能，出于自我进步和提升，将这些good taste加以消化，从架构层面扩展自己的知识视野。`lfp`取名 __lee's firmware platform__，知识、技能 _roadmapping_ 中所描述、涉及的知识内容，不一定按照由浅入深的顺序去排列，主要还是 __以自我兴趣、提升为前提和中心__，并应用到项目中，学以致用。

## mkdocs介绍

[MKdocs](www.mkdocs.org)是一个优秀的静态文档生成器。将文档源文件使用`markdown`编写，文档的目录层级在`mkdocs.yml`文件中进行配置，运行`mkdocs serve`后即可在浏览器中看到编写的文档内容，排版格式简洁、美观。

### mkdocs安装方法

- 在设备上安装python及其包管理工具pip（目前windows下python安装包会默认安装pip工具）；
- 使用`pip install mkdocs`命令安装`mkdocs`（windows下使用`pip -m install mkdocs`）；
- 可以通过安装[mkdocs-material][mkdocs-material安装]，来集成安装`mkdocs`；

更多安装指导详见[mkdocs安装](https://www.mkdocs.org/#installing-mkdocs)；

## mkdocs-material介绍

`mkdocs-material`针对`mkdocs`提供的文档服务功能，对文档/特有功能做了渲染优化，偏向于google风格。丰富的主题/页面配置风格，能够为我们提供更好的用户体验。

=== "mkdocs-material在线安装方法"

	* 和`mkdocs`一样，安装`mkdocs-material`需要`python`和`pip`前置安装；
	* 使用`pip install mkdocs-material`安装`mkdocs-material`，此时会同步安装`mkdocs`相关资源;

=== "mkdocs-material离线安装方法"
	

	* cd mkdocs-material
	* pip install -r requirements.txt
	* pip install mkdocs-minify-plugin
	* pip install mkdocs-redirects
	* npm install

## 核心组件介绍

> __lfp__ 组件的主要目录构成，本章节根据      __lfp_system_arch.drawio__ 中的层级顺序，由低向高的层级进行介绍；

### lfp util

基础公共架构部分，支撑项目的通用业务，为 _upper层_提供基础服务，例如日志等；

**[日志系统][lfp util]**，根据 _模块->子模块..._的基础树形结构进行日志模块的分块管理，实现系统日志信息的精准定位和精确捕捉；

### lfp_arch

**[架构实现层][lfp arch]**，实现不同OS的系统层封装，上层应用业务不感知系统的差异性；

### lfp_arch_adapter

**[架构适配层][lfp arch adapter]**，用以兼容/适配不同的操作系统（或者cpu平台，预留，目前暂时适配不同操作系统）, 用户层无需感知系统的变化；

### lfp_documents

以`markdown`编写的项目各模块的详细设计架构，以项目架构进行文档分层，设计和文档一致性。将文档使用`mkdocs`和`mkdocs-material`渲染后，发布到`Github Page`，点击[项目文档][lfp documents]查看详细的项目文档信息；

### lfp_include

按照`src .c`层级架构，存放项目相关的头文件，不要为了图简单而将一系列都文件都包含到某一个头文件，再暴露出去供引用。头文件应包含哪些头文件仅取决于自身，而非包含该头文件的源文件：

> 例如，编译源文件时需要用到头文件B，且源文件已包含头文件A，而索性将头文件B包含在头文件A中，这是错误的做法。
>
> 头文件A是否应该包含头文件B，取决于头文件中定义的数据结构/函数声明是否需要头文件B中的数据结构；

### lfp_app_base

**[app的基础服务][lfp app base]**，主要为上层应用app提供系统级的通用基础组件，为后期扩展打基础。例如算法封装、用户串口命令、常用的业务模块封装库（链表、线程池等）、开源代码、数据库等；

### lfp_app

**[应用业务层][lfp app]**，根据不同的业务场景，构建不同的app模块；

### lfp_exec

可执行程序输出目录，各模块编译之后，最后在`lfp_exec`进行链接、组装，形成最终的可执行文件；

### lfp_main

项目主入口，实现各核心模块的注册启动；

### menuconfig

用以配置、裁剪控制模块；

### lfp_linking

库链接顺序管理，每一层及的模块独立控制，越是底层的库，链接时越是靠后，确保链接顺序正常；

### lfp_rules.make

编译管理，控制各组件的统一编译风格；

## 编码规则

编码规则主要对项目中的编码习惯进行一个约定，后期随着工程的迭代，可能会引入新的编码规则，目的是一致的，就是促进项目的健壮性，朝着可维护性、可扩展性方向发展。你可以在[lfp编码规则][programming rules]处查看编码规则。

[mkdocs-material安装]: #mkdocs-material安装方法
[lfp util]: /util/util_logs/
[lfp arch]:   /arch/arch/
[lfp arch adapter]: /arch_adapter/arch_adapter/
[programming rules]: /programming_rules/proogramming_rules/
[lfp documents]: https://lee91.github.io/lfp_tech_advance/
[lfp app base]: /app_base/app_base/
[lfp app]: /app/app/



