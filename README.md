# lfp tech advance

[![PyPI Version][pypi-v-image]][pypi-v-link]
[![Build Status][travis-image]][travis-link]
[![Windows Build Status][appveyor-image]][appveyor-link]
[![Coverage Status][codecov-image]][codecov-link]

- [lfp tech advance][lfp tech advance]访问项目，获取更多的工具、源码以及文档信息。

## 概述

自我提升，保持技术热情。lfp取名 lee's firmware platform。

## 特性

### 支持Mkdocs文档管理工具

项目文档主要以mkdown文档书写，使用[MKdocs](https://mkdocs.readthedocs.io/en/stable/)进行文档服务器的部署，达到管理工程项目文档的目的，点击[项目文档][lfp document]查看完整、详细的项目文档。

### 总体架构

![总体架构](lfp_documents/docs/roadmapping/res/%E6%95%B4%E4%BD%93%E6%9E%B6%E6%9E%84.png)

### 基础组件

 * usrbusybox、DB、open sources、libs package；

 * 多OS适配。对不同OS进行适配封装，应用层业务使用`lfp_arch_adapter`组件可以无需关心具体的系统差异；


[pypi-v-image]: https://img.shields.io/pypi/v/mkdocs.svg
[pypi-v-link]: https://pypi.org/project/mkdocs/
[lfp tech advance]: https://github.com/Lee91/lfp_tech_advance
[lfp document]: https://github.com/Lee91/lfp_tech_advance/tree/master/lfp_documents/CN/
[appveyor-image]: https://img.shields.io/appveyor/ci/d0ugal/mkdocs/master.svg
[appveyor-link]: https://ci.appveyor.com/project/d0ugal/mkdocs
[codecov-image]: https://codecov.io/github/mkdocs/mkdocs/coverage.svg?branch=master
[codecov-link]: https://codecov.io/github/mkdocs/mkdocs?branch=master
[landscape-image]: https://landscape.io/github/mkdocs/mkdocs/master/landscape.svg
[landscape-link]: https://landscape.io/github/mkdocs/mkdocs/master
[travis-image]: https://img.shields.io/travis/mkdocs/mkdocs/master.svg
[travis-link]: https://travis-ci.org/mkdocs/mkdocs