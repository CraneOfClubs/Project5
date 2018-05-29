#pragma once
#include <iostream>



template <typename T> class Container {
public:
	template <typename T>
	class Node;
	template
		<class Type, class UnqualifiedType = std::remove_cv_t<Type>>
		class ForwardIterator: public std::iterator<std::forward_iterator_tag, UnqualifiedType, std::ptrdiff_t, Type*, Type&> {
		Node<UnqualifiedType>* itr;

	public:

		explicit ForwardIterator(Node<UnqualifiedType>* nd) : itr(nd)
		{
		}

		ForwardIterator(): itr(nullptr)
		{
		}

		void swap(ForwardIterator& other) noexcept
		{
			using std::swap;
			swap(itr, other.iter);
		}

		ForwardIterator& operator++ () // Pre-increment
		{
			if (itr == nullptr) {
				throw std::runtime_error("Out-of-bounds iterator increment!");
			}
			itr = itr->next;
			return *this;
		}

		ForwardIterator operator++ (int) // Post-increment
		{
			if (itr == nullptr) {
				throw std::runtime_error("Out-of-bounds iterator increment!");
			}
			ForwardIterator tmp(*this);
			itr = itr->next;
			return tmp;
		}

		template<class OtherType>
		bool operator == (const ForwardIterator<OtherType>& rhs) const
		{
			return itr == rhs.itr;
		}

		template<class OtherType>
		bool operator != (const ForwardIterator<OtherType>& rhs) const
		{
			return itr != rhs.itr;
		}

		Type& operator* () const
		{
			if (itr == nullptr) {
				throw std::runtime_error("Invalid iterator dereference!");
			}
			return itr->_value;
		}

		Type& operator-> () const
		{
			if (itr == nullptr) {
				throw std::runtime_error("Invalid iterator dereference!");
			}
			return itr->_value;
		}

		// One way conversion: iterator -> const_iterator
		operator ForwardIterator<const Type>() const
		{
			return ForwardIterator<const Type>(itr);
		}
	};

	typedef ForwardIterator<T> iterator;
	typedef ForwardIterator<const T> const_iterator;


	Container() {
		this->m_first = nullptr;
		this->m_last = nullptr;
		this->m_size = 0;
	}

	Container(const Container &a) {
		this->m_first = a.m_first;
		this->m_last = a.m_last;
		this->m_size = a.m_last;
	}

	template <typename T> void push_back(T elem) {
		if (this->isEmpty()) {
			addFirstElement(elem);
		}
		else {
			Node<T> *newNode = new Node<T>(elem, nullptr, this->m_last);
			this->m_last->next = newNode;
			this->m_last = newNode;
		}
		this->m_size++;
	}

	template <typename T> void push_front(T elem) {
		if (this->isEmpty()) {
			addFirstElement(elem);
		}
		else {
			Node *newNode = new Node(elem, this->m_first, nullptr);
			this->m_first->prev = newNode;
			this->m_first = newNode;
		}
		this->m_size++;
	}

	template <typename T> void pop_back() {
		if (this->isEmpty())
			return;

		Node *nodeToKill = this->m_last;

		if (this->m_size == 1) {
			delete nodeToKill;
			this->m_size = 0;
			return;
		}

		this->m_last->prev->next = nullptr;
		this->m_last = this->m_last->prev;
		delete nodeToKill;
	}

	template <typename T> void pop_front() {
		if (this->isEmpty())
			return;

		Node *nodeToKill = this->m_first;

		if (this->m_size == 1) {
			delete nodeToKill; //nodeToKill->~Node();?? Серьезно?
			this->m_size = 0;
			return;
		}

		this->m_first->next->prev = nullptr;
		this->m_first = this->m_first->next;
		delete nodeToKill;
	}

	const size_t size() { return this->m_size; }

	const bool isEmpty() { return this->m_size == 0; }

	void clear() {
		int a = 1;
		iterator it;
		for (it = this->begin(); it != this->end(); it++) {
		}
	}

	template <typename T>
	class Node {
	public:
		T _value;
		Node *next;
		Node *prev;
		Node(const T val) {
			this->_value = val;
			this->next = nullptr;
			this->prev = nullptr;
		}

		Node(const T val, Node *next, Node *prev) {
			this->_value = val;
			this->next = next;
			this->prev = prev;
		}

		Node(const Node &a) {
			this->_value = a._value;
			this->next = a.next;
			this->prev = a.prev;
		}

		~Node() {}
	};

	iterator begin() {
		auto iter = iterator(m_first);
		return iter;
	}


private:
	template <typename T> void addFirstElement(T elem) {
		Node<T> *newNode = new Node<T>(elem, nullptr, nullptr);
		this->m_first = newNode;
		this->m_last = newNode;
	}

	Node<T> *m_first;
	Node<T> *m_last;
	std::size_t m_size = 0;
};