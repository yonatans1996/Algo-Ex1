#include "Queue.h"

Queue::Queue() : head(nullptr), tail(nullptr) {}

Queue::~Queue()
{
	MakeEmpty();
}

void Queue::MakeEmpty()
{
	QueueNode* currentNode = head;
	QueueNode* nextNode = nullptr;

	while (currentNode != nullptr)
	{
		nextNode = currentNode->next;
		delete currentNode;
		currentNode = nextNode;
	}
}


bool Queue::isEmpty()
{
	if (head == nullptr)
	{
		return true;
	}

	return false;
}

Vertex* Queue::front()
{
	if (head->data == nullptr)
	{
		return nullptr;
	}

	return head->data;
}

void Queue::EnQueue(Vertex* item)
{
	QueueNode* temp = new QueueNode(item);

	if (tail == nullptr)
	{
		head = tail = temp;
	}
	else
	{
		tail->next = temp;
		tail = temp;
	}
}

Vertex* Queue::DeQueue()
{
	if (isEmpty())
	{
		return nullptr;
	}
	
	QueueNode* queue_node_to_delete = head;
	Vertex* vertex_to_return = head->data;

	head = head->next;
	
	if (head == nullptr)
	{
		tail = nullptr;
	}

	queue_node_to_delete->next = nullptr;
	delete queue_node_to_delete;

	return vertex_to_return;
}