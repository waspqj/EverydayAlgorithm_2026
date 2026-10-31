#include <stdio.h>
#include <string.h>


//1. 计算指针
//uint32_t * p;
//p = (uint32_t*)0x810000;
//
//p + 5 = 0x810014 ;

//2. 写出下列函数的输出
//uint32_t a = 20;
//
//printf("size=%u\n", sizeof(a++));
//
//printf("a=%d\n", a);

//2. 4
//	 a=21
//
//
//3. 写出下列函数的输出
//void fun(int p[]) {
//    printf("size=%u, %u\n", sizeof(p), sizeof(*p));
//}
//
//int a[] = { 20, 30, 40, 50 };
//fun(a)
//
// 3. 16 4 

//4. 写出下列函数的输出
//void fun(int* p) {
//    p++;
//    *p = 80;
//}
//
//int a[] = { 20, 30, 40, 50 };
//int* p = &a[1];
//printf("v=%d\n", *p);
//
//fun(p)
//printf("v=%d\n", *p);
// 
//for (int i = 0; i < 4; i++) {
//    printf("%d ", a[i]);
//}
//
//4. 30
//	 30
//   20 30 80 50

//5. 编写my_strcmp函数
int my_strcmp(const char* s1, const char* s2) 
{
	while (*s1 && *s2)
	{
		if (*s1 > *s2) return 1;
		else if (*s1 < *s2) return -1;
		s1++, s2++;
	}
	if (*s1) return 1;
	if (*s2) return -1;

	return 0;
}

//6. 写出链表插入 / 删除函数
struct Node {
	int data;
	struct Node* next;
};

struct Node* insert(struct Node* head, struct Node* new_node)
{
	new_node->next = head;
	head = new_node;
}

struct Node* delete(struct Node* head, struct Node* node)
{
	struct Node* pre = NULL, *cur = head;
	while (cur && cur != node)
	{
		pre = cur;
		cur = cur->next;
	}
	if(!pre)
		return head->next;
	pre->next = node->next;
	return head;
}


//7. 编写IP地址字符串到int的转换
uint32_t convert(const char* ip_addr)   // "192.168.2.1"  => 0xC0A80201, 0xC0 = 192, 0xA8 = 168
{
	uint8_t result[4] = { 0 };
	const char* p = ip_addr;
	for(int i = 0; i < 4; ++i)
	{
		while (*p != '.')
		{
			result[i] = result[i] * 10 + *p - '0';
			++p;
		}
	}

	return result[0] << 24 | result[1] << 16 | result[2] << 8 | result[3];
	
}