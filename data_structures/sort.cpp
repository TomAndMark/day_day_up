#include <iostream>
#include <vector>
#include <stack>

//using namespace std;

/*********************
* 函数名： portition(快排部分函数)
* 返回值： 返回key所在的下标位置
******************/
template <class T>
int portition (std::vector<T> &s, int left, int right) 
{
	T key = s[left];
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

		while (left < right && s[left] < key)
		{
			++left;
		}
		if (left < right)
		{
			s[right--] = s[left];
		}
	}
	s[left] = key;

	return left;
}

/***********************************
* 函数名:   quick_sort(递归快排)
* 参数说明: s  无序vector；
*		   left 最左边vector下标, right 最右边vector下标(长度-1)
*递归式: quick_sort(s, from, right-1);
*	     quick_sort(s, right+1, to);
*
*递归临界值:if (left >= right) return;   1:left >= right  5:left < right
* 复杂度说明:O(nlogn) 空间赋值复杂度O(n) 
*
************************************/
template <class T>
void quick_sort(std::vector<T> &s, int left, int right)
{
	if (left >= right)
		return ;
	int mid = portition(s, left, right);
	quick_sort(s, left, mid - 1);
	quick_sort(s, mid + 1, right);
}


/***********************************
* 函数名:   quick_sort1(非递归快排)
* 参数说明: s  无序vector；
*		   left 最左边vector下标, right 最右边vector下标(长度-1)
* stack st:其实就是用栈保存每一个待排序子串的"首尾元素下标"，
  下一次while循环时取出这个范围，对这段子序列进行partition操作
  注意顺序先 if(mid + 1 < right)：right->mid + 1  
          后 if (left < mid -1)：mid - 1->left  原则先大后小
*
* 复杂度说明:O(nlogn) 空间赋值复杂度O(n) 
* 
* 用非递归的原因：递归数据规模很大时，递归的算法很容易导致栈溢出
*
* 非递归和递归的效率比较：
递归：栈由程序自动产生。包含:函数调用时的"参数"和函数中的"局部变量"
如果“局部变量很多”或者“函数内部又调用了其他函数”，则栈会很大,效率自然下降。

非递归：每次循环使用自己预先创建的栈，因此不管程序复杂度如何，都不会影响程序效率。
所以递归不一定都比非递归效率低。(当局部变量少，递归次数少时)
*
************************************/
template <class T>
void quick_sort1(std::vector<T> &s, int left, int right)  //一定要引用
{
	if (left >= right)
		return ;
	
	std::stack<int> st;
	int mid = portition(s, left, right);
	if (mid + 1 < right)
	{
		st.push(right);
		st.push(mid + 1);
	}

	if (left < mid -1)
	{
		st.push(mid - 1);
		st.push(left);
	}

	while (!st.empty())
	{
		int from = st.top();
		st.pop();

		int to = st.top();
		st.pop();

		mid = portition(s, from, to);
		if (mid + 1 < to)
		{
			st.push(to);
			st.push(mid + 1);
		}

		if (from < mid -1)
		{
			st.push(mid - 1);
			st.push(from);
		}
	}
}



int main(int argc, char const *argv[])
{
    std::vector<int> s;
    s.push_back(10);
    s.push_back(4);
    s.push_back(23);
    s.push_back(3);
    s.push_back(7);
    s.push_back(19);
    //quick_sort(s, 0, 5);

    quick_sort1(s, 0, 5);
    for (int i = 0; i < 6; ++i)
    {
    	std::cout << s[i] << std::endl;
    }

	return 0;
}