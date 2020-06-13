#include <iostream>
#include "Node.h"
#include "NTree.h"
#include "Parser.h"
#include "Test.h"
#include "TreesFactory.h"



using namespace trees;
int main(){

	TestNodes();

	TestSmallTree();

	TestBigTree();

	TestDoubleTree();

	TestComplexTree();

	TestStringTree();

	TestStudentTree();

	return 0;
}