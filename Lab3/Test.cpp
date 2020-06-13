#include "Test.h"

using trees::NTree;
using trees::Node;
using Arithmetics::Complex;
using std::string;
using trees::Student;

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

	std::cout << std::endl;
}

void TestSmallTree()
{
	NTree<int> tree(3, 6);
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
		}, trees::DepthFormat(3));

	test = test && r == 38;

	NTree<int> tree2 = *tree.GetSubTree(20);

	Node<int>* subTree = tree.FindSubTree(tree2);

	test = test && subTree->GetContent() == 20;
	test = test && subTree->GetChild(0)->GetContent() == 2;

	tree.Insert(12, 1, 100);

	tree.DeleteChild(12, 0);
	
	test = test && tree.Root()->GetChild(0)->GetContent() == 100;
	test = test && tree.Root()->GetChild(1)->GetContent() == 4;

	if (test)
		std::cout << "Test 2 passed" << std::endl;
	else
		std::cout << "Test 2 failed" << std::endl;

	std::cout << std::endl;
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

	Node<int>* eight = tree5.FindFirst(
		[](int a)->bool
		{
			return a % 8 == 0;
		},trees::DepthFormat(4)
	);
	std::cout << eight->GetContent() << std::endl;

	std::vector<Node<int>*> even = tree5.FindAll(
		[](int a)->bool
		{
			return a % 2 == 0;
		}
	);

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

	std::cout << std::endl;
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

	std::cout << std::endl;
}

void TestComplexTree()
{
	NTree<Complex> tree5 = trees::fromPairFile<Complex>("ComplexTree.txt", 4);

	unsigned long long start_time = clock();

	Complex prod = tree5.Reduce(
		[](Complex a, Complex b) -> Complex
		{
			return (a * b);
		}, trees::DepthFormat(4), 1);
	std::cout << prod << std::endl;

	Complex sum = 0;
	tree5.CustomMap(
		[&sum](Complex a)->Complex
		{
			return sum = sum + a;
		}, trees::DepthFormat(4));


	sum = 0;
	tree5.CustomMap(
		[&sum](Complex a)->Complex
		{
			return sum = sum + a;
		}, trees::WidthFormat(4));

	std::cout << tree5.Save(trees::WidthFormat(4)) << std::endl;

	unsigned long long end_time = clock();

	std::cout << "Execution time: " << static_cast<float>(end_time - start_time) / CLOCKS_PER_SEC << " s" << std::endl;

	std::cout << std::endl;
}

void TestStringTree()
{
	NTree<std::string> tree5 = trees::fromPairFile<std::string>("StringTree.txt", 4);

	unsigned long long start_time = clock();

	std::string prod = tree5.Reduce(
		[](string a, string b) -> string
		{
			return a + " " + b;
		}, trees::DepthFormat(4), "");
	std::cout << prod << std::endl;

	
	tree5.CustomMap(
		[](string a)->string
		{
			char tmp = '\0';
			auto front = a.begin();
			auto back = a.end() - 1;

			for (;front < back; ++front, --back) {
				tmp = *front;
				*front = *back;
				*back = tmp;
				
			}
			return a;
		}, trees::DepthFormat(4));

	std::cout << tree5.Save(trees::WidthFormat(4)) << std::endl;

	unsigned long long end_time = clock();

	std::cout << "Execution time: " << static_cast<float>(end_time - start_time) / CLOCKS_PER_SEC << " s" << std::endl;

	std::cout << std::endl;
}

void TestStudentTree()
{
	NTree<Student> tree5 = trees::fromPairFile<Student>("StudentTree.txt", 4);

	unsigned long long start_time = clock();

	tree5.CustomMap(
		[](Student a)->Student
		{
			a.SetAge(a.GetAge() + 1);
			return a;
		}, trees::DepthFormat(4));

	trees::ID_t id = 6000000;
	Node<Student>* mary = tree5.FindFirst(
		[id](Student s) -> bool
		{
			return s.GetID() == id;
		}, trees::DepthFormat(4)
	);
	Student marriedMary = mary->GetContent();
	marriedMary.SetLastName("Ivanova");
	mary->SetContent(marriedMary);

	id = 8000000;

	Node<Student>* vasyan = tree5.FindFirst(
		[id](Student s) -> bool
		{
			return s.GetID() == id;
		}, trees::DepthFormat(4)
			);
	Student cyberVasyan = vasyan->GetContent();
	cyberVasyan.SetGroup("B19-504");
	vasyan->SetContent(cyberVasyan);
	

	std::cout << tree5.Save(trees::WidthFormat(4)) << std::endl;

	unsigned long long end_time = clock();

	std::cout << "Execution time: " << static_cast<float>(end_time - start_time) / CLOCKS_PER_SEC << " s" << std::endl;

	std::cout << std::endl;
}