#include <iostream>
#include "Node.h"
#include "NTree.h"
#include "Parser.h"
#include "TreesFactory.h"



using namespace trees;
int main(){

	Node<int>* n1 = new Node<int>(2, 1);
	Node<int>* n2 = new Node<int>(2, 3);
	n1->AddChild(n2);
	Node<int>* n3 = new Node<int>(2, 100);
	n1->AddChild(n3);
	Node<int>* n4 = new Node<int>(*n2);
	n3->AddChild(n4);

	std::cout << n1->GetContent() << " " 
		<< n1->GetChild(0)->GetContent() << " "
		<< n1->GetChild(1)->GetContent() << " "
		<< n1->GetChild(1)->GetChild(0)->GetContent() << " " << std::endl;

	NTree<int> tree(4, 6);
	tree.Insert(6, 10);
	tree.Insert(10, 1);
	tree.Insert(6, 2);

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

	NTree<int> tree4("(20;12) (2;20) (4;12)", 2);

	NTree<int> tree5 = fromPairFile<int>("BigTree.txt", 4);
	//NTree<int> tree5("(4;21) (3;4) (2;3) (1;2) (5;4) (6;4) (7;6) (11;21) (16;21) (20;21)", 4);

	int sum = 0;
	tree5.CustomMap(
		[&sum](int a)->int
		{
			return sum += a;
		}, Depth(4));

	std::cout << tree5.Save(Width(4)) << std::endl;

	int prod = tree5.Reduce(
		[](int a, int b) -> int
		{
			return (a * b) % 10000007;
		}, Depth(4), 1);
	std::cout << prod << std::endl;

	return 0;
}