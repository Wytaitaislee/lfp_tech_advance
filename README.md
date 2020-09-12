# LFP

[![PyPI Version][pypi-v-image]][pypi-v-link]
[![Build Status][travis-image]][travis-link]
[![Windows Build Status][appveyor-image]][appveyor-link]
[![Coverage Status][codecov-image]][codecov-link]
[![Landscale Code Health][landscape-image]][landscape-link]

- 浏览地址[LFP Project][LFP Project]访问项目，获取更多的工具、源码以及文档信息。

## 概述

在工作、优秀开源代码的阅读过程中，时常会遇到一些比较亮眼的编码方式，出于对技术的好奇、自我提升，将这些good taste加以理解消化，从架构层面扩展自己的知识视野，提升自己的技术水平。`lfp`取名自**lee's firmware platform**。

## 特性

### 支持Mkdocs文档管理工具

项目文档主要以mkdown文档书写，使用[MKdocs](https://mkdocs.readthedocs.io/en/stable/)进行文档服务器的部署，达到管理工程项目文档的目的，点击[项目文档][LFP document]查看完整、详细的项目文档。

### 基础组件
 
 * 多级模块日志系统，通过模块细分日志场景，精准捕捉运行形态；
 
 * 多OS适配。对不同OS进行适配封装，应用层业务使用`lfp_arch_adapter`组件可以无需关心具体的系统差异；

 * 交互命令管理, 实现用户交互。借鉴busybox实现, 通过运行终端实现和主程序的交互，完成状态查询、触发控制等操作。

### 业务模块

 * 系统层隔离，便于移植；
 * 通过配置不同的应用模块，控制程序支持的不同业务集，方便快速裁剪。

## 分层架构

* 多级模块分布式架构管理，模块顶层向`main`注册；

* 头文件、`.c`源码以及文档分层暴露，避免在`.c`文件中`include`过多引用，统一存放管理，仅模块内部使用的头文件禁止暴露，封装到模块内部。

[pypi-v-image]: https://img.shields.io/pypi/v/mkdocs.svg
[pypi-v-link]: https://pypi.org/project/mkdocs/
[LFP Project]: https://github.com/Lee91/lfp_tech_advance
[LFP document]: https://github.com/Lee91/lfp_tech_advance/tree/master/lfp_documents/CN/
[release-notes]: todo

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