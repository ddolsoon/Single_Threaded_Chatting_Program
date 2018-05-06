//#ifndef _LINKED_LIST_H
//#define _LINKED_LIST_H
//
///**
//*	Structure for NodeType to use in Linked structure.
//*/
//template <typename ItemType>
//struct NodeType
//{
//	ItemType data;	///< A data for each node.
//	NodeType * next;	///< A node pointer to point succeed node.
//};
//
//
///**
//*	Simple unsorted list class for managing items.
//*/
//template <typename ItemType>
//class LinkedList
//{
//private:
//	NodeType<ItemType>* m_pList;	///< Pointer for pointing a first node.
//	NodeType<ItemType>* m_pCurPointer;	///< Node pointer for pointing current node to use iteration.
//	int m_nLength;	///< Number of node in the list.
//	NodeType<ItemType>* m_currentNode;
//	NodeType<ItemType>* m_newNode;
//public:
//	/**
//	*	default constructor.
//	*/
//	LinkedList();
//
//	/**
//	*	@brief	���� ������ ����, ������ �����ε��� ���ؼ� Deep Copy �Ѵ�.(�̰Ծ�����, Memory Leak �߻�)
//	*	@pre	None
//	*	@post	����Ʈ�� Deep Copy�Ǿ�����.
//	*/
//	LinkedList<ItemType>& operator=(const LinkedList<ItemType>& l)
//	{
//		//MakeEmpty();
//		//cout << "Linked List ���� ������ �����ε� ȣ��" << endl;
//		m_pList = NULL;
//		m_pCurPointer = NULL;
//		m_nLength = l.m_nLength;
//
//		m_currentNode = l.m_pList;
//		while (m_currentNode != NULL) {
//			if (m_pList == NULL) {
//				m_newNode = new NodeType<ItemType>;
//				m_newNode->data = m_currentNode->data;
//				m_newNode->next = NULL;
//				m_pList = m_newNode;
//				m_pCurPointer = m_pList;
//			}
//			else {
//				m_newNode = new NodeType<ItemType>;
//				m_newNode->data = m_currentNode->data;
//				m_newNode->next = NULL;
//
//				m_pCurPointer->next = m_newNode;
//				m_pCurPointer = m_pCurPointer->next;
//
//			}
//			m_currentNode = m_currentNode->next;
//
//		}
//
//		return *this;
//	}
//
//	/**
//	*	destructor.
//	*/
//	~LinkedList();
//
//	/**
//	*	@brief	Initialize list to empty state.
//	*	@pre	None
//	*	@post	List is empty.
//	*/
//	void MakeEmpty();
//
//	/**
//	*	@brief	Get number of elements in the list.
//	*	@pre	None.
//	*	@post	Function value = number of elements in list.
//	*	@return	Number of elements in this list.
//	*/
//	int GetLength() const;
//
//	/**
//	*	@brief	Add item into this list.
//	*	@pre	List is not full. item is not in list.
//	*	@post	Item is inserted in this list.
//	*	@return	1 if this function works well, otherwise 0.
//	*/
//	int Add(ItemType item);
//
//	/**
//	*	@brief	Retrieve list element whose key matches item's key (if present).
//	*	@pre	Key member of item is initialized.
//	*	@post	If there is an element whose key matches with item's key then the element's record is copied to the item.
//	*	@return	1 if any element's primary key matches with item's, otherwise 0.
//	*/
//	int Get(ItemType& item);
//
//	/**
//	*	@brief	Initialize current pointer for an iteration through the list.
//	*	@pre	None.
//	*	@post	current pointer is prior to list. current pointer has been initialized.
//	*/
//	void ResetList();
//
//	/**
//	*	@brief	Get the next element in list.
//	*	@pre	current pointer is defined. Element at current pointer is not last in list.
//	*	@post	current pointer is updated to next position. item is a copy of element at current pointer.
//	*/
//	void GetNextItem(ItemType& item);
//
//	/**
//	*	@brief	����Ʈ�� �������ִ��� �� Ȯ���ϴ� �Լ�
//	*	@pre	����Ʈ�� �ʱ�ȭ�Ǿ��� �־���Ѵ�..
//	*	@return	true �Ǵ� false ��ȯ.
//	*/
//	bool IsFull() const;
//
//	/**
//	*	@brief	����Ʈ�� ����ִ��� �� Ȯ���ϴ� �Լ�
//	*	@pre	����Ʈ�� �ʱ�ȭ�Ǿ��� �־���Ѵ�..
//	*	@return	true �Ǵ� false ��ȯ.
//	*/
//	bool IsEmpty() const;
//
//	/**
//	*	@brief	Delete list element whose key matches item's key (if present).
//	*	@pre	Key member of item is initialized.
//	*	@post	If there is an element whose key matches with item's key then the element's record is copied to the item.
//	*	@return	1 if any element's primary key matches with item's, otherwise 0.
//	*/
//	int Delete(ItemType item);
//
//	/**
//	*	@brief	Replace list element whose key matches item's key (if present).
//	*	@pre	Key member of item is initialized.
//	*	@post	If there is an element whose key matches with item's key then the element's record is copied to the item.
//	*	@return	1 if any element's primary key matches with item's, otherwise 0.
//	*/
//	int Replace(ItemType item);
//
//	/**
//	*	@brief	Display list element whose key matches item's key (if present).
//	*	@pre	Key member of item is initialized.
//	*	@post	If there is an element whose key matches with item's key then the element's record is copied to the item.
//	*	@return	1 if any element's primary key matches with item's, otherwise 0.
//	*/
//	int Display(ItemType item);
//
//};
//
//
//// Class constructor
//template <typename ItemType>
//LinkedList<ItemType>::LinkedList()
//{
//	m_nLength = 0;
//	m_pList = NULL;
//	m_pCurPointer = NULL;
//}
//
//// Class destructor
//template <typename ItemType>
//LinkedList<ItemType>::~LinkedList()
//{
//	//����Ʈ���� ��� node ����
//	MakeEmpty();
//}
//
//template <typename ItemType>
//bool LinkedList<ItemType>::IsEmpty() const
//{
//	if (m_pList == NULL)
//		return true;
//	else
//		return false;
//}
//
//template <typename ItemType>
//int LinkedList<ItemType>::Delete(ItemType item)
//{
//	NodeType<ItemType> * deleteLocation;
//
//	if (IsEmpty())	//����Ʈ�� ���� �� ���,
//		return 0;
//
//	ItemType dummy;
//	ResetList();	//m_pCurPointer NULL�� �ʱ�ȭ
//	GetNextItem(dummy);
//
//	if (item == m_pCurPointer->data)	//�ٷ� ã�� ���, (lucky guy!)
//	{
//		deleteLocation = m_pCurPointer;
//		m_pList = m_pList->next;
//	}
//	else
//	{
//		bool found = false;
//		while (!found && m_pCurPointer->next != NULL)
//		{
//			if (item == (m_pCurPointer->next)->data)
//			{
//				found = true;
//				break;
//			}
//			GetNextItem(dummy);
//
//		}
//
//		if (!found)
//			return 0;
//
//		deleteLocation = m_pCurPointer->next;
//		m_pCurPointer->next = (m_pCurPointer->next)->next;
//
//	}
//
//
//	delete deleteLocation;
//	m_nLength--;
//
//	return 1;
//}
//
//
//template <typename ItemType>
//bool LinkedList<ItemType>::IsFull() const
//{
//	NodeType<ItemType> * test;
//	try
//	{
//		test = new NodeType<ItemType>;
//		delete test;
//		return false;
//
//	}
//	catch (bad_alloc exception)
//	{
//		return true;
//	}
//}
//
//
//
//
//// Initialize list to empty state.
//template <typename ItemType>
//void LinkedList<ItemType>::MakeEmpty()
//// Post: List is empty; all items have been deallocated.
//{
//	// ����Ʈ���� ��� ��� ���� �ϰ� ����Ʈ�� length�� �ʱ�ȭ
//	NodeType<ItemType> * tempPtr;
//
//	while (m_pList != NULL)
//	{
//		tempPtr = m_pList;
//		m_pList = m_pList->next;
//	
//	}
//
//	m_nLength = 0;
//}
//
//
//// Get number of elements in the list.
//template <typename ItemType>
//int LinkedList<ItemType>::GetLength() const
//{
//	return m_nLength;
//}
//
//
//// Add item into this list.
//template <typename ItemType>
//int LinkedList<ItemType>::Add(ItemType item)
//{
//	bool moreToSearch;
//	NodeType<ItemType> * location;
//	NodeType<ItemType> * preLoc;
//	NodeType<ItemType> * newNode;
//	newNode = new NodeType<ItemType>;
//	newNode->data = item;
//	newNode->next = NULL;
//
//	if (m_pList == NULL) {
//		m_pList = newNode;
//		m_nLength++;
//	}
//	else {
//		location = m_pList;
//		preLoc = m_pList;
//		moreToSearch = (location != NULL);
//		while (moreToSearch)
//		{
//			if (item < location->data)
//			{
//				moreToSearch = false;
//			}
//			else if (item > location->data)
//			{
//				preLoc = location;
//				location = location->next;
//				moreToSearch = (location != NULL);
//			}
//		
//		}
//
//		if (preLoc == location)
//		{
//			newNode->next = m_pList;
//			m_pList = newNode;
//		}
//		else
//		{
//			preLoc->next = newNode;
//			newNode->next = location;
//		}
//		m_nLength++;
//
//	}
//
//	return 1;
//}
//
//template <typename ItemType>
//int LinkedList<ItemType>::Get(ItemType& item)
//{
//	bool moreToSearch, found;
//	NodeType<ItemType> * location;
//
//	location = m_pList;
//	found = false;
//	moreToSearch = (location != NULL);
//
//	while (moreToSearch && !found)
//	{
//
//		if (location->data == item)
//		{
//			found = true;
//			item = location->data;
//		}
//		else
//		{
//			location = location->next;
//			moreToSearch = (location != NULL);
//		}
//	}
//
//	if (found)
//		return 1;
//	else
//		return 0;
//}
//
//
//// Initializes current pointer for an iteration through the list.
//template <typename ItemType>
//void LinkedList<ItemType>::ResetList()
//{
//	// current pointer �ʱ�ȭ
//	m_pCurPointer = NULL;
//}
//
//
//// Gets the next element in list.
//template <typename ItemType>
//void LinkedList<ItemType>::GetNextItem(ItemType& item)
//{
//	// current pointer �� NULL�̶�� ó�� node�� ����Ŵ.
//	if (m_pCurPointer == NULL)
//	{
//		m_pCurPointer = m_pList;
//	}
//	else
//		//current position �� ���� ���� �̵�
//		m_pCurPointer = m_pCurPointer->next;
//
//	//item �� current position �� info �� ����
//	if (m_pCurPointer != NULL)
//		item = m_pCurPointer->data;
//}
//
//template <typename ItemType>
//int LinkedList<ItemType>::Replace(ItemType item)
//{
//	bool moreToSearch, found;
//	NodeType<ItemType> * location;
//
//	location = m_pList;
//	found = false;
//	moreToSearch = (location != NULL);
//
//	while (moreToSearch && !found)
//	{
//
//		if (item == location->data)
//		{
//			found = true;
//			location->data = item;
//		}
//		else
//		{
//			location = location->next;
//			moreToSearch = (location != NULL);
//		}
//	}
//
//	if (found)
//		return 1;
//	else
//		return 0;
//}
//
//template <typename ItemType>
//int LinkedList<ItemType>::Display(ItemType item)
//{
//	bool moreToSearch, found;
//	NodeType<ItemType> * location;
//
//	location = m_pList;
//	found = false;
//	moreToSearch = (location != NULL);
//
//	while (moreToSearch && !found)
//	{
//
//		if (item == location->data)
//		{
//			found = true;
//			item = location->data;
//		}
//		else
//		{
//			location = location->next;
//			moreToSearch = (location != NULL);
//		}
//	}
//
//	if (found)
//	{
//		item.DisplayRecordOnScreen();
//		return 1;
//	}else
//		return 0;
//
//}
//
//
//#endif	// LINKED_LIST