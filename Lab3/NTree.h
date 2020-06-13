#pragma once
#include "Node.h"
#include "Parser.h"
#include "Format.h"
#include <functional>
#include <vector>
#include <sstream>
#include <fstream>
#define Zero T()

namespace trees {

	template<class T> class NTree {
	private:
		Node<T>* root;
		int n;
	public:
		//Tree with default root
		NTree(int num):
			n(num)
		{
			root = new Node<T>(n);
		}
		//Tree with 'content' root
		NTree(int num, T content) :
			NTree(num)
		{
			root->SetContent(content);
		}
		//Tree from existing node (can be with children)
		NTree(Node<T>* node) :
			n(node->GetCapacity())
		{
			root = node;
		}
		//Tree from list string
		NTree(std::string str, int num, std::string format):
			n(num)
		{
			std::vector<int> index = parse_list<T>(format);
		
			root = new Node<T>(str, num, index);
		}
		//Tree from pair string
		NTree(std::string str, int num):
			n(num)
		{
			std::vector<std::pair<T, T>> pairs = parse_pairs<T>(str);

			root = new Node<T>(n, find_root<T>(pairs), pairs);
		}

	public:
		Node<T>* Root()
		{
			return root;
		}
		Node<T>* Find(T value)
		{
			return root->Find(value);
		}
		Node<T>* FindFirst(std::function<bool(T)> p, std::string format)
		{
			const std::vector<int> index = parse_list<int>(format);

			return root->FindFirst(p, index);
		}
		std::vector<Node<T>*> FindAll(std::function<bool(T)> p)
		{
			std::vector<Node<T>*> res;

			root->FindAll(p, res);

			return res;
		}
	private:
		//UNSAFE!
		bool InsertUnsafe(T place, int num, T content)
		{
			Node<T>* placePtr = Find(place);
			if (placePtr == nullptr)
				return false;
			else {
				Node<T>* tmp = placePtr->GetChild(num);
				Node<T>* newNode = new Node<T>(n, content);
				placePtr->SetChild(num, newNode);
				newNode->SetChild(0, tmp);
				return true;
			}
		}
	public:
		//Inserts the child and shifts the next ones
		bool Insert(T place, int num, T content)
		{
			Node<T>* existing = Find(content);
			if (existing == nullptr) {
				Node<T>* placePtr = Find(place);
				if (placePtr == nullptr)
					return false;
				else if (placePtr->GetChildCount() == placePtr->GetCapacity())
					return false;
				else {
					for (int i = placePtr->GetChildCount() - 1; i >= num; i--) {
						placePtr->SetChild(i + 1, placePtr->GetChild(i));
					}
					placePtr->SetChild(num, new Node<T>(n, content));
					return true;
				}
			}
			else
				return false;
		}

	
		//Inserts at 1st free place, if there isn't, returns false
		bool Insert(T place, T content)
		{
			Node<T>* existing = Find(content);
			if (existing == nullptr) {
				
				Node<T>* placePtr = Find(place);
					
				if (placePtr == nullptr)
					return false;
				else {
					placePtr->AddChild(content);
					return true;
				}
				
			}
			else
				return false;
		}
		bool DeleteChild(T item, int num)
		{
			Node<T>* placePtr = Find(item);
			if (placePtr == nullptr)
				return false;
			else {
				placePtr->DeleteChild(num);
				for (int i = num; i < placePtr->GetChildCount(); i++) {
					placePtr->SetChild(i , placePtr->GetChild(i + 1));
				}
				placePtr->SetChild(placePtr->GetChildCount(), nullptr);
				return true;
			}
		}
		//For functions where order does not matter
		void Map(std::function<T(T)> f)
		{
			root->Map(f);
		}
		void CustomMap(std::function<T(T)> f, std::string format)
		{
			std::vector<int> index = parse_list<int>(format);

			root->CustomMap(f, index);
		}
		T Reduce(std::function<T(T, T)> f, std::string format, T acc = T())
		{
			const std::vector<int> index = parse_list<int>(format);

			return root->Reduce(f, index, acc);
		}
		NTree<T>* GetSubTree(T item)
		{
			Node<T>* placePtr = Find(item);
			if (placePtr == nullptr)
				return nullptr;
			else {
				Node<T>* newRoot = GetSubTreeHelper(placePtr);
				
				return new NTree(newRoot);
			}
		}
	private:
		Node<T>* GetSubTreeHelper(Node<T>* place)
		{
			Node<T>* cur;
			Node<T>* res = new Node<T>(*place);
			for (int i = 0; i < n; i++) {
				cur = place->GetChild(i);
				if (cur != nullptr) {
					res->SetChild(i, GetSubTreeHelper(cur));
				}
			}
			return res;
		}
	public:
		Node<T>* FindSubTree(NTree<T> sub) {
			Node<T>* placePtr = Find(sub.root->GetContent());
			if (placePtr->CheckSubTree(sub.root)) {
				return placePtr;
			}
			else
				return nullptr;
		}

		std::string Save(std::string format)
		{

			std::stringstream ss;

			std::vector<int> index = parse_list<int>(format);
			root->Save(&ss, index);

			return ss.str();
		}
		void SaveToFile(std::string path, std::string format)
		{
			std::ofstream ofs(path);

			if (ofs) {
				ofs << Save(format) << std::endl;
				ofs.close();
			}
			else
				throw std::runtime_error("Error writing to file!");
		}
		std::string SavePairs()
		{
			std::stringstream ss;

			root->SavePairs(&ss);

			return ss.str();
		}
		
		void SavePairsToFile(std::string path)
		{
			std::ofstream ofs(path);

			if (ofs) {
				ofs << SavePairs() << std::endl;
				ofs.close();
			}
			else
				throw std::runtime_error("Error writing to file!");
		}

	};


}