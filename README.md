# LFP

[![PyPI Version][pypi-v-image]][pypi-v-link]
[![Build Status][travis-image]][travis-link]
[![Windows Build Status][appveyor-image]][appveyor-link]
[![Coverage Status][codecov-image]][codecov-link]
[![Landscale Code Health][landscape-image]][landscape-link]

- View the [MkDocs documentation][mkdocs].
- Project [release notes][release-notes].
- Visit the [MkDocs wiki](https://github.com/mkdocs/mkdocs/wiki) for community
  resources, including third party themes and a list of MkDocs users.
- IRC channel: `#mkdocs` on freenode.
- Discussions and support: <https://groups.google.com/forum/#!forum/mkdocs>

## 项目简介

在工作、优秀开源代码的阅读过程中，时常会遇到一些比较亮眼的编码方式，出于好奇、自我提升，将这些good taste加以消化，从架构层面扩展自己的知识视野。`lfp`**lee's firmware platform**。

## FEATURES

### Mkdocs文档管理工具

项目文档主要以mkdown文档书写，使用[MKdocs](https://mkdocs.readthedocs.io/en/stable/)进行文档服务器的部署，达到管理工程项目文档的目的。

###
### lfp_util

基础架构部分，支撑项目的通用业务，例如日志输出等、timer、串口交互等；

#### lfp_util_dbg

管理项目各模块的日志输出, 方便调试；

#### lfp util timer

管理项目的基础时间相关业务，不随着OS/平台的变化而变化，如果依赖OS/平台，需要封装成`lfp_adapter`层;

### lfp_util_cmd

> 串口命令管理, 实现用户交互。用户busybox实现, 通过串口交互实现和主程序的交互，完成状态查询、触发控制等;

### lfp_arch_adapter

> 平台适配层，用以兼容/适配不同的操作系统（或者cpu平台，预留，目前暂时适配不同操作系统）, 用户层无需感知系统的变化；

### lfp_arch

> 架构层实现，主要实现不同OS的系统层封装，上层用用业务不感知；

### lfp_documents

> 以mkdown编写的项目各模块的详细设计架构，以项目架构进行文档分层，设计和文档一致性；

### lfp_exec

> 可执行程序输出目录，各模块编译之后，最后在lfp_exec进行链接、组装，形成最终的可执行文件；

### lfp_main

> 项目主入口，各核心模块的注册启动；

### lfp_include

> 项目外部头文件，内部头文件不输出到次目录，直接存放在对应模块，以`__`作为文件前缀；

### lfp_modules

> 各应用模块业务代码，所有的应用都基于平台层实现，不能随意直接调用`lfp_arch`层代码；

### menuconfig

> 用以配置、裁剪控制模块；

### link_order

> 库链接顺序，越是底层的库，链接时越是靠后；

### rules.make

> 编译规则

### 编码规则

编码规则主要对项目中的编码习惯进行一个约定，后期随着工程的迭代，可能会引入新的编码规则，目的是一致的，就是促进项目的健壮性，朝着可维护性、可扩展性方向发展。你可以在[lfp编码规则][]处查看编码规则。

#### 统计代码行数

```shell
find . "(" -name "*.c"  -or -name "*.cpp" -or -name "*.h" ")" -print | xargs wc -l
```

[appveyor-image]: https://img.shields.io/appveyor/ci/d0ugal/mkdocs/master.svg
[appveyor-link]: https://ci.appveyor.com/project/d0ugal/mkdocs
[codecov-image]: https://codecov.io/github/mkdocs/mkdocs/coverage.svg?branch=master
[codecov-link]: https://codecov.io/github/mkdocs/mkdocs?branch=master
[landscape-image]: https://landscape.io/github/mkdocs/mkdocs/master/landscape.svg?style=flat
[landscape-link]: https://landscape.io/github/mkdocs/mkdocs/master
[pypi-v-image]: https://img.shields.io/pypi/v/mkdocs.svg
[pypi-v-link]: https://pypi.org/project/mkdocs/
[travis-image]: https://img.shields.io/travis/mkdocs/mkdocs/master.svg
[travis-link]: https://travis-ci.org/mkdocs/mkdocs

[mkdocs]: https://www.mkdocs.org
[release-notes]: https://www.mkdocs.org/about/release-notes/

[PyPA Code of Conduct]: https://www.pypa.io/en/latest/code-of-conduct/


[编码规则]: /index/
