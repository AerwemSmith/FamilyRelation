TriTree *Create(DataType familyname[MAXNUM])/* ���������ϵ�������ļ�*/
{
    int i=0;                  /* i����family�����±�*/
    DataType ch,str[MAXNUM];  /* ch�洢�����y��n��str�洢������ַ���*/
    TriTree *t;
    FILE *fp;
    strcpy(fname,familyname);  /* �Լ�����Ϊ�ı��ļ����洢*/
    strcat(fname,".txt");
    fp=fopen(fname,"r");      /* �Զ�ȡ��ʽ���ļ�*/
    if(fp)                    /* �ļ��Ѵ���*/
    {
        fclose(fp);
        printf("%s �ļ����ϵ�Ѵ��ڣ����½����밴��Y��,ֱ�Ӵ��밴��N��\n",familyname);
        ch=getchar();
        getchar();            /* ���ջس�*/
        if(ch=='N'||ch=='n')
        {
            t=Open(familyname);/* ֱ�Ӵ�*/
            return t;
        }
    }
    if(!fp||ch=='Y'||ch=='y')    /* ���½�����ִ�����²���*/
    {
        fp=fopen(fname,"w");      /* ��д�뷽ʽ���ļ������������½�*/
        printf("�밴��������㣬ÿ�������Ϣռһ��\n");
        printf("�ֵ���������ԡ�@��Ϊ��־��������־Ϊ��#��\n��������������:");
        gets(str);
        fputs(str,fp);
        fputc('\n',fp);
        strcpy(family[i],str);  /* ����Ա��Ϣ�洢���ַ�������*/
        i++;                      /* family�����±����*/
        while(str[0]!='#')
        {
            printf("����������Ա:");      /* �Ե���ʾ����ʾ��������*/
            gets(str);
            fputs(str,fp);    /* д���ļ��У�ÿ����Ϣռһ��*/
            fputc('\n',fp);
            strcpy(family[i],str);/* ����Ա��Ϣ�洢���ַ�������*/
            i++;                  /* family�����±����*/
        }
        fclose(fp);              /* �ر��ļ�*/
        t=TriTreeCreate();  /* ����family������Ϣ����������*/
        printf("�����ϵ�ѳɹ�������\n");
        return t;                /* ������*/
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
    LinkQueue *q=LQueueCreateEmpty();/* ����һ���յĶ��У��洢ָ������ָ��*/
    int i=0,flag=0,start=0;
    DataType str[MAXNUM];      /* ���family��������Ϣ*/
    strcpy(str,family[i]);          /* ����*/
    i++;                            /* family�����±����*/
    while(str[0]!='#')            /* û����������־����ѭ��*/
    {
        while(str[0]!='@')    /* û�����ֵ����������־����*/
        {
            if(root==NULL)          /* ����*/
            {
                root=(TriTree *)malloc(sizeof(TriTree));/* ����ռ�*/
                strcpy(root->data,str);
                root->parent=NULL;
                root->lchild=NULL;
                root->rchild=NULL;
                LQueueEnQueue(q,root);                    /* ��root�������*/
                tree=root;
            }
            else                              /* ��Ϊ����*/
            {
                t=(TriTree *)malloc(sizeof(TriTree)); /* ����ռ�*/
                strcpy(t->data,str);
                t->lchild=NULL;
                t->rchild=NULL;
                t->parent=LQueueGetFront(q);        /* ��ǰ����˫��Ϊ��ͷԪ��*/
                LQueueEnQueue(q,t);                /* ���*/
                if(!flag)      /* flagΪ0����ǰ���û������*/
                    root->lchild=t;
                else        /* flagΪ1����ǰ�����������*/
                    root->rchild=t;
                root=t;                /* rootָ���µĽ��t */
            }
            flag=1;            /* ��ǵ�ǰ�����������*/
            strcpy(str,family[i]);
            i++;
        }
        if(start!=0)              /* ��ǲ��ǵ�һ�γ��֡�@��*/
        {
            LQueueDeQueue(q,x);              /* ����*/
            if(q->front!=NULL)
                root=LQueueGetFront(q);/* rootΪ��ͷԪ��*/
        }
        start=1;                      /* ����ѳ��ֹ���@��*/
        flag=0;              /* ��@������Ľ��һ��Ϊ����*/
        strcpy(str,family[i]);
        i++;
    }
    return tree;                        /* ������*/
}
TriTree *Open(DataType familyname[MAXNUM])
{
    int i=0,j=0;
    DataType ch;
    FILE *fp;
    TriTree *t;
    strcpy(fname,familyname);  /* �Լ�����Ϊ�ı��ļ����洢*/
    strcat(fname,".txt");
    fp=fopen(fname,"r");            /* �Զ�ȡ��ʽ���ļ�*/
    if(fp==NULL)                    /* �ļ�������*/
    {
        printf("%s �ļ����ϵ�����ڣ�\n",familyname);
        return NULL;
    }
    else
    {
        ch=fgetc(fp);              /* ���ַ���ȡ�ļ�*/
        while(ch!=EOF)            /* �����ļ�β����*/
        {
            if(ch!='\n')        /* ch��Ϊһ�������Ϣ�Ľ�β*/
            {
                family[i][j]=ch;  /* ���ļ���Ϣ�洢��family������*/
                j++;
            }
            else
            {
                family[i][j]='\0';    /* �ַ���������־*/
                i++;              /* family�������±����*/
                j=0;              /* family�������±����*/
            }
            ch=fgetc(fp);        /* ������ȡ�ļ���Ϣ*/
        }
        fclose(fp);              /* �ر��ļ�*/
        t=TriTreeCreate();  /* ���ú���������������*/
        printf("�����ϵ�ѳɹ��򿪣�\n");
        printf("������������Ϊ:\n");
        PreOrder(t);
        printf("\n");
        return t;
    }
}
TriTree *Search(TriTree *t,DataType str[])
{
    TriTree *temp;
    if(t==NULL)                /* ��������򷵻�NULL */
        return NULL;
    else if(strcmp(t->data,str)==0) /* ����ҵ����ظó�Աָ��*/
        return t;
    else              /* ���û�ҵ����������������в���*/
    {
        temp=Search(t->lchild,str); /* �ݹ����*/
        if(temp)                    /* ��㲻�������*/
            return(Search(t->lchild,str));
        else
            return(Search(t->rchild,str));
    }
}
void Append(TriTree *t)
{
    int i=0,j,parpos=1,curpos,num,end=0,count=-1;
    DataType chi[MAXNUM],par[MAXNUM];/* �洢����ĺ��Ӻ���˫�׽��*/
    TriTree *tpar,*temp;
    FILE *fp;
    printf("������Ҫ��ӵĳ�Ա:\n");
    gets(chi);
    printf("������Ҫ��ӳ�Ա�ĸ���:");
    gets(par);
    tpar=Search(t,par);  /* ����˫�׽���Ƿ����*/
    if(!tpar)
        printf("%s �ó�Ա�����ڣ�\n");
    else                /* ����������亢��*/
    {
        temp=(TriTree *)malloc(sizeof(TriTree));/* ����ռ�*/
        temp->parent=tpar;
        strcpy(temp->data,chi);
        temp->lchild=NULL;        /* �½�����Һ����ÿ�*/
        temp->rchild=NULL;
        if(tpar->lchild)                    /* ��Ա��������*/
        {
            tpar=tpar->lchild; /* ������ǰ��Ա���ӵ�������*/
            while(tpar->rchild)          /* ��ǰ����Һ��Ӵ���*/
                tpar=tpar->rchild;        /* ���������Һ���*/
            tpar->rchild=temp;                /* ���½����ӵ����к���֮��*/
        }
        else                      /* û�к�����ֱ�����*/
            tpar->lchild=temp;
        fp=fopen(fname,"w");        /* ��д�뷽ʽ���ļ�*/
        if(fp)
        {
            while(strcmp(par,family[i])!=0&&family[i][0]!='#')
            {
                if(family[i][0]!='@')        /* ����˫����������λ��*/
                    parpos++;                /* parpos����*/
                i++;              /* family�������±����*/
            }
            i=0;                    /* family�������±��0*/
            while(family[i][0]!='#')
            {
                if(family[i][0]=='@')        /* ���ҡ�@���ĸ�������һ������*/
                    count++;              /* count�ۼӸ���*/
                if(count==parpos)            /* ˵���ˡ�@������ǰһ����@��֮ǰΪpar�ĺ���*/
                    curpos=i;            /* curpos�Ƶ�ǰλ��*/
                i++;              /* family�������±����*/
            }
            if(count<parpos)          /* ��@����С��parpos��*/
            {
                num=parpos-count;    /* ��ӡ�@������Ϊnum */
                for(j=i; j<=i+num; j++) /* ������ĩβ��ӡ�@��*/
                    strcpy(family[j],"@\0");
                strcpy(family[i+num+1],"#\0");/* ��#���Ƶ�����ĩβ*/
                strcpy(family[i+num-1],chi);  /* �����һ����@��ǰ����³�Ա*/
                end=1;              /* endΪʱ��������*/
            }
            else
            {
                for(j=i; j>=curpos; j--)      /* ��ǰλ�õ���������ȫ����Ϣ����һ��*/
                    strcpy(family[j+1],family[j]);
                strcpy(family[curpos],chi);  /* ���½��洢����@����ǰһ��*/
            }
            if(end==1) /* ��endΪ��������ĩβ�±����numλ*/
                i=i+num;
            for(j=0; j<=i+1; j++) /* ������������Ϣд���ļ�*/
            {
                fputs(family[j],fp);
                fputc('\n',fp);            /* һ����Ϣ��һ��*/
            }
            fclose(fp);                      /* �ر��ļ�*/
            printf("����³�Ա�ɹ���\n");
        }
        else
            printf("����³�Աʧ�ܣ�\n");
    }
}
void Ancesstor(TriTree *t)            /* ���ҳ�Ա��������*/
{
    if(t->parent==NULL)
        printf("%s��Ա������",t->data);
    else
    {
        printf("%s������Ϊ��",t->data);
        while(t->parent!=NULL)
        {
            printf("%s ",t->parent->data);
            t=t->parent;
        }
    }
}
void Parent(TriTree *t)
{
    if(t->parent!=NULL)  /* ���ó�ԱΪ���ȣ�����˫��*/
        printf("%s ��˫��Ϊ%s\n",t->data,t->parent->data);
    else
        printf("%s ��˫�ף�\n",t->data);
}
void Brothers(TriTree *t,DataType str[])    /* �����ֵ�*/
{
    if(t->parent!=NULL)      /* ���ý�������ȣ������ֵ�*/
    {
        t=t->parent;                          /* �ý����ֵܼ�Ϊ��˫�׳��ó�Ա��������к���*/
        if(t->lchild&&t->lchild->rchild)    /* ��ǰ�������Ӽ����Һ��Ӷ�����*/
        {
            printf("%s �������ֵ��У�",str);
            t=t->lchild;
            while(t)            /* ������ǰ��Ա���ӵ�������*/
            {
                if(strcmp(t->data,str)!=0)  /* ������������ѡ�����*/
                    printf("%s  ",t->data); /* ���ʵ�ǰ���*/
                t=t->rchild;
            }
            printf("\n");
        }
        else
            printf("%s ���ֵܣ�\n",str);
    }
    else
        printf("%s ���ֵܣ�\n",str);
}
void Children(TriTree *t)          /* ��������*/
{
    if(t->lchild)                  /* ��ǰ����������*/
    {
        printf("%s �����к����У�",t->data);
        t=t->lchild;        /* ������ǰ��Ա���ӵ�������*/
        while(t)                  /* ����*/
        {
            printf("%s  ",t->data);/* ���ʵ�ǰ��Ա*/
            t=t->rchild;
        }
        printf("\n");
    }
    else
        printf("%s �޺��ӣ�\n",t->data);
}
/* �������һ����*/
void InOrder(TriTree *t)
{
    if(t)                      /* ����������*/
    {
        InOrder(t->lchild);    /* �������������*/
        printf("%s  ",t->data);/* ���ʳ�Ա*/
        InOrder(t->rchild);    /* �������������*/
    }
}
void Descendants(TriTree *t)  /* ��������*/
{
    if(t->lchild)              /* ��ǰ����������*/
    {
        printf("%s�������������У�",t->data);
        InOrder(t->lchild);  /* ���������ǰ������������*/
        printf("\n");
    }
    else
        printf("%s�޺����\n",t->data);
}
void Print()
{
    printf("ÿһ���˵ķֲ�����:\n");
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
void Correct(TriTree *T)//�޸ļ����Ա����Ϣ
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
        printf("��������ȷ���޸���Ϣ:\n");
        gets(newname);
        strcpy(family[tag],newname);
        for(int j=0;j<100; j++) /* ������������Ϣд���ļ�*/
        {
            fputs(family[j],fp);
            fputc('\n',fp);            /* һ����Ϣ��һ��*/
        }
         fclose(fp);
    }
    printf("���޸ĳɹ�!\n");
}
void Delete(TriTree *T,DataType name[MAXNUM])
{

    TriTree *s=Search(T,name);
    s->data[0]='\0';
    printf("ɾ���ɹ���\n");
    printf("���������Ϊ��\n");
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
        printf("\t\t|*               ��ӭʹ�ü����ϵ��ѯϵͳ��             *|\n");
        printf("\t\t|*                   ������(1-10)                       *|\n");
        printf("\t\t|*            1. �½�һ����ͥ��ϵ                       *|\n");
        printf("\t\t|*            2. ��һ����ͥ��ϵ                       *|\n");
        printf("\t\t|*            3. ����³�Ա����Ϣ                       *|\n");
        printf("\t\t|*            4. ����һ����Ա������                     *|\n");
        printf("\t\t|*            5. ����һ����Ա��˫��                     *|\n");
        printf("\t\t|*            6. ����һ����Ա���ֵ�                     *|\n");
        printf("\t\t|*            7. ����һ����Ա�ĺ���                     *|\n");
        printf("\t\t|*            8. ����һ����Ա��������                 *|\n");
        printf("\t\t|*            9. �޸ļ�ͥ��Ա����Ϣ                     *|\n ");
		printf("\t\t|*            10.ɾ�������Ա                           *|\n");
		printf("\t\t|*            11.�˳�ϵͳ                               *|\n");
		printf("\t\t*********************************************************\n");
		printf("\t\t���������ѡ��:\n");
		scanf("%d",&flag);
        if(flag==1)
            printf("������Ҫ�����ļ���:\n");
        if(flag==2)
            printf("������Ҫ�򿪵ļ���:\n");
        if(flag==3)
            printf("��������ӳ�Ա�ļ���:\n");
        if(flag==4)
            printf("������Ҫ�������ȵĳ�Ա:\n");
        if(flag==5)
            printf("������Ҫ����˫�׵ĳ�Ա:\n");
        if(flag==6)
            printf("������Ҫ�������ֵܵĳ�Ա:\n");
        if(flag==7)
            printf("������Ҫ�����亢�ӵĳ�Ա\n");
        if(flag==8)
            printf("������Ҫ�������������ĳ�Ա:\n");
        if(flag==9)
            printf("������Ҫ�޸ĵĳ�Ա:\n");
        if(flag==10)
            printf("������Ҫɾ���Ĵ�����Ϣ�ĳ�Ա��\n");
        if(flag==11)
          printf("лл����ʹ�ü����ϵ����ϵͳ!");
		fflush(stdin);
        gets(str);
        if(!(flag==1||flag==2||flag==11)&&start==0)
        {
            /* �����һ�����뺯�����ǽ������򿪻��˳�������������*/
            printf("\t���Ƚ������һ�������ϵ��\n");
            continue;
        }
        start=1;                /* ��ǲ��ǵ�һ������input */
        if(flag>=4&&flag<=10&&start==1) /* ������Ҫ�ַ����Ͳ���name */
        {
            temp=Search(tree,str);/* �������򷵻ؽ��*/
            if(!temp)            /* ���������򷵻�*/
            {
                printf("�ó�Ա�����ڣ�\n");
                continue;
            }
        }
        switch(flag)              /* ����flag��ǵ��ú���*/
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