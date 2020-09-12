# 统计工具

## 工程所含代码行数统计

```bash
find . "(" -name "*.c"  -or -name "*.cpp" -or -name "*.h" ")" -print | xargs wc -l
```
## 工程所含文档行数统计

```bash
find . "(" -name "*.md" ")" -print | xargs wc -l
```

