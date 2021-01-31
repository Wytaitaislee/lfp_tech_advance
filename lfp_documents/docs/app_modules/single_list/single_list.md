<center><font face="黑体" size=6>**本部分主要介绍单链表相关知识**</font></center>
<br/>

## 单链表和数组的比较

### 单链表
 
    1. 在内存中，节点的地址空间不连续；
   
    2. 增、删数据相对容易，只需要知道要增加、删除的位置，可以不操作其他额外的元素即可实现；
   
    3. 因为不可以通过随机读取链表，故查找效率相对较低；
   
    4. 不用指定大小，扩展方便；

### 数组
   
    1. 在内存中，元素的地址空间连续；
    
    2. 需要在程序开始运行时预分配好空间，可能会存在内存空间的浪费；
    
    3. 插入和删除数据效率低，增删数据时，被操作数据后面的数据都需要移动；

    4. 随机读取效率高，因为数组是连续的内存空间，所以可以直接使用数组下表访问对应的数据；

    5. 不利于扩展，空间不够时，需要重新定义数组；

### 各自的优缺点

    1. 数组优点：①、数组内的数据可以随机访问； ②、数据查找效率较高（内存连续）；

    2. 链表优点：①、方便数据的删除、插入； ②、长度可变，扩展性好； ③、内存利用率高（可以不连续）；

<br/>

## 链表在项目中的使用

### 链表数据结构

```c
/*single list structure definition */
typedef struct lfp_single_list_t
{
	LFP_INT32 data;
	struct lfp_single_list_t *pNext;
}LFP_SINGLE_LIST_T;
```

### 链表实现过程
> 链表主要涉及创建、添加、查找、插入、删除、销毁等几个点，下面分述这些过程（查找过程不显式描述）

#### 创建（带头节点）

##### 伪代码
- 因为需要修改头节点(指针)的指向，所以需要传入指针的地址，也即二维指针；

```c
    create(list **ppList)
    {
        *ppList = (list *)malloc(sizeof(list));
        *ppList->data = 0;
        *ppList->pNext = NULL;
    }
```

#### 添加（尾部添加）

##### 伪代码
- 使用pWalk->pNext而不是pWalk去遍历链表，省去记录前驱节点，避免尾部添加时，需要二次遍历；
```c
    add(list *pList, data_t data)
    {
        ...
        assert(pList);
        pWalk = pList;
        while(pWalk->pNext)
        {
            pWalk = pWalk->pNext;
        }
        pNewNode = (list *)malloc(sizeof(list));
        ...
        pWalk->pNext = pNewNode;
    }
```

#### 插入（在某指定节点之前插入）

##### 伪代码
- 插入有多种方式，例如在指定的位置插入，指定某节点插入等，这里介绍以某指定的节点插入
```c
    insert(list *pList, list *pNode)
    {
        ...
        assert(pList);
        pWalk = pList;
        while(pWalk->pNext)
        {
            if(pWalk->pNext == pNode)
            {
                break;
            }
            pWalk = pWalk->pNext;
        }
        if(!pWalk->pNext)
        {
            return err;
        }
        pNewNode = (list *)malloc(sizeof(list));
        pNewNode->pNext = pWalk->pNext;
        pWalk->pNext = pNewNode;     
    }
```

#### 删除（删除某个指定的节点）
##### 伪代码
- 将指定的节点从链表中删除，释放先前分配的存储空间
```c
    delete(list *pList, list *pDelNode)
    {
        ...
        assert(pList);
        pWalk = pList;
        while(pWalk->pNext)
        {
            if(pWalk->pNext == pDelNode)
            {
                break;
            }
            pWalk = pWalk->pNext;
        }
        if(!pWalk->pNext)
        {
            return err;
        }
        pWalk->pNext = pWalk->pNext->pNext; /* 无论pwalk->pNext->pNext是否为空，都可以表示 */
    }
```

#### 销毁（和create结对，销毁链表时）
##### 伪代码
- 传入头节点的地址
```c
    destroy(list *ppList)
    {
        ...
        assert(pplist && *ppList);
        pWalk = *ppList;
        while(pWalk)
        {
            pTmp = pWalk;
            pWalk = pWalk->pNext;
            free(pTmp);
        }
        *pList = (list *)NULL;
    }
```
- 不传入头节点的地址
```c
    destroy(list *pList)
    {
        ...
        assert(pList);
        pWalk = pList;
        while(pWalk)
        {
            pTmp = pWalk;
            pWalk = pWalk->pNext;
            free(pTmp);
        }
    }
    此时如果有一个链表pHead，以此方式销毁链表时，应：
    destroy(pList);
    pHead = NULL;/* 将头节点指向空地址，避免使用pHead仍然可以访问已经释放的链表 */
```