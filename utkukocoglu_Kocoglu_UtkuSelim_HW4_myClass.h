struct StackNode
{
	int row;
	int col;
	StackNode *next;
};

class DynIntStack
{
private:
	StackNode *top;

public:
	DynIntStack(void);
	void push(int num, int n);
	void pop(int & r, int & c);
	bool isEmpty(void);
};
