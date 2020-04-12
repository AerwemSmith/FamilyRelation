TriTree *Create(DataType familyname[MAXNUM])/* 建立家族关系并存入文件*/
{
    int i=0;                  /* i控制family数组下标*/
    DataType ch,str[MAXNUM];  /* ch存储输入的y或n，str存储输入的字符串*/
    TriTree *t;
    FILE *fp;
    strcpy(fname,familyname);  /* 以家族名为文本文件名存储*/
    strcat(fname,".txt");
    fp=fopen(fname,"r");      /* 以读取方式打开文件*/
    if(fp)                    /* 文件已存在*/
    {
        fclose(fp);
        printf("%s 的家族关系已存在！重新建立请按“Y”,直接打开请按“N”\n",familyname);
        ch=getchar();
        getchar();            /* 接收回车*/
        if(ch=='N'||ch=='n')
        {
            t=Open(familyname);/* 直接打开*/
            return t;
        }
    }
    if(!fp||ch=='Y'||ch=='y')    /* 重新建立，执行以下操作*/
    {
        fp=fopen(fname,"w");      /* 以写入方式打开文件，不存在则新建*/
        printf("请按层次输入结点，每个结点信息占一行\n");
        printf("兄弟输入结束以“@”为标志，结束标志为“#”\n请输入家族的祖先:");
        gets(str);
        fputs(str,fp);
        fputc('\n',fp);
        strcpy(family[i],str);  /* 将成员信息存储到字符数组中*/
        i++;                      /* family数组下标后移*/
        while(str[0]!='#')
        {
            printf("请输入家族成员:");      /* 以点提示符提示继续输入*/
            gets(str);
            fputs(str,fp);    /* 写到文件中，每个信息占一行*/
            fputc('\n',fp);
            strcpy(family[i],str);/* 将成员信息存储到字符数组中*/
            i++;                  /* family数组下标后移*/
        }
        fclose(fp);              /* 关闭文件*/
        t=TriTreeCreate();  /* 根据family数组信息创建三叉树*/
        printf("家族关系已成功建立！\n");
        return t;                /* 返回树*/
    }
}
void PreOrder(TriTree *T)
{
    if(T&&T->data[0]!='\0')
    {
        printf("%s ",T->data);
        PreOrder(T->lchild);
        PreOrder(T->rchild);
    }
}
TriTree *TriTreeCreate()
{
    TriTree *t,*x=NULL,*tree,*root=NULL;
    LinkQueue *q=LQueueCreateEmpty();/* 建立一个空的队列，存储指向树的指针*/
    int i=0,flag=0,start=0;
    DataType str[MAXNUM];      /* 存放family数组中信息*/
    strcpy(str,family[i]);          /* 复制*/
    i++;                            /* family数组下标后移*/
    while(str[0]!='#')            /* 没遇到结束标志继续循环*/
    {
        while(str[0]!='@')    /* 没遇到兄弟输入结束标志继续*/
        {
            if(root==NULL)          /* 空树*/
            {
                root=(TriTree *)malloc(sizeof(TriTree));/* 申请空间*/
                strcpy(root->data,str);
                root->parent=NULL;
                root->lchild=NULL;
                root->rchild=NULL;
                LQueueEnQueue(q,root);                    /* 将root存入队列*/
                tree=root;
            }
            else                              /* 不为空树*/
            {
                t=(TriTree *)malloc(sizeof(TriTree)); /* 申请空间*/
                strcpy(t->data,str);
                t->lchild=NULL;
                t->rchild=NULL;
                t->parent=LQueueGetFront(q);        /* 当前结点的双亲为队头元素*/
                LQueueEnQueue(q,t);                /* 入队*/
                if(!flag)      /* flag为0，当前结点没有左孩子*/
                    root->lchild=t;
                else        /* flag为1，当前结点已有左孩子*/
                    root->rchild=t;
                root=t;                /* root指向新的结点t */
            }
            flag=1;            /* 标记当前结点已有左孩子*/
            strcpy(str,family[i]);
            i++;
        }
        if(start!=0)              /* 标记不是第一次出现“@”*/
        {
            LQueueDeQueue(q,x);              /* 出队*/
            if(q->front!=NULL)
                root=LQueueGetFront(q);/* root为队头元素*/
        }
        start=1;                      /* 标记已出现过“@”*/
        flag=0;              /* “@”后面的结点一定为左孩子*/
        strcpy(str,family[i]);
        i++;
    }
    return tree;                        /* 返回树*/
}
TriTree *Open(DataType familyname[MAXNUM])
{
    int i=0,j=0;
    DataType ch;
    FILE *fp;
    TriTree *t;
    strcpy(fname,familyname);  /* 以家族名为文本文件名存储*/
    strcat(fname,".txt");
    fp=fopen(fname,"r");            /* 以读取方式打开文件*/
    if(fp==NULL)                    /* 文件不存在*/
    {
        printf("%s 的家族关系不存在！\n",familyname);
        return NULL;
    }
    else
    {
        ch=fgetc(fp);              /* 按字符读取文件*/
        while(ch!=EOF)            /* 读到文件尾结束*/
        {
            if(ch!='\n')        /* ch不为一个结点信息的结尾*/
            {
                family[i][j]=ch;  /* 将文件信息存储到family数组中*/
                j++;
            }
            else
            {
                family[i][j]='\0';    /* 字符串结束标志*/
                i++;              /* family数组行下标后移*/
                j=0;              /* family数组列下标归零*/
            }
            ch=fgetc(fp);        /* 继续读取文件信息*/
        }
        fclose(fp);              /* 关闭文件*/
        t=TriTreeCreate();  /* 调用函数建立三叉链表*/
        printf("家族关系已成功打开！\n");
        printf("其先序遍历结果为:\n");
        PreOrder(t);
        printf("\n");
        return t;
    }
}
TriTree *Search(TriTree *t,DataType str[])
{
    TriTree *temp;
    if(t==NULL)                /* 如果树空则返回NULL */
        return NULL;
    else if(strcmp(t->data,str)==0) /* 如果找到返回该成员指针*/
        return t;
    else              /* 如果没找到遍历左右子树进行查找*/
    {
        temp=Search(t->lchild,str); /* 递归查找*/
        if(temp)                    /* 结点不空则查找*/
            return(Search(t->lchild,str));
        else
            return(Search(t->rchild,str));
    }
}
void Append(TriTree *t)
{
    int i=0,j,parpos=1,curpos,num,end=0,count=-1;
    DataType chi[MAXNUM],par[MAXNUM];/* 存储输入的孩子和其双亲结点*/
    TriTree *tpar,*temp;
    FILE *fp;
    printf("请输入要添加的成员:\n");
    gets(chi);
    printf("请输入要添加成员的父亲:");
    gets(par);
    tpar=Search(t,par);  /* 查找双亲结点是否存在*/
    if(!tpar)
        printf("%s 该成员不存在！\n");
    else                /* 存在则添加其孩子*/
    {
        temp=(TriTree *)malloc(sizeof(TriTree));/* 申请空间*/
        temp->parent=tpar;
        strcpy(temp->data,chi);
        temp->lchild=NULL;        /* 新结点左右孩子置空*/
        temp->rchild=NULL;
        if(tpar->lchild)                    /* 成员存在左孩子*/
        {
            tpar=tpar->lchild; /* 遍历当前成员左孩子的右子树*/
            while(tpar->rchild)          /* 当前结点右孩子存在*/
                tpar=tpar->rchild;        /* 继续遍历右孩子*/
            tpar->rchild=temp;                /* 将新结点添加到所有孩子之后*/
        }
        else                      /* 没有孩子则直接添加*/
            tpar->lchild=temp;
        fp=fopen(fname,"w");        /* 以写入方式打开文件*/
        if(fp)
        {
            while(strcmp(par,family[i])!=0&&family[i][0]!='#')
            {
                if(family[i][0]!='@')        /* 查找双亲在数组中位置*/
                    parpos++;                /* parpos计数*/
                i++;              /* family数组行下标后移*/
            }
            i=0;                    /* family数组行下标归0*/
            while(family[i][0]!='#')
            {
                if(family[i][0]=='@')        /* 查找“@”的个数，第一个不计*/
                    count++;              /* count累加个数*/
                if(count==parpos)            /* 说明此“@”与其前一个“@”之前为par的孩子*/
                    curpos=i;            /* curpos计当前位置*/
                i++;              /* family数组行下标后移*/
            }
            if(count<parpos)          /* “@”数小于parpos数*/
            {
                num=parpos-count;    /* 添加“@”个数为num */
                for(j=i; j<=i+num; j++) /* 从数组末尾添加“@”*/
                    strcpy(family[j],"@\0");
                strcpy(family[i+num+1],"#\0");/* “#”移到数组末尾*/
                strcpy(family[i+num-1],chi);  /* 在最后一个“@”前添加新成员*/
                end=1;              /* end为时标记已添加*/
            }
            else
            {
                for(j=i; j>=curpos; j--)      /* 当前位置到数组最后的全部信息后移一行*/
                    strcpy(family[j+1],family[j]);
                strcpy(family[curpos],chi);  /* 将新结点存储到“@”的前一行*/
            }
            if(end==1) /* 若end为，则数组末尾下标后移num位*/
                i=i+num;
            for(j=0; j<=i+1; j++) /* 将数组所有信息写入文件*/
            {
                fputs(family[j],fp);
                fputc('\n',fp);            /* 一个信息存一行*/
            }
            fclose(fp);                      /* 关闭文件*/
            printf("添加新成员成功！\n");
        }
        else
            printf("添加新成员失败！\n");
    }
}
void Ancesstor(TriTree *t)            /* 查找成员所有祖先*/
{
    if(t->parent==NULL)
        printf("%s成员无祖先",t->data);
    else
    {
        printf("%s的祖先为：",t->data);
        while(t->parent!=NULL)
        {
            printf("%s ",t->parent->data);
            t=t->parent;
        }
    }
}
void Parent(TriTree *t)
{
    if(t->parent!=NULL)  /* 若该成员为祖先，则无双亲*/
        printf("%s 的双亲为%s\n",t->data,t->parent->data);
    else
        printf("%s 无双亲！\n",t->data);
}
void Brothers(TriTree *t,DataType str[])    /* 查找兄弟*/
{
    if(t->parent!=NULL)      /* 若该结点是祖先，则无兄弟*/
    {
        t=t->parent;                          /* 该结点的兄弟即为其双亲除该成员以外的所有孩子*/
        if(t->lchild&&t->lchild->rchild)    /* 当前结点的左孩子及其右孩子都存在*/
        {
            printf("%s 的所有兄弟有：",str);
            t=t->lchild;
            while(t)            /* 遍历当前成员左孩子的右子树*/
            {
                if(strcmp(t->data,str)!=0)  /* 遍历右子树，选择输出*/
                    printf("%s  ",t->data); /* 访问当前结点*/
                t=t->rchild;
            }
            printf("\n");
        }
        else
            printf("%s 无兄弟！\n",str);
    }
    else
        printf("%s 无兄弟！\n",str);
}
void Children(TriTree *t)          /* 遍历左孩子*/
{
    if(t->lchild)                  /* 当前结点存在左孩子*/
    {
        printf("%s 的所有孩子有：",t->data);
        t=t->lchild;        /* 遍历当前成员左孩子的右子树*/
        while(t)                  /* 不空*/
        {
            printf("%s  ",t->data);/* 访问当前成员*/
            t=t->rchild;
        }
        printf("\n");
    }
    else
        printf("%s 无孩子！\n",t->data);
}
/* 中序遍历一棵树*/
void InOrder(TriTree *t)
{
    if(t)                      /* 二叉树存在*/
    {
        InOrder(t->lchild);    /* 中序遍历左子树*/
        printf("%s  ",t->data);/* 访问成员*/
        InOrder(t->rchild);    /* 中序遍历右子树*/
    }
}
void Descendants(TriTree *t)  /* 遍历左孩子*/
{
    if(t->lchild)              /* 当前结点存在左孩子*/
    {
        printf("%s的所有子孙后代有：",t->data);
        InOrder(t->lchild);  /* 中序遍历当前结点的左右子树*/
        printf("\n");
    }
    else
        printf("%s无后代！\n",t->data);
}
void Print()
{
    printf("每一代人的分布如下:\n");
    int i=0;
    while(family[i][0]!='#')
    {
        if(family[i][0]!='@')
            printf("%s ",family[i]);
        else
            printf("\n");
            i++;
    }
}
void Correct(TriTree *T)//修改家族成员的信息
{
    int tag;
    FILE *fp;
    fp=fopen(fname,"w");
    int i=0;
    if(fp)
    {
        while(strcmp(T->data,family[i])!=0)
        {
            i++;
            tag=i;
        }
        i=0;
        family[tag][0]='\0';
        DataType newname[MAXNUM];
        printf("请输入正确的修改信息:\n");
        gets(newname);
        strcpy(family[tag],newname);
        for(int j=0;j<100; j++) /* 将数组所有信息写入文件*/
        {
            fputs(family[j],fp);
            fputc('\n',fp);            /* 一个信息存一行*/
        }
         fclose(fp);
    }
    printf("已修改成功!\n");
}
void Delete(TriTree *T,DataType name[MAXNUM])
{

    TriTree *s=Search(T,name);
    s->data[0]='\0';
    printf("删除成功！\n");
    printf("其先序遍历为：\n");
    PreOrder(T);
    printf("\n");

}
int main()
{
    DataType str[MAXNUM];
    int flag,start=0;
    TriTree *temp,*tree=NULL;
    while(1)
    {
		printf("\t\t*********************************************************\n");
        printf("\t\t|*               欢迎使用家族关系查询系统！             *|\n");
        printf("\t\t|*                   请输入(1-10)                       *|\n");
        printf("\t\t|*            1. 新建一个家庭关系                       *|\n");
        printf("\t\t|*            2. 打开一个家庭关系                       *|\n");
        printf("\t\t|*            3. 添加新成员的信息                       *|\n");
        printf("\t\t|*            4. 查找一个成员的祖先                     *|\n");
        printf("\t\t|*            5. 查找一个成员的双亲                     *|\n");
        printf("\t\t|*            6. 查找一个成员的兄弟                     *|\n");
        printf("\t\t|*            7. 查找一个成员的孩子                     *|\n");
        printf("\t\t|*            8. 查找一个成员的子孙后代                 *|\n");
        printf("\t\t|*            9. 修改家庭成员的信息                     *|\n ");
		printf("\t\t|*            10.删除家族成员                           *|\n");
		printf("\t\t|*            11.退出系统                               *|\n");
		printf("\t\t*********************************************************\n");
		printf("\t\t请输入你的选择:\n");
		scanf("%d",&flag);
        if(flag==1)
            printf("请输入要建立的家族:\n");
        if(flag==2)
            printf("请输入要打开的家族:\n");
        if(flag==3)
            printf("请输入添加成员的家族:\n");
        if(flag==4)
            printf("请输入要查找祖先的成员:\n");
        if(flag==5)
            printf("请输入要查找双亲的成员:\n");
        if(flag==6)
            printf("请输入要查找其兄弟的成员:\n");
        if(flag==7)
            printf("请输入要查找其孩子的成员\n");
        if(flag==8)
            printf("请输入要查找其子孙后代的成员:\n");
        if(flag==9)
            printf("请输入要修改的成员:\n");
        if(flag==10)
            printf("请输入要删除的错误信息的成员：\n");
        if(flag==11)
          printf("谢谢本次使用家族关系处理系统!");
		fflush(stdin);
        gets(str);
        if(!(flag==1||flag==2||flag==11)&&start==0)
        {
            /* 如果第一次输入函数不是建立、打开或退出，则重新输入*/
            printf("\t请先建立或打开一个家族关系！\n");
            continue;
        }
        start=1;                /* 标记不是第一次输入input */
        if(flag>=4&&flag<=10&&start==1) /* 函数需要字符串型参数name */
        {
            temp=Search(tree,str);/* 若存在则返回结点*/
            if(!temp)            /* 若不存在则返回*/
            {
                printf("该成员不存在！\n");
                continue;
            }
        }
        switch(flag)              /* 根据flag标记调用函数*/
        {
        case 1:
            tree=Create(str);
            break;
        case 2:
            tree=Open(str);
            Print();
            break;
        case 3:
            Append(tree);
            break;
        case 4:
            Ancesstor(temp);
            printf("\n");
            break;
        case 5:
            Parent(temp);
            break;
        case 6:
            Brothers(temp,str);
            break;
        case 7:
            Children(temp);
            break;
        case 8:
             Descendants(temp);
            break;
		case 9:
			Correct(temp);
			break;
        case 10:
            Delete(tree,str);
            break;
        case 11:
            exit(0);
        }
    }
	return 0;
}