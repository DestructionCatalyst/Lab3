#include "Test.h"

using trees::NTree;
using trees::Node;



void TestNodes()
{
	Node<int>* n1 = new Node<int>(2, 1);
	Node<int>* n2 = new Node<int>(2, 3);
	n1->AddChild(n2);
	Node<int>* n3 = new Node<int>(2, 100);
	n1->AddChild(n3);
	Node<int>* n4 = new Node<int>(*n2);
	n3->AddChild(n4);

	bool test;
	test = n1->GetContent() == 1;
	test = test && n1->GetChild(0)->GetContent() == 3;
	test = test && n1->GetChild(1)->GetContent() == 100;
	test = test && n1->GetChild(1)->GetChild(0)->GetContent() == 3;

	if (test)
		std::cout << "Test 1 passed" << std::endl;
	else
		std::cout << "Test 1 failed" << std::endl;
}

void TestSmallTree()
{
	NTree<int> tree(2, 6);
	tree.Insert(6, 10);
	tree.Insert(10, 1);
	tree.Insert(6, 2);

	bool test;

	test = tree.Find(10)->GetChild(0)->GetContent() == 1;

	tree.Map(
		[](int a) -> int
		{
			return a * 2;
		}
	);

	test = test && tree.Find(20)->GetChild(0)->GetContent() == 2;
	test = test && tree.Find(12)->GetChild(1)->GetContent() == 4;

	int r = tree.Reduce(
		[](int a, int b) -> int
		{
			return a + b;
		}, trees::DepthFormat(2));

	test = test && r == 38;

	NTree<int> tree2 = *tree.GetSubTree(20);

	Node<int>* subTree = tree.FindSubTree(tree2);

	test = test && subTree->GetContent() == 20;
	test = test && subTree->GetChild(0)->GetContent() == 2;

	if (test)
		std::cout << "Test 2 passed" << std::endl;
	else
		std::cout << "Test 2 failed" << std::endl;
	
}

void TestBigTree()
{
	NTree<int> tree5 = trees::fromPairFile<int>("BigTree.txt", 4);

	unsigned long long start_time = clock();

	int prod = tree5.Reduce(
		[](int a, int b) -> int
		{
			return (a * b) % 10000007;
		}, trees::DepthFormat(4), 1);
	std::cout << prod << std::endl;

	int sum = 0;
	tree5.CustomMap(
		[&sum](int a)->int
		{
			return sum += a;
		}, trees::DepthFormat(4));


	sum = 0;
	tree5.CustomMap(
		[&sum](int a)->int
		{
			return sum += a;
		}, trees::WidthFormat(4));

	std::cout << tree5.Save(trees::WidthFormat(4)) << std::endl;

	

	unsigned long long end_time = clock();

	std::cout << "Execution time: " << static_cast<float>(end_time - start_time) / CLOCKS_PER_SEC << " s" << std::endl;
}

void TestDoubleTree()
{
	NTree<double> tree5 = trees::fromPairFile<double>("DoubleTree.txt", 4);

	unsigned long long start_time = clock();

	double prod = tree5.Reduce(
		[](double a, double b) -> double
		{
			return (a * b);
		}, trees::DepthFormat(4), 1);
	std::cout << prod << std::endl;

	double sum = 0;
	tree5.CustomMap(
		[&sum](double a)->double
		{
			return sum += a;
		}, trees::DepthFormat(4));


	sum = 0;
	tree5.CustomMap(
		[&sum](double a)->double
		{
			return sum += a;
		}, trees::WidthFormat(4));

	std::cout << tree5.Save(trees::WidthFormat(4)) << std::endl;



	unsigned long long end_time = clock();

	std::cout << "Execution time: " << static_cast<float>(end_time - start_time) / CLOCKS_PER_SEC << " s" << std::endl;
}