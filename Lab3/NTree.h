#pragma once
#include "Node.h"
#include "Parser.h"
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
			std::vector<int> index = parse<T>(format);
		
			root = new Node<T>(str, num, index);
		}
		//Tree from pair string
		NTree(std::string str, int num):
			n(num)
		{
			std::vector<std::pair<T, T>> pairs = parse_pairs<int>(str);

			root = new Node<T>(n, find_root<int>(pairs), pairs);
		}

	public:
		Node<T>* Find(T value)
		{
			return root->Find(value);
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
		//UNSAFE
		bool Insert(T place, int num, T content)
		{
			Node<T>* existing = Find(content);
			if (existing == nullptr) {
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
			else
				return false;
		}
	public:
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
					/*
					for (int i = 0; i < n; i++) {
						Node<T>* tmp = placePtr->GetChild(i);
						if (tmp == nullptr) {
							Node<T>* newNode = new Node<T>(n, content);
							placePtr->SetChild(i, newNode);
							return true;
						}
					}
					return false;
					*/
				}
				
			}
			else
				return false;
		}
		bool DeleteChild(T item, int num)
		{
			--num;
			Node<T>* placePtr = Find(item);
			if (placePtr == nullptr)
				return false;
			else {
				placePtr->DeleteChild(num);
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
			std::vector<int> index = parse<T>(format);

			root->CustomMap(f, index);
		}
		T Reduce(std::function<T(T, T)> f, std::string format, T acc = T())
		{
			const std::vector<int> index = parse<T>(format);

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

			std::vector<int> index = parse<T>(format);
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