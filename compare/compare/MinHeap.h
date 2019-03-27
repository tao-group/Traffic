#pragma once
#include<iostream>
using namespace std;
//enum bool{true, false};
#define defaultSize 100
template<class T>
class MinHeap {
public:
	MinHeap(int sz = defaultSize);         //��С�ѵ�Ĭ�Ϲ��캯��
	MinHeap(T arr[], int sz);             //ͨ��һ�����鴴�����캯��
	~MinHeap();                            //��������
	bool insert(const T& x);              //��x���뵽��С����
	bool removeMin(T& x);                //ɾ����С������С��Ԫ�أ�������x��
	bool isEmpty();                       //�ж���С���Ƿ�Ϊ��
	bool isFull();                       //�ж���С���Ƿ���
	void makeEmpty();                     //����С���ÿ�
	void display();                      //�����С��
private:
	T* _heap;                              //��Ŷ���Ԫ�ص�����
	int _currentSize;                       //��С���е�ǰԪ�صĸ���
	int _maxHeapSize;                       //��С�����������ĸ���
	void shifDown(int start, int end);      //��start ��end�»�����Ϊ��С��
	void shifUp(int start);                //��start ��0�ϻ�����Ϊ��С��
};


//��С�ѵ�Ĭ�Ϲ��캯��
template<class T>
MinHeap<T>::MinHeap(int sz /*= defaultSize*/) {
	_maxHeapSize = (sz > defaultSize) ? sz : defaultSize;          //_maxHeapSizeΪ����sz��defaultSize�еĽϴ���
	_heap = new T[_maxHeapSize];                                   //Ϊ��Ŷ�Ԫ�ص���������ڴ�
	if (_heap == nullptr) {                                        //�ڴ����ʧ��
		cerr << "�ڴ�������" << endl;
		exit(-1);
	}
	_currentSize = 0;                                             //��ǰ��Ԫ������Ϊ0
}

//ͨ��һ�����鴴�����캯��
template<class T>
MinHeap<T>::MinHeap(T arr[], int sz) {
	_maxHeapSize = (sz > defaultSize) ? sz : defaultSize;          //_maxHeapSizeΪ����sz��defaultSize�еĽϴ���
	_heap = new T[_maxHeapSize];                                   //Ϊ��Ŷ�Ԫ�ص���������ڴ�
	if (_heap == nullptr) {                                        //�ڴ����ʧ��
		cerr << "�ڴ�������" << endl;
		exit(-1);
	}

	for (int i = 0; i < sz; i++)                                     //�����������е�Ԫ��һһ��ֵ����Ԫ��
		_heap[i] = arr[i];
	_currentSize = sz;                                             //Ϊ��Ԫ��������ֵ���Ͳ��������С��ͬ

	int currentPos = (_currentSize - 2) / 2;                       //��ʱ������ָ�����һ����Ҷ�ڵ�Ķ�
	while (currentPos >= 0) {
		shifDown(currentPos, _currentSize - 1);                    //�Ե�����(���������Ѷ���)-���϶���(���ھֲ��Ѷ���)����Ϊ��
		currentPos--;
	}
}


//��start ��end�»�����Ϊ��С��
template<class T>
void MinHeap<T>::shifDown(int start, int end) {
	//˽�к������ӽ��start��ʼ����endΪֹ���������±Ƚϣ����
	//��Ů��ֵС�ڸ��ڵ��ֵ����ؼ���С��ֵ�ϸ����������²�Ƚ�
	//������һ�����Ͼֲ�����Ϊ��С��
	int i = start;
	int j = 2 * i + 1;                             //ָ��i������
	T tempValue = _heap[i];                        //��ʱ�����±�Ϊstart����ֵ
	while (j <= end) {                             //δ�ﵽend������㣬һֱѭ��
		if (j < end && _heap[j] > _heap[j + 1])    //������ҽ�㣬�����ҽ��С������
			j++;                                    //j��ָ���ҽ��
		if (tempValue <= _heap[j])                 //������ڵ�С�ڵ������ҽ�㣬��ֱ�ӽ�����һ��ѭ��
			break;
		else {
			_heap[i] = _heap[j];                     //�����ӽ���ֵ��ֵ�����ڵ�
			i = j;                                   //ʹiָ���ӽڵ�
			j = 2 * i + 1;                           //jָ��i���ӽ��
		}
	}
	_heap[i] = tempValue;                            //�ط�
}


//��start ��end�ϻ�����Ϊ��С��
template<class T>
void MinHeap<T>::shifUp(int start) {
	//˽�к������ӽ��start��ʼ�����0Ϊֹ���������ϱȽ�
	//�����Ů��ֵС�ڸ��ڵ��ֵ�����໥����
	//�������������µ���Ϊ��С��
	int j = start;
	int i = (j - 2) / 2;                          //��iָ��j�ĸ��ڵ�
	T tempValue = _heap[j];                       //tempValue�ݴ�_heap[j]��ֵ
	while (j > 0) {                               //��δ�ﵽ���ڵ�֮ǰ��һֱѭ��
		if (tempValue >= _heap[i])                //����ӽ����ڵ��ڸ��ڵ��ֱ�ӽ�����һ��ѭ��
			break;
		else {
			_heap[i] = _heap[j];
			j = i;                                //jָ��ǰ�ĸ��ڵ�
			i = (j - 2) / 2;                      //iָ��j�ĸ��ڵ�
		}
	}
	_heap[j] = tempValue;                         //�ط�
}

//��������
template<class T>
MinHeap<T>::~MinHeap() {
	if (_heap != nullptr)
		delete _heap;
}

//����������x���뵽��С����
template<class T>
bool MinHeap<T>::insert(const T& x) {
	if (isFull())                                           //����������Ͳ��ܽ��в���
		return false;
	_heap[_currentSize] = x;                               //��������ֵ���µĶ�Ԫ��
	shifUp(_currentSize);                                  //����shifUp����������С�ѵ���
	_currentSize++;                                        //��������������һ
	return true;
}

//ɾ����С������С��Ԫ�أ�������x��
template<class T>
bool MinHeap<T>::removeMin(T& x) {
	if (isEmpty())                                         //����ѿ�,�Ͳ��ܽ���ɾ��
		return false;
	x = _heap[0];                                         //�Ѷ�Ԫ�ظ�ֵ�����ز���x
	_heap[0] = _heap[_currentSize - 1];                   //�����һ��Ԫ�ظ�ֵ���Ѷ�Ԫ��
	_currentSize--;                                     //���������Լ���һ
	shifDown(0, _currentSize - 1);                        //����shifDown����������С�ѵ���  
	return true;
}

//�ж���С���Ƿ�Ϊ��
template<class T>
bool  MinHeap<T>::isEmpty() {
	return _currentSize == 0;
}

//�ж���С���Ƿ��� 
template<class T>
bool  MinHeap<T>::isFull() {
	return _currentSize == _maxHeapSize;
}

//����С���ÿ�
template<class T>
void  MinHeap<T>::makeEmpty() {
	if (!isEmpty()) {                             //�����Ϊ��
		delete _heap;
		_currentSize = 0;
	}
}

//�����С��
template<class T>
void MinHeap<T>::display() {
	for (int i = 0; i < _currentSize; i++)
		cout << _heap[i] << " ";
	cout << endl;
}