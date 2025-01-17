#ifndef BST_EVAN
#define BST_EVAN

#include <functional>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <queue>

	using std::cout;
	using std::endl;

	using std::to_string;

	struct ValueNotFoundError : std::runtime_error
	{
		using std::runtime_error::runtime_error;
	};
	struct ValueExistsError : std::runtime_error
	{
		using std::runtime_error::runtime_error;
	};

	template <class T>
	class BST
	{
	public:

		class Node
		{
		public:


			Node();
			Node(const Node& other);

			~Node();

			T& getData();
			void setData(T data);

			size_t getDepth() const;
			void setDepth(size_t depth);

			void setParent(std::shared_ptr<Node> p);
			std::shared_ptr<Node> getParent() const;

			void setLeftChild(std::shared_ptr<Node> lc);
			std::shared_ptr<Node> getLeftChild() const;

			void setRightChild(std::shared_ptr<Node> rc);
			std::shared_ptr<Node> getRightChild() const;

			void clear();

			T& operator*();
			bool operator==(const Node& other);
			bool operator!=(const Node& other);

		private:

			T data_;
			size_t depth_ = 0;

			std::shared_ptr<Node>
				parent_,
				left_child_,
				right_child_
				;

			friend class BST;
		};

		BST();
		BST(const BST& other);

		~BST();

		void insert(T value);
		T& find(T value);
		std::shared_ptr<Node> find_node(T value) const;
		void remove(T value);
		void remove(std::shared_ptr<Node> node);
		bool exists(T value) const;
		std::shared_ptr<Node> getRoot() const;

		bool isRoot(const std::shared_ptr<Node>& node) const;
		bool isInternal(const std::shared_ptr<Node>& node) const;
		bool isExternal(const std::shared_ptr<Node>& node) const;
		bool isLeaf(const std::shared_ptr<Node>& node) const;

		bool isParent(const std::shared_ptr<Node>& node) const;
		bool hasParent(const std::shared_ptr<Node>& node) const;

		size_t getChildCount(const std::shared_ptr<Node>& node) const;
		bool hasOneChild(const std::shared_ptr<Node>& node) const;
		bool hasTwoChildren(const std::shared_ptr<Node>& node) const;

		bool isLeftChild(const std::shared_ptr<Node>& node) const;
		bool hasLeftChild(const std::shared_ptr<Node>& node) const;
		bool isRightChild(const std::shared_ptr<Node>& node) const;
		bool hasRightChild(const std::shared_ptr<Node>& node) const;

		void traversePreOrder(std::function<bool(BST&, std::shared_ptr<Node>)> callback);
		void traverseInOrder(std::function<bool(const BST&, std::shared_ptr<Node>)> callback) const;
		void traverseInOrder(std::function<bool(BST&, std::shared_ptr<Node>)> callback);
		void traversePostOrder(std::function<bool(BST&, std::shared_ptr<Node>)> callback);
		void traverseLevelOrder(std::function<bool(const BST&, std::shared_ptr<Node>)> callback) const;
		void traverseLevelOrder(std::function<bool(BST&, std::shared_ptr<Node>)> callback);

		std::pair<std::shared_ptr<Node>, std::shared_ptr<Node>> GULocator(T value) const;
		void clear();
		bool empty() const;
		size_t size() const;
		std::shared_ptr<Node> getDeepestLeaf();
		size_t computeHeight();

		bool operator==(const BST<T>& other);
		bool operator!=(const BST<T>& other);
		BST& operator=(const BST<T>& other);

	private:

		void traverseLevelOrder
		(
			std::shared_ptr<Node> node,
			std::function<bool(const BST&, std::shared_ptr<Node>)> callback
		) const;

		void traverseLevelOrder
		(
			std::shared_ptr<Node> node,
			std::function<bool(BST&, std::shared_ptr<Node>)> callback
		);

		std::shared_ptr<Node> root_;
		size_t size_ = 0;

		friend class Tester;
	};

	template <class T>
	BST<T>::Node::Node() : data_{},
		depth_{ 0 },
		parent_{ nullptr },
		left_child_{ nullptr },
		right_child_{ nullptr } {
	}

	template <class T>
	BST<T>::Node::Node(const BST<T>::Node& other) : data_(other.data_),
		depth_(other.depth_),
		parent_(other.parent_),
		left_child_(other.left_child_),
		right_child_(other.right_child_) {
	}

	template <class T>
	BST<T>::Node::~Node()
	{
		clear();
	}

	template <class T>
	T& BST<T>::Node::getData()
	{
		return data_;
	}

	template <class T>
	void BST<T>::Node::setData(T data)
	{
		data_ = data;
	}

	template <class T>
	size_t BST<T>::Node::getDepth() const
	{
		return depth_;
	}

	template <class T>
	void BST<T>::Node::setDepth(size_t depth)
	{
		depth_ = depth;
	}

	template <class T>
	void BST<T>::Node::setParent(std::shared_ptr<BST<T>::Node> p)
	{
		parent_ = p;
	}

	template <class T>
	std::shared_ptr<class BST<T>::Node::Node> BST<T>::Node::getParent() const
	{
		return parent_;
	}

	template <class T>
	void BST<T>::Node::setLeftChild(std::shared_ptr<BST<T>::Node> lc)
	{
		left_child_ = lc;
	}

	template <class T>
	std::shared_ptr<class BST<T>::Node> BST<T>::Node::getLeftChild() const
	{
		return left_child_;
	}

	template <class T>
	void BST<T>::Node::setRightChild(std::shared_ptr<BST<T>::Node> rc)
	{
		right_child_ = rc;
	}

	template <class T>
	std::shared_ptr<class BST<T>::Node::Node> BST<T>::Node::getRightChild() const
	{
		return right_child_;
	}

	template <class T>
	void BST<T>::Node::clear()
	{
		parent_.reset();
		left_child_.reset();
		right_child_.reset();
	}

	template <class T>
	T& BST<T>::Node::operator*()
	{
		return data_;
	}

	template <class T>
	bool BST<T>::Node::operator==(const Node& other)
	{
		if (data_ == other.data_) {
			return true;
		}
		else {
			return false;
		}
	}

	template <class T>
	bool BST<T>::Node::operator!=(const Node& other)
	{
		return !(*this == other);
	}

	template <class T>
	BST<T>::BST() : root_(nullptr),
		size_(0)
	{}

	template <class T>
	BST<T>::BST(const BST& other)
	{
		if (other.empty()) {
			root_ = nullptr;
			size_ = 0;
			return;
		}

		other.traverseLevelOrder(other.getRoot(), [&](const BST<T>&,
			std::shared_ptr<Node> node) {
				this->insert(node->getData());
				return true;
			}
		);
	}

	template <class T>
	BST<T>::~BST()
	{
		clear();
	}

	template <class T>
	void BST<T>::insert(T value)
	{

		if (!root_) {
			root_ = std::make_shared<Node>();
			root_->setData(value);
			root_->setDepth(0);
			size_++;
			return;
		}

		auto root1 = root_;
		while (true) {
			if (value == root1->getData()) {
				throw ValueExistsError("VERROR check");
			}
			else if (value < root1->getData()) {

				if (root1->getLeftChild()) {
					root1 = root1->getLeftChild();
				}
				else {
					auto LorR1 = std::make_shared<Node>();
					LorR1->setData(value);
					LorR1->setParent(root1);
					LorR1->setDepth(root1->getDepth() + 1);
					root1->setLeftChild(LorR1);
					size_++;
					return;
				}
			}
			else {

				if (root1->getRightChild()) {
					root1 = root1->getRightChild();
				}
				else {
					auto LorR1 = std::make_shared<Node>();
					LorR1->setData(value);
					LorR1->setParent(root1);
					LorR1->setDepth(root1->getDepth() + 1);
					root1->setRightChild(LorR1);
					size_++;
					return;
				}
			}
		}
	}

	template <class T>
	std::pair<std::shared_ptr<typename BST<T>::Node>,
		std::shared_ptr<typename BST<T>::Node>>
		BST<T>::GULocator(T value) const
	{
		auto gotroot = root_;
		std::shared_ptr<Node> parent = nullptr;
		while (gotroot && gotroot->getData() != value) {
			parent = gotroot;
			if (value < gotroot->getData()) {
				gotroot = gotroot->getLeftChild();
			}
			else {
				gotroot = gotroot->getRightChild();
			}
		}
		return { gotroot, parent };
	}

	template <class T>
	T& BST<T>::find(T value)
	{
		auto [node, parent] = GULocator(value);

		if (!node) {
			throw ValueNotFoundError("VERROR CHECK AHGHHH");
		}

		return node->getData();
	}

	template <class T>
	std::shared_ptr<class BST<T>::Node> BST<T>::find_node(T value) const
	{
		auto [node, parent] = GULocator(value);
		return node;
	}

	template <class T>
	void BST<T>::remove(T value)
	{
		if (!exists(value)) {
			throw ValueNotFoundError("VERROR CHECK NOT FOUNDDDD AH");
		}

		auto [node, parent] = GULocator(value);

		if (isLeaf(node)) {
			if (isRoot(node)) {
				root_ = nullptr;
			}
			else if (parent) {
				if (isLeftChild(node)) {
					parent->setLeftChild(nullptr);
				}
				else {
					parent->setRightChild(nullptr);
				}
			}

		}
		else if (hasOneChild(node)) {
			auto child = node->getLeftChild()
				? node->getLeftChild()
				: node->getRightChild();
			if (isRoot(node)) {
				root_ = child;
			}
			else if (parent) {
				if (isLeftChild(node)) {
					parent->setLeftChild(child);
				}
				else {
					parent->setRightChild(child);
				}
				child->setParent(parent);
				node->setParent(nullptr);
			}

		}
		else if (hasTwoChildren(node)) {
			auto newnew = node->getRightChild();
			while (newnew->getLeftChild()) {
				newnew = newnew->getLeftChild();
			}

			node->setData(newnew->getData());
			auto newnewP = newnew->getParent();
			auto newnewC = newnew->getRightChild();

			if (newnewP) {
				if (newnewP->getLeftChild() == newnew) {
					newnewP->setLeftChild(newnewC);
				}
				else {
					newnewP->setRightChild(newnewC);
				}
			}

			if (newnewC) {
				newnewC->setParent(newnewP);
			}

			newnew->setParent(nullptr);
			newnew->setRightChild(nullptr);
		}

		std::function<void(std::shared_ptr<Node>, size_t)> depthcheck;

		depthcheck = [&](std::shared_ptr<Node> node,
			size_t depthnow) {
				if (!node) return;
				node->setDepth(depthnow);
				depthcheck(node->getLeftChild(), depthnow + 1);
				depthcheck(node->getRightChild(), depthnow + 1);
			};
		if (parent) {
			depthcheck(parent, parent->getDepth());
		}
		else {
			depthcheck(root_, 0);
		}
		size_--;

	}

	template <class T>
	void BST<T>::remove(std::shared_ptr<BST<T>::Node> node)
	{
		if (!(node)) {
			throw ValueNotFoundError("VERROR CHECK NOT FOUNDDDD AH");
		}

		remove(node->getData());
	}

	template <class T>
	bool BST<T>::exists(T value) const
	{
		auto [node, parent] = GULocator(value);
		return node != nullptr;
	}

	template <class T>
	std::shared_ptr<class BST<T>::Node> BST<T>::getRoot() const
	{
		return root_;
	}

	template <class T>
	bool BST<T>::isRoot(const std::shared_ptr<BST<T>::Node>& node) const
	{
		if (node == root_) {
			return true;
		}
		else {
			return false;
		}
	}

	template <class T>
	bool BST<T>::isInternal(const std::shared_ptr<BST<T>::Node>& node) const
	{
		if (node && (node->getLeftChild() || node->getRightChild())) {
			return true;
		}
		else {
			return false;
		}
	}

	template <class T>
	bool BST<T>::isExternal(const std::shared_ptr<BST<T>::Node>& node) const
	{
		if (node) {
			if (!node->getLeftChild() && !node->getRightChild()) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}

	template <class T>
	bool BST<T>::isLeaf(const std::shared_ptr<BST<T>::Node>& node) const
	{
		if (node) {
			if (!node->getLeftChild() && !node->getRightChild()) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}

	template <class T>
	bool BST<T>::isParent(const std::shared_ptr<BST<T>::Node>& node) const
	{
		if (node) {
			if (node && (node->getLeftChild() || node->getRightChild())) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}

	template <class T>
	bool BST<T>::hasParent(const std::shared_ptr<BST<T>::Node>& node) const
	{
		if (node && node->getParent() != nullptr) {
			return true;
		}
		else {
			return false;
		}
	}

	template <class T>
	size_t BST<T>::getChildCount(const std::shared_ptr<BST<T>::Node>& node) const
	{
		size_t gcc = 0;
		if (node->getLeftChild()) {
			gcc++;
		}

		if (node->getRightChild()) {
			gcc++;
		}
		return gcc;
	}

	template <class T>
	bool BST<T>::hasOneChild(const std::shared_ptr<BST<T>::Node>& node) const
	{
		if (getChildCount(node) == 1) {
			return true;
		}
		else {
			return false;
		}
	}

	template <class T>
	bool BST<T>::hasTwoChildren(const std::shared_ptr<BST<T>::Node>& node) const
	{
		if (getChildCount(node) == 2) {
			return true;
		}
		else {
			return false;
		}
	}

	template <class T>
	bool BST<T>::isLeftChild(const std::shared_ptr<BST<T>::Node>& node) const
	{
		if (!node || !node->getParent()) {
			return false;
		}
		if (node->getParent()->getLeftChild() == node) {
			return true;
		}
		else {
			return false;
		}
	}

	template <class T>
	bool BST<T>::hasLeftChild(const std::shared_ptr<BST<T>::Node>& node) const
	{
		if (node && node->getLeftChild() != nullptr) {
			return true;
		}
		else {
			return false;
		}
	}

	template <class T>
	bool BST<T>::isRightChild(const std::shared_ptr<BST<T>::Node>& node) const
	{
		if (!node || !node->getParent()) {
			return false;
		}
		if (node->getParent()->getRightChild() == node) {
			return true;
		}
		else {
			return false;
		}
	}

	template <class T>
	bool BST<T>::hasRightChild(const std::shared_ptr<BST<T>::Node>& node) const
	{
		if (node && node->getRightChild() != nullptr) {
			return true;
		}
		else {
			return false;
		}
	}

	template <class T>
	void BST<T>::traversePreOrder
	(
		std::function<bool(BST<T>&, std::shared_ptr<BST<T>::Node>)> callback
	)
	{
		if (!root_) {
			return;
		}

		std::shared_ptr<Node> start = root_;
		auto moving = [&](std::shared_ptr<Node> here, auto&& here_)->bool {
			if (here == nullptr) {
				return true;
			}

			bool movecheck = callback(*this, here);
			if (movecheck == false) {
				return false;
			}

			if (here->getLeftChild() != nullptr) {
				bool movecheck1 = here_(here->getLeftChild(), here_);
				if (movecheck1 == false) {
					return false;
				}
			}

			if (here->getRightChild() != nullptr) {
				bool movecheck2 = here_(here->getRightChild(), here_);
				if (movecheck2 == false) {
					return false;
				}
			}
			return true;
			};
		moving(root_, moving);
	}

	template <class T>
	void BST<T>::traverseInOrder
	(
		std::function<bool(const BST<T>&, std::shared_ptr<BST<T>::Node>)> callback
	) const
	{
		if (!root_) {
			return;
		}

		std::shared_ptr<Node> start = root_;
		auto moving = [&](std::shared_ptr<Node> here, auto&& here_)->bool {
			if (here == nullptr) {
				return true;
			}

			if (here->getLeftChild() != nullptr) {
				bool movecheck = here_(here->getLeftChild(), here_);
				if (movecheck == false) {
					return false;
				}
			}

			bool movecheck = callback(*this, here);
			if (movecheck == false) {
				return false;
			}

			if (here->getRightChild() != nullptr) {
				bool movecheck = here_(here->getRightChild(), here_);
				if (movecheck == false) {
					return false;
				}
			}
			return true;

			};
		moving(root_, moving);
	}


	template <class T>
	void BST<T>::traverseInOrder
	(
		std::function<bool(BST<T>&, std::shared_ptr<BST<T>::Node>)> callback
	)
	{
		if (!root_) {
			return;
		}

		std::shared_ptr<Node> start = root_;
		auto moving = [&](std::shared_ptr<Node> here, auto&& here_)->bool {
			if (here == nullptr) {
				return true;
			}

			if (here->getLeftChild() != nullptr) {
				bool movecheck = here_(here->getLeftChild(), here_);
				if (movecheck == false) {
					return false;
				}
			}

			bool movecheck = callback(*this, here);
			if (movecheck == false) {
				return false;
			}

			if (here->getRightChild() != nullptr) {
				bool movecheck = here_(here->getRightChild(), here_);
				if (movecheck == false) {
					return false;
				}
			}
			return true;

			};
		moving(root_, moving);
	}

	template <class T>
	void BST<T>::traversePostOrder
	(
		std::function<bool(BST<T>&, std::shared_ptr<BST<T>::Node>)> callback
	)
	{
		if (!root_) {
			return;
		}

		std::shared_ptr<Node> start = root_;
		auto moving = [&](std::shared_ptr<Node> here, auto&& here_)->bool {
			if (here == nullptr) {
				return true;
			}

			if (here->getLeftChild() != nullptr) {
				bool movecheck = here_(here->getLeftChild(), here_);
				if (movecheck == false) {
					return false;
				}
			}

			if (here->getRightChild() != nullptr) {
				bool movecheck = here_(here->getRightChild(), here_);
				if (movecheck == false) {
					return false;
				}
			}

			bool movecheck = callback(*this, here);
			if (movecheck == false) {
				return false;
			}
			return true;

			};
		moving(root_, moving);
	}

	template <class T>
	void BST<T>::traverseLevelOrder
	(
		std::function<bool(const BST<T>&, std::shared_ptr<BST<T>::Node>)> callback
	) const
	{}

	template <class T>
	void BST<T>::traverseLevelOrder
	(
		std::function<bool(BST<T>&, std::shared_ptr<BST<T>::Node>)> callback
	)
	{}

	template <class T>
	void BST<T>::clear()
	{
		if (!root_) {
			return;
		}

		std::shared_ptr<Node> start = root_;
		auto movingWithNulling = [&](std::shared_ptr<Node> here, auto&& here_)->bool {
			if (here == nullptr) {
				return true;
			}

			if (here->getLeftChild() != nullptr) {
				bool movecheck = here_(here->getLeftChild(), here_);
				if (movecheck == false) {
					return false;
				}
			}

			if (here->getRightChild() != nullptr) {
				bool movecheck = here_(here->getRightChild(), here_);
				if (movecheck == false) {
					return false;
				}
			}

			if (here->getLeftChild()) {
				here->setLeftChild(nullptr);
			}

			if (here->getRightChild()) {
				here->setRightChild(nullptr);
			}

			if (here->getParent()) {
				auto pcheck = here->getParent();
				if (pcheck->getLeftChild() == here) {
					pcheck->setLeftChild(nullptr);
				}
				else if (pcheck->getRightChild() == here) {
					pcheck->setRightChild(nullptr);
				}
				here->setParent(nullptr);
			}
			return true;
			};
		movingWithNulling(root_, movingWithNulling);
		root_ = nullptr;
		size_ = 0;
	}

	template <class T>
	bool BST<T>::empty() const
	{
		if ((root_ == nullptr && size_ == 0)) {
			return true;
		}
		else {
			return false;
		}
	}

	template <class T>
	size_t BST<T>::size() const
	{
		return size_;
	}

	template <class T>
	std::shared_ptr<class BST<T>::Node> BST<T>::getDeepestLeaf()
	{
		if (!root_) {
			return 0;
		}
		std::shared_ptr<Node> foundIt = nullptr;

		std::queue<std::shared_ptr<Node>> GetINLINE;
		GetINLINE.push(root_);

		while (!GetINLINE.empty()) {
			std::shared_ptr<Node> here = GetINLINE.front();
			GetINLINE.pop();

			foundIt = here;

			if (here->getLeftChild() != nullptr) {
				GetINLINE.push(here->getLeftChild());
			}

			if (here->getRightChild() != nullptr) {
				GetINLINE.push(here->getRightChild());
			}
		}

		return foundIt;
	}

	template <class T>
	size_t BST<T>::computeHeight()
	{
		if (!root_) {
			return 0;
		}
		size_t height = 0;

		std::queue<std::shared_ptr<Node>> GetINLINE;
		GetINLINE.push(root_);

		while (!GetINLINE.empty()) {
			size_t levels = GetINLINE.size();
			for (size_t p = 0; p < levels; ++p) {
				std::shared_ptr<Node> here = GetINLINE.front();
				GetINLINE.pop();

				if (here->getLeftChild() != nullptr) {
					GetINLINE.push(here->getLeftChild());
				}

				if (here->getRightChild() != nullptr) {
					GetINLINE.push(here->getRightChild());
				}
			}
			height++;
		}
		return height;
	}

	template <class T>
	bool BST<T>::operator==(const BST<T>& other)
	{
		if (this->root_ == nullptr && other.root_ == nullptr) {
			return true;
		}

		if (this->root_ == nullptr || other.root_ == nullptr) {
			return false;
		}

		std::queue<std::shared_ptr<Node>> queue, queueAgain;
		queue.push(this->root_);
		queueAgain.push(other.root_);

		while (!queue.empty() && !queueAgain.empty()) {
			auto nqueue = queue.front();
			auto nq2 = queueAgain.front();
			queue.pop();
			queueAgain.pop();

			if (nqueue->getData() != nq2->getData()) {
				return false;
			}

			if (nqueue->getLeftChild() && nq2->getLeftChild()) {
				queue.push(nqueue->getLeftChild());
				queueAgain.push(nq2->getLeftChild());
			}
			else if (nqueue->getLeftChild() || nq2->getLeftChild()) {
				return false;
			}

			if (nqueue->getRightChild() && nq2->getRightChild()) {
				queue.push(nqueue->getRightChild());
				queueAgain.push(nq2->getRightChild());
			}
			else if (nqueue->getRightChild() || nq2->getRightChild()) {
				return false;
			}
		}
		return queue.empty() && queueAgain.empty();
	}

	template <class T>
	bool BST<T>::operator!=(const BST<T>& other)
	{
		if (*this == other) {
			return false;
		}
		else {
			return true;
		}
	}

	template <class T>
	class BST<T>& BST<T>::operator=(const BST<T>& other)
	{
		if (this == &other) {
			return *this;
		}

		this->clear();
		if (other.empty()) {
			root_ = nullptr;
			size_ = 0;
			return *this;
		}

		other.traverseLevelOrder(other.getRoot(),
			[&](const BST<T>&,
				std::shared_ptr<Node> node) {
					this->insert(node->getData());
					return true;
			}
		);
		return *this;
	}

	template <class T>
	void BST<T>::traverseLevelOrder
	(
		std::shared_ptr<BST<T>::Node> node,
		std::function<bool(const BST&, std::shared_ptr<BST<T>::Node>)> callback
	) const
	{
		if (this->empty()) {
			return;
		}

		std::queue<std::shared_ptr<BST<T>::Node>> q;
		q.push(node);

		while (!q.empty())
		{
			auto node = q.front();
			q.pop();

			if (!callback(*this, node)) {
				return;
			}

			if (node->getLeftChild()) {
				q.push(node->getLeftChild());
			}
			if (node->getRightChild()) {
				q.push(node->getRightChild());
			}
		}
	}

	template <class T>
	void BST<T>::traverseLevelOrder
	(
		std::shared_ptr<BST<T>::Node> node,
		std::function<bool(BST&, std::shared_ptr<BST<T>::Node>)> callback
	)
	{
		if (this->empty()) {
			return;
		}

		std::queue<std::shared_ptr<BST<T>::Node>> q;
		q.push(node);

		while (!q.empty())
		{
			auto node = q.front();
			q.pop();

			if (!callback(*this, node)) {
				return;
			}

			if (node->getLeftChild()) {
				q.push(node->getLeftChild());
			}
			if (node->getRightChild()) {
				q.push(node->getRightChild());
			}
		}
	}

#endif


