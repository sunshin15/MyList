#include<iostream>
using namespace std;

class empty{};//pop an empty list.
class errorIndex{};//give the function a wrong index.

template<class T>
class MyList{
private:
	T *a;
	int len;
	int size;

	void double_space();
	int partition(T* a,int low,int high);
	void quickSort(T* a,int low,int high);
public:
	MyList(){
		size = 100;
		len=0;
		a = new T [size];		
	}
	MyList(int num, const T &item);//copy item num times.
	MyList(const MyList &l);//copy another MyList.
    MyList(T* arr, int len2);//len2 elements of arr.

	void push(const T &item);//add item at the end.
	T pop() throw (empty);//delete the final element and return it.
	void insert(int index, const T &item) throw(errorIndex);//insert item in the index(index).
	void clean();
	int get_size();
	void erase(int start, int end) throw(errorIndex); //delete elements from start to end (include start and end).
	T get_item(int index) throw(errorIndex);//return the element with index(index).
	MyList get_item(int start, int end) throw(errorIndex);//return a MyList with elements from start to end.
	int count(const T &item);//how many elements==item.
	void remove(const T &item);//delete the first element==item

	template<class T>
	friend MyList operator + (const MyList &l1, const MyList &l2); //merge two lists.
	template<class T>
	friend MyList operator + (const MyList &l1, const T &item); 
	MyList &operator = (const MyList &l);
	MyList &operator += (const T &item);
	MyList &operator += (const MyList &l);//add a list after this list
	T &operator [](int index) throw(errorIndex);

	template<class T>
	friend ostream &operator<<(ostream &, const MyList &);
    // example:[1, 2, 5, 4, 1]

	void sort(bool less=true);
	// if less=true ascending else descending

	void reverse();

	~MyList(){delete [] a;}
};

int main(){

	try{
		MyList<int> a, b;
	
		int i;
		for (i=0; i<5; ++i)
			a.push(i);
	
		// a = [0, 1, 2, 3, 4]
		a[3] = 15; // a = [0, 1, 2, 15, 4]
		a.sort(); // a = [0, 1, 2, 4, 15]
		a.reverse(); // a = [15, 4, 2, 1, 0]
		a += 12; // a = [15, 4, 2, 1, 0, 12]
		for (i=0; i<a.get_size(); ++i)
			cout<<a[i]<<endl;
		b = a.get_item(4, -3); // b = [] * if start > end ,return []
		b = a.get_item(3, -1); // b = [1, 0, 12] 
		a += b; // a = [15, 4, 2, 1, 0, 12, 1, 0, 12]
		for (i=0; i<a.get_size(); ++i)
			cout<<a.get_item(i)<<endl;
		cout<<a.count(5)<<endl;
		b.clean(); // b = []
		cout<<b.get_size()<<endl;
		a.erase(2, 5); 
		b = a + a; 
		b.insert(3, 116); 
		b.remove(4); 
		MyList<double> c(10, 3.14);
		for (i=0; i<100; ++i)
			c.push(1.1*i);
		cout<<c.get_item(100, 105)<<endl;
	}
	catch(empty){cout<<"Error:The list is already empty!"<<endl;}
	catch(errorIndex){cout<<"Error:The index out of range!"<<endl;}
	return 0;
}



//functions~~
template<class T>
void MyList<T>::double_space()
{
	T *a2=new T[size*2];
	for (int i=0;i<len;i++)
		a2[i]=a[i];
	delete [] a;
	a=a2;
	size*=2;
}

template<class T>
MyList<T>::MyList(int num, const T &item)
{
	len=num;
	size=len<=100?100:len*2;
	a=new T[size];
	for(int i=0;i<num;++i)
		a[i]=item;
	return;
}


template<class T>
MyList<T>::MyList(const MyList<T> &l)
{
	size=l.size;
	len=l.len;
	a=new T[size];
	for(int i=0;i<len;++i)
		a[i]=l.a[i];
}

template<class T>
MyList<T>::MyList(T* arr, int len2)
{
	//how to solve it if len2>arrMaxIndex?
	size=len2*2;
	len=len2;		
	a=new T[size];
	for (int i=0;i<len;i++)
		a[i]=arr[i];
}

template<class T>
void MyList<T>::push(const T &item)
{
	while (len>=size-1)
		double_space();
	a[len++]=item;	
}

template<class T>
T MyList<T>::pop()
{
	if (len=0)
		throw empty();
	len--;
	return(a[len]);
}

template<class T>
void MyList<T>::insert(int index, const T &item)
{
	if (index>=len ||index<0)
	{
		throw errorIndex();
	}
	if (len>=size-1) double_space();
	for(int i=len;i<index+1;i--)
		a[i]=a[i-1];
	a[index]=item;
}

template<class T>
void MyList<T>::clean()
{
	len=0;		
}

template<class T>
int MyList<T>::get_size()
{
	return len;
}

template<class T>
void MyList<T>::erase(int start, int end)
{										

	if (start<0) start+=len;
	if (end<0) end+=len;
	if (start<0 || end>=len || start>len)
	{
		throw errorIndex();
	}
	for (int i=start;i<len-end+start-1;i++)
		a[i]=a[i+end-start+1];

	len-=end-start+1;
}

template<class T>
MyList<T> MyList<T>::get_item(int start, int end)
{
	if (start<0) start+=len;
	if (end<0) end+=len;
	if (start<0 || end>=len)
	{
		throw errorIndex();
	}
	MyList newList;
	newList.len=end-start+1;
	newList.size=size;
	newList.a=new T[size];
	if (start>end)
	{
		newList.len=0;
		return newList;
	}

	for (int i=start;i<=end;++i)
		newList.a[i-start]=a[i];
	return newList;
}

template<class T>
T MyList<T>::get_item(int index)
{
	if (index<0) 
		index+=len;
	if (index<0 || index>=len)
	{
		throw errorIndex();
	}
	return a[index];
}

template<class T>
int MyList<T>::count(const T &item)
{
	int sum=0;
	for (int i=0;i<len;i++)
		if (a[i]==item)
			++sum;
	return sum;
}

template<class T>
void MyList<T>::remove(const T &item)
{
	int pos=0;
	while(a[pos]!=item)
	{
		pos++;
		if (pos>=len)
		{
			cout<<"There are no:"<<item<<"!"<<endl; 
			//I think we needn't throw this error and exit the program.
			return;
		}
	}
	erase(pos,pos);
}

template<class T>
MyList<T> operator+ (const MyList<T> &l1, const MyList<T> &l2)
{
	MyList<T> newList=MyList<T>(l1);
	for (int i=0;i<l2.len;++i)
		newList.a[i+l1.len]=l2.a[i];
	newList.size=l1.size+l2.size;
	newList.len=l1.len+l2.len;
	return newList;
}

template<class T>
MyList<T> operator+ (const MyList<T> &l1, const T &item)
{
	MyList newList=MyList(l1);
	newList.push(item);
	return newList;
}

template<class T>
MyList<T> & MyList<T>::operator = (const MyList<T> &l)
{
	if (this==&l) return *this;

	delete [] a;
	a=new T[l.size];
	len=l.len;
	size=l.size;
	for (int i=0;i<len;++i)
		a[i]=l.a[i];
	
	return *this;
}
template<class T>
MyList<T> & MyList<T>::operator += (const T &item)//ͬpush(T item)
{
	this->push(item);
	return *this;
}

template<class T>
MyList<T> & MyList<T>::operator += (const MyList<T> &l)
{
	while (len+l.len>size) double_space();
	for (int i=0;i<l.len;++i)
	{
		a[len+i]=l.a[i];
	}
	len+=l.len;

	return *this;
}

template<class T>
T &MyList<T>::operator [](int index)
{
	if (index<0 || index>=len)
		throw errorIndex();
	else
		return a[index];
	
}

template<class T>
ostream &operator<<(ostream &os, const MyList<T> &obj)
{
	if (obj.len==0)
	{
		os<<"[]";
		return os;
	}
	os<<'[';
	for(int i=0;i<obj.len-1;++i)
		os<<obj.a[i]<<',';
	os<<obj.a[obj.len-1]<<']';
	return os;
}

template<class T>
void mySwap(T &a,T &b)
{
	T c=a;
	a=b;
	b=c;
}

template<class T>
int MyList<T>::partition(T* a,int low,int high)
{
	int key=a[low];
	while(low<high)
	{
		while(low<high && a[high]>=key) --high;
		mySwap(a[low],a[high]);
		while(low<high && a[low]<=key) ++low;
		mySwap(a[low],a[high]);
	}
	return low;
}

template<class T>
void MyList<T>::quickSort(T* a,int low,int high)
{

	if (low<high)
	{
		int med=partition(a,low,high);
		quickSort(a,low,med-1);
		quickSort(a,med+1,high);
	}
}

template<class T>
void MyList<T>::sort(bool less=true)
{
	quickSort(a,0,len-1);
	if (!less)
		this->reverse();
}

template<class T>
void MyList<T>::reverse()
{
	int i=0,j=len-1;
	while(i<j)
	{
		T temp=a[i];
		a[i++]=a[j];
		a[j--]=temp;
	}
}

