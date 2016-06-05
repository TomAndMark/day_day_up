/********************************************************************
*
*　 文件名：sort.c
*
*　 文件描述：各类排序
*		1.冒泡排序	
*		2.交换排序
*       3.选择排序	
*       4.插入排序
*       5.基数排序
*		6.快速排序
*		7.并归排序
*　 创建人：MARK, 2016年6月5日
*
*　 版本号：1.0
*
*　 修改记录：无
*
********************************************************************/
#include <stdio.h>
#include <stdlib.h>
/***************************
	排序方式:冒泡排序
	bubble_sort : 升序
	bubble_desc_sort : 降序
	时间赋值度:O(n^2)
	空间复杂度:O(1)
****************************/
void bubble_sort(int *s, int len)
{
	int i, j, tmp;
	for (i = 0; i < len-1; ++i)        //i为已经确定位置个数,只需确定len-1个就行
	{
		for (j = 0; j < len-1-i; ++j)  //j为当前比较下标的前一个下标
		{
			if (s[j] > s[j+1])
			{
				tmp = s[j+1];
				s[j+1] = s[j];
				s[j] = tmp;
			}
		}
	}
}

void bubble_desc_sort(int *s, int len)
{
	int i, j, tmp;
	for (i = 0; i < len-1; ++i)        
	{
		for (j = 0; j < len-1-i; ++j)  
		{
			if (s[j] < s[j+1])        //将'>' 改为 '<'
			{
				tmp = s[j+1];
				s[j+1] = s[j];
				s[j] = tmp;
			}
		}
	}
}





/**************************
	排序方式:交换排序
	exchange_sort : 升序
	exchange_desc_sort : 降序
	时间赋值度:O(n^2)
	空间复杂度:O(1)
***************************/
void exchange_sort(int *s, int len)
{
	int i, j, tmp;
	for (i = 0; i < len-1; ++i)           //i为确定位置元素的下标
	{
		for (j = i+1; j < len; ++j)       //j为比较元素的下标
		{
			if (s[i] > s[j])       
			{
				tmp = s[j];
				s[j] = s[i];
				s[i] = tmp;
			}	
		}
	}
}

void exchange_desc_sort(int *s, int len)
{
	int i, j, tmp;
	for (i = 0; i < len-1; ++i)
	{
		for (j = i+1; j < len; ++j) 
		{
			if (s[i] < s[j])           //将'>' 改为 '<'
			{
				tmp = s[j];
				s[j] = s[i];
				s[i] = tmp;
			}	
		}
	}
}





/**************************
	排序方式:选择排序(假设第一个为最值):找到最值后 交换一次。最多交换len-2次
	selection_sort : 升序
	selection_desc_sort : 降序
	时间赋值度:O(n^2)
	空间复杂度:O(2) min, index 
***************************/
void selection_sort(int *s, int len)
{
	int i, j, min, index;
	for (i = 0; i < len-1; ++i)         //i为确定的下标
	{
		min = s[i];				        //纪录最值,交换时与tmp类似
		index = i;                      //index 为最值的下标
		for (j = i+1; j < len; ++j)     //j为比较元素的下标
		{
			if (min > s[j])
			{
				min = s[j];
				index = j;
			}
		}

		if (i != index)
		{
	     	s[index] = s[i];
	     	s[i] = min;
		}
	}
}

void selection_desc_sort(int *s, int len)
{
	int i, j, max, index;
	for (i = 0; i < len-1; ++i)         
	{
		max = s[i];				        
		index = i;                      
		for (j = i+1; j < len; ++j)    
		{
			if (max < s[j])            //将'>' 改为 '<'
			{
				max = s[j];
				index = j;
			}
		}

		if (i != index)
		{
	     	s[index] = s[i];
	     	s[i] = max;
		}
	}
}




/**************************
	排序方式:插入排序:从第二个数开始,把这个数插入前面适当的位置
	(从第二个起,保证前面的数总是有序的)
	insert_sort : 升序
	insert_desc_sort : 降序
	时间赋值度:O(n^2)
	空间复杂度:O(2) tmp  
***************************/
void insert_sort (int *s, int len)     //时刻谨记前面的数是有序的
{
	int i, j, tmp;
	for (i = 1; i < len; ++i)
	{
		tmp = s[i];		               //tmp 保存 要插入的数
		j = i-1;                       //j用来表示前面元素的下标
		while (s[j] > tmp && j >= 0)   //两个限定1.前面元素比插入元素大 2.当插入数最小时退出while
		{
			s[j+1] = s[j];             //覆盖tmp的数据,s[j+1] 而不是 s[i] 
			--j; 
		}
		s[j+1] = tmp;                 //此时的j+1 是多出来的数据
	}
}

void insert_desc_sort (int *s, int len)    
{
	int i, j, tmp;
	for (i = 1; i < len; ++i)
	{
		tmp = s[i];		              
		j = i-1;                      
		while (s[j] < tmp && j >= 0)     //将'>' 改为 '<'
		{
			s[j+1] = s[j];             
			--j; 
		}
		s[j+1] = tmp;                 
	}
}





/********************************************************
*函数名称：GetNumInPos
*参数说明：num 一个整形数据
*		   pos 表示要获得的整形的第pos位数据
*说明：    找到num的从低到高的第pos位的数据
*********************************************************/
int GetNumInPos(int num,int pos)
{
	int temp = 1;
	int i;
	for (i = 0; i < pos - 1; ++i)
		temp *= 10;

	return (num / temp) % 10;
}

/********************************************************
*函数名称：RadixSort
*参数说明：pDataArray 无序数组；
*		   iDataNum为无序数据个数
*说明：    基数排序
*平均时间复杂度：O(d(n+radix)) (d即表示整形的最高位数,n为元素个数,radix一般为10关键字范围)
*空间复杂度：O(n+radix)        (radix一般为10 0~9，用于存储临时的序列)
*稳定性:稳定 (为交换,装桶)
*********************************************************/
#define RADIX_10 10    //整形排序
#define KEYNUM_31 10     //关键字个数，这里为整形位数
void RadixSort(int* pDataArray, int iDataNum)
{
	int *radixArrays[RADIX_10];                  //分别为0~9的序列空间
	int i;
	for (i = 0; i < 10; i++)
	{
		radixArrays[i] = (int *)malloc(sizeof(int) * (iDataNum + 1));
		radixArrays[i][0] = 0;                   //index为0处记录这组数据的个数
	}
	
	int pos;
	int j,k;
	for (pos = 1; pos <= KEYNUM_31; ++pos)       //从个位开始到31位
	{
		for (i = 0; i < iDataNum; ++i)           //分配过程
		{
			int num = GetNumInPos(pDataArray[i], pos);
			int index = ++radixArrays[num][0];
			radixArrays[num][index] = pDataArray[i];
		}

		for (i = 0, j =0; i < RADIX_10; i++)    //收集
		{
			for (k = 1; k <= radixArrays[i][0]; ++k)
				pDataArray[j++] = radixArrays[i][k];
			radixArrays[i][0] = 0;             //复位
		}
	}
}



/***********************************
* 函数名:   quick_sort(快排)
* 参数说明: s  无序数组；
*		   left 最左边数组下标, right 最右边数组下标(长度-1)
*递归式: quick_sort(s, from, right-1);
*	     quick_sort(s, right+1, to);
*
*递归临界值:if (left >= right) return;   1:left >= right  6:left < right
* 复杂度说明:O(nlogn) 空间赋值复杂度O(n) 
*
************************************/
void quick_sort(int *s, int left, int right)
{
	if (left >= right)
	{
		return;
	}

	int from = left;
	int to = right;
	int key = s[left];
	while (left < right)
	{
		while (left < right && key < s[right])
		{
			--right;
		}

		if (left < right)
		{
			s[left++] = s[right];
		}

		while (left < right && key > s[left])
		{
			++left;
		}

		if (left < right)
		{
			s[right--] = s[left];
		}
	}
	s[right] = key;   //s[left] = key; 也行

	quick_sort(s, from, right-1);
	quick_sort(s, right+1, to);
}


/***********************************
* 函数名:   merge_sort(并归排序)
* 参数说明: a,b  有序数组；
*		   lenA, lenB 数组长度
*
* 复杂度说明:时间复杂度为O(nlogn) 
*		    空间复杂度为 O(n)
*			稳定性:效率高、稳定
*
************************************/
void merge_sort(int *a, int lenA, int *b, int lenB)
{
	int *array = (int *)malloc((lenA+lenB)*sizeof(int));
	int indexa = 0, indexb = 0;
	int i = 0;
	while (1)
	{
		if (indexa < lenA)
		{
			while (a[indexa]>=b[indexb] && indexb<lenB)
			{
	            array[i] = b[indexb];
	            ++indexb;
	            ++i;
	        }	
		}

		if (indexb < lenB)
		{
	        while(a[indexa]<b[indexb] && indexa<lenA)
		    {
		          array[i] = a[indexa];
		          ++indexa;
		          ++i;
		    }	
		}

	    if(indexa==lenA && indexb<lenB)
	    {
	          for(; indexb<lenB; ++indexb,++i)
	          {
	                array[i] = b[indexb];
	          }
	    }

	    if(indexb==lenB && indexa<lenA)
	    {
	          for(; indexa<lenA; ++indexa,++i)
	          {
	                array[i] = a[indexa];
	          }
	    }

	    if(indexa==lenA && indexb==lenB)
	       break;
	}

	for(i=0; i < lenA+lenB; ++i)
	{
		printf("%d\t",array[i]);
	}

	free(array);
	array=NULL;
	printf("\n");
	
}


int main(int argc, char const *argv[])
{
	int s[6] = {53,231,22,31,64,99};
	// bubble_sort(s, 6);
	// bubble_desc_sort(s, 6);

	// exchange_sort(s, 6);
	// exchange_desc_sort(s, 6);

	// selection_sort(s, 6);
	// selection_desc_sort(s, 6);

	// insert_sort(s, 6);
	// insert_desc_sort(s, 6);

	// RadixSort(s, 6);

	quick_sort(s, 0, 5);

	int i;
	for (i = 0; i < 6; ++i)
	{
		printf("%d\t", s[i]);
	}
	printf("\n");

	int a[]={1,31,53,77,89,100};
	int b[]={11,22,33,44,55,66,77,88};

	merge_sort(a, 6, b, 8);

	return 0;
}
