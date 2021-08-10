#include "Vertex.h"
using namespace std;

struct QueueNode {
	Vertex* data;
	QueueNode* next;
	
	QueueNode(Vertex* _data)
	{
		data = _data;
		next = nullptr;
	}

	~QueueNode()
	{
		
	
	}

};

class Queue {
	
	private:
		QueueNode* head, * tail;

	public:
		Queue();
		~Queue();

		void MakeEmpty();
		bool isEmpty();
		Vertex* front();
		void EnQueue(Vertex* item);
		Vertex* DeQueue();
};
