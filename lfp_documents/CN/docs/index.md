# lfp documents

在工作、优秀开源代码的阅读过程中，时常会遇到一些比较亮眼的编码方式，出于好奇、自我提升，将这些good taste加以消化，从架构层面扩展自己的知识视野。`lfp`取名**lee's firmware platform**，知识、技能*roads*中所描述、涉及的知识内容，不一定按照由浅入深的顺序去排列，主要还是**以自我兴趣、提升为前提和中心**，并应用到项目中，学以致用。

## mkdocs介绍

[MKdocs](www.mkdocs.org)是一个优秀的静态文档生成器。将文档源文件使用`Markdown`编写，文档的目录层级在`mkdocs.yml`文件中进行配置，运行`mkdocs serve`后即可在浏览器中看到编写的文档内容，排版格式简洁、美观。

### mkdocs安装方法

- 在设备上安装python及其包管理工具pip（目前windows下python安装包会默认安装pip工具）；
- 使用`pip install mkdocs`命令安装`mkdocs`（windows下使用`pip -m install mkdocs`）；
- 可以通过安装[mkdocs-material][mkdocs-material安装]，来集成安装`mkdocs`；

更多安装指导详见[mkdocs安装](https://www.mkdocs.org/#installing-mkdocs)；

## mkdocs-material介绍

`mkdocs-material`针对`mkdocs`提供的文档服务功能，对文档/特有功能做了渲染优化，偏向于google风格。丰富的主题/页面配置风格，能够为我们提供更好的用户体验。

### mkdocs-material安装方法

- 和`mkdocs`一样，安装`mkdocs-material`需要`python`和`pip`前置安装；
- 使用`pip install mkdocs-material`安装`mkdocs-material`，此时会同步安装`mkdocs`相关资源;

## 核心模块介绍

### lfp util

基础公共架构部分，支撑项目的通用业务，一是构成系统人机交互的重要桥梁，例如终端命令交互；二是为*upper层*提供基础服务，例如始终、日志等；

#### lfp_util_dbg

**[日志系统][lfp util]**，根据*模块->子模块...*的基础树形结构进行日志模块的分块管理，实现系统日志信息的精准定位和精确捕捉；

#### lfp util timer

**[基础时间管理][lfp util timer]**，服务不随着OS/平台的变化而变化，如果依赖OS/平台，转封装`lfp_adapter`层；

#### lfp_util_cmd

**[终端命令][lfp util cmd]**, 实现用户交互。用户busybox实现, 通过串口交互实现和主程序的交互，完成状态查询、触发控制等；

### lfp_arch_adapter

**[架构适配层][lfp arch adapter]**，用以兼容/适配不同的操作系统（或者cpu平台，预留，目前暂时适配不同操作系统）, 用户层无需感知系统的变化；

### lfp_arch

**[架构实现层][lfp arch]**，实现不同OS的系统层封装，上层应用业务不感知系统的差异性；

### lfp_documents

以`mkdown`编写的项目各模块的详细设计架构，以项目架构进行文档分层，设计和文档一致性，点击[项目文档][lfp documents]查看详细的项目文档架构；

### lfp_exec

可执行程序输出目录，各模块编译之后，最后在lfp_exec进行链接、组装，形成最终的可执行文件；

### lfp_main

项目主入口，各核心模块的注册启动；

### lfp_include

按照`src .c`层级架构，项目外部头文件，内部头文件不输出到此目录，直接存放在对应模块，以`__`作为文件前缀；

### lfp_modules

各应用模块业务代码，所有的应用都基于平台层实现，不能随意直接调用`lfp_arch`层代码，模块业务代码统一在模块中进行注册之后，再注册到`main`；

### menuconfig

用以配置、裁剪控制模块；

### link_order

库链接顺序，越是底层的库，链接时越是靠后；

### rules.make

编译规则

## 编码规则

编码规则主要对项目中的编码习惯进行一个约定，后期随着工程的迭代，可能会引入新的编码规则，目的是一致的，就是促进项目的健壮性，朝着可维护性、可扩展性方向发展。你可以在[lfp编码规则][programming rules]处查看编码规则。

[mkdocs-material安装]: #mkdocs-material安装方法
[lfp util cmd]: /util/util_cmd/
[lfp util timer]: /util/
[lfp util]: /util/util/
[lfp arch adapter]: /arch_adapter/arch_adaprer/
[lfp arch]: /arch/arch/
[lfp documents]: /./
[programming rules]: /programming_rules/proogramming_rules/