#pragma once

struct Vertex
{
	int value;
	Vertex* next;

	Vertex(int value, Vertex* next = nullptr) :value(value), next(next) {}
};