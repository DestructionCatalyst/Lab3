#pragma once
#include <memory>
#include <stdexcept>
#include <cstdlib>
#include <functional>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include "Parser.h"

namespace trees {
	template <class T> class Node {
	private:
		int capacity;
		int childCount;
		Node** mChildren;
		T mContent;
	public:
		Node(int child_num) :
			capacity(child_num),
			childCount(0),
			mContent()
		{
			if (capacity <= 0)
				throw std::invalid_argument("Child number can't be 0 or less!");
			mChildren = static_cast<Node**>(malloc(sizeof(Node*) * capacity));
			for (int i = 0; i < capacity; i++) {
				mChildren[i] = nullptr;
			}
		}
		Node(int child_num, T content) :
			Node(child_num)
		{
			mContent = content;
		}
		Node(Node<T>& node) :
			Node(node.capacity, node.mContent)
		{

			childCount = node.childCount;
			for (int i = 0; i < capacity; i++)
				mChildren[i] = node.GetChild(i);

		}
		Node(std::string str, int num, std::vector<int>& ind):
			Node(num)
		{
			std::vector<std::string> str_nodes = split_to_nodes(str);
			
			int trueIndex;

			if (str_nodes.size() == capacity + 1) {
				for (int i = 0; i < capacity; i++) {
					trueIndex = ind[i] - 1;
					if (str_nodes[i] == "#")
						SetChild(trueIndex, nullptr);
					else if (str_nodes[i].starts_with("("))
						SetChild(trueIndex, new Node<T>(str_nodes[i], num, ind)),
						childCount++;
					else if (ind[i] == 0)
						SetContent(parse<T>(str_nodes[i]));
					else 
						throw std::invalid_argument("String format exception!");
				}
			}
			else
				throw std::invalid_argument("Node is not the right size!");
		}
		Node(int n, T content, std::vector<std::pair<T, T>>& pairs):
			Node(n, content)
		{
			auto iter = pairs.begin();
			for (int i = 0; i < pairs.size(); i++) {

				if (iter->second == content) {
					T childRoot = iter->first;
					AddChild(new Node<T>(n, childRoot, pairs));
					if (childCount == capacity)
						break;
				}
				++iter;
			}
		}
		
	public:
		T GetContent()
		{
			return mContent;
		}
		void SetContent(T content)
		{
			mContent = content;
		}
		Node<T>* GetChild(int num)
		{
			if ((num < 0) || (num >= capacity))
				throw std::out_of_range("Child index is out of bounds!");
			else
				return mChildren[num];
		}
		//Re-initialize existing children
		void SetChild(int num, Node<T>* node)
		{
			if ((num < 0) || (num > childCount) || (num >= capacity))
				throw std::out_of_range("Child index is out of bounds!");
			else 
				mChildren[num] = node;

			if (num == childCount)
				childCount++;
		}
		//Add new children
		void AddChild(Node<T>* node)
		{
			SetChild(childCount, node);
		}
		//Add new children
		void AddChild(T content)
		{
			SetChild(childCount, new Node(capacity, content));
		}
		int GetCapacity() {
			return capacity;
		}
		int GetChildCount() {
			return childCount;
		}
	public:
		Node<T>* Find(T value) {
			if (GetContent() == value)
				return this;
			for (int i = 0; i < capacity; i++) {
				if (GetChild(i) != nullptr)
					return GetChild(i)->Find(value);
			}
			return nullptr;
		}

		void DeleteChild(int num) {
			Node<T>* childPtr = GetChild(num);
			Node<T>* grandchildPtr;
			for (int i = 0; i < capacity; i++) {
				grandchildPtr = GetChild(i);
				if (grandchildPtr != nullptr) {
					childPtr->DeleteChild(num);
				}
			}		
			delete (childPtr);
			SetChild(num, nullptr);
		}
		//For functions where order does not matter
		void Map(std::function<T(T)> f) {
			for (int i = 0; i < capacity; i++) {
				if (GetChild(i) != nullptr)
					GetChild(i)->Map(f);
			}
			SetContent(f(GetContent()));
		}
		void CustomMap(std::function<T(T)> f, std::vector<int>& ind)
		{
			int trueIndex;
			for (int i = 0; i < ind.size(); i++) {
				trueIndex = ind[i] - 1;
				if (trueIndex < 0) 
					SetContent(f(GetContent()));
				else if (GetChild(trueIndex) != nullptr)
					GetChild(trueIndex)->CustomMap(f, ind);
			}
		}
		T Reduce(std::function<T(T, T)> f, const std::vector<int>& ind, T acc)
		{
			int trueIndex;
			
			for (int i = 0; i < ind.size(); i++) {
				trueIndex = ind[i] - 1;
				if (trueIndex < 0) {
					acc = f(GetContent(), acc);
					
				}
				else if ((GetChild(trueIndex) != nullptr)) {
					acc = GetChild(trueIndex)->Reduce(f, ind, acc);
					
				}
			}
			return acc;
		}
		bool CheckSubTree(Node<T>* sub) {
			
			bool res = true;
			Node<T>* thisChild;
			Node<T>* subChild;
			for (int i = 0; i < capacity; i++) {
				thisChild = this->GetChild(i);
				subChild = sub->GetChild(i);
				if ((thisChild == subChild) || (thisChild->GetContent() == subChild->GetContent())) {
					if (subChild != nullptr) {
						res = res && thisChild->CheckSubTree(subChild);
					}
				}
				else
					res = false;
			}
			return res;

		}
		void Save(std::stringstream* ss, std::vector<int>& ind)
		{
			int trueIndex;
			*ss << "( ";
			for (int i = 0; i < ind.size(); i++) {
				trueIndex = ind[i] - 1;
				if (trueIndex < 0)
					*ss << GetContent() << " ";
				else {
					if (GetChild(trueIndex) != nullptr)
						GetChild(trueIndex)->Save(ss, ind);
					else
						*ss << "#" << " ";
				}
			}
			*ss << ") ";
		}
		void SavePairs(std::stringstream* ss) {
			for (int i = 0; i < capacity; i++) {
				if (GetChild(i) != nullptr) {
					*ss << "(" << GetChild(i)->GetContent() << ";" << GetContent() << ") ";
					GetChild(i)->SavePairs(ss);
				}
			}
		}
		void SubTreeFromPairs(std::vector<std::pair<T, T>>& pairs) {
			
			for (int i = 0; i < pairs.size(); i++) {
				
			}
		}

		private:
		//DEBUG
		void PrintChildren() {
			for (int i = 0; i < capacity; i++) {
				std::cout << GetChild(i);
			}
			std::cout << std::endl;
		}
	};
}