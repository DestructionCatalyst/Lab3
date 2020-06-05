#include <iostream>
#include "Node.h"
#include "NTree.h"
#include "Parser.h"

using namespace trees;
int main(){

	Node<int>* n1 = new Node<int>(2, 1);
	Node<int>* n2 = new Node<int>(2, 3);
	n1->SetChild(0, n2);
	Node<int>* n3 = new Node<int>(2, 100);
	n1->SetChild(1, n3);
	Node<int>* n4 = new Node<int>(*n2);
	n3->SetChild(0, n4);

	std::cout << n1->GetContent() << " " << n1->GetChild(0)->GetContent() << " " << n1->GetChild(1)->GetContent() <<
		" " << n1->GetChild(1)->GetChild(0)->GetContent() << " " << std::endl;

	NTree<int> tree(4, 6);
	tree.Insert(6, 0, 1);
	tree.Insert(6, 1, 2);
	tree.Insert(6, 0, 10);

	//( ( ( # 2 # # # ) 20 # # # ) 12 ( # 4 # # # ) # # ) 
	//	12
	//20 4 # # 
	//2

	std::cout << tree.Find(10)->GetChild(0)->GetContent() << " " << tree.Find(100) << std::endl;

	std::string str = " 0 1 3 10 777   7, 8  0  098 0";
	std::vector<int> v = parse<int>(str);
	
	tree.Map(
		[](int a) -> int
		{
			return a * 2;
		}
	);
	std::cout << tree.Find(20)->GetChild(0)->GetContent() << " " << tree.Find(12)->GetContent() << std::endl;
	//tree.Delete(10);

	int r = tree.Reduce(
		[](int a, int b) -> int
		{
			return a + b;
		}, "1 2 3 4 0");

	std::cout << r << std::endl;

	NTree<int> tree2 = *tree.GetSubTree(20);

	Node<int>* subTree = tree.FindSubTree(tree2);

	std::cout << tree.Save("1 0 2 3 4") << std::endl;

	tree.SaveToFile("SampleTree.txt", "1 0 2 3 4");

	//tree.DeleteChild(12, 1);

	NTree<int> tree3("( ( ( # 2 # # # ) 20 # # # ) 12 ( # 4 # # # ) # # ) ", 4, "1 0 2 3 4");

	std::cout << tree3.Save("1 0 2 3 4") << std::endl;

	std::cout << tree.SavePairs() << std::endl;

	return 0;
}