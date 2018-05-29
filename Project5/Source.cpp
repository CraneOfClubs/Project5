#include "Container.h"

int main() {
	Container<int> biba;
	biba.push_back(20);
	auto begin = biba.begin();
	int test = *begin;
}