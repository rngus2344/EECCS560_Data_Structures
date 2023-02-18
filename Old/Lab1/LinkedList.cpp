/* -----------------------------------------------------------------------------
*	@author Guhyoun Nam
* @file LinkedList.cpp
* @date 6/26/2020
* @brief cpp file of LinkedList
 ---------------------------------------------------------------------------- */
//Start your program.

template <typename T>
LinkedList<T>::LinkedList()
{
  m_length = 0;
  m_front = nullptr;
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T> & orig)
{
  int index = 1;
  Node<T>* temp = orig.m_front;
  while(temp != nullptr)
  {
    insert(index, temp->getEntry());
    index++;
    temp = temp->getNext();
  }
}

template <typename T>
LinkedList<T>::~LinkedList()
{
  clear();
}

template <typename T>
void LinkedList<T>::insert(T entry, int index)
{
  if(index>m_length+1 || index<1) throw(std::runtime_error("Insert index is invalid."));
    if(index==1)
    {
        Node<T>* createTemp=new Node<T>(entry);
        createTemp->setNext(m_front);
        m_front=createTemp;
        m_length++;
    }
    else
    {
        Node<T>* leftLinkTemp=m_front;
        Node<T>* createTemp=nullptr;
        Node<T>* rightLinkTemp=nullptr;
        for(int i=1;i<index-1;i++)
        {
            leftLinkTemp=leftLinkTemp->getNext();
        }//sets leftLink to one before the index
        rightLinkTemp=leftLinkTemp->getNext();//sets rightLink one head of leftLink
        createTemp=new Node<T>(entry);//creates new Node
        leftLinkTemp->setNext(createTemp);//links left neighbor to the new Node
        createTemp->setNext(rightLinkTemp);//links new Node to the right neighbor
        m_length++;
    }
}

template <typename T>
void LinkedList<T>::remove(int index)
{
  if(index <1 || index > m_length)
  {
    throw(std::runtime_error("Invalid index.\n"));
  }
  if(index == 1)
  {
    Node<T>* nodeHolder = m_front;
    m_front = nodeHolder->getNext();
    delete nodeHolder;
  }
  else
  {
    Node<T>* scanner = m_front;
    Node<T>* temp;
    for(int i=1; i<index-1; i++)
    {
      scanner = scanner->getNext();
    }
    temp = scanner->getNext();
    Node<T>* nodeHolder = temp->getNext();
    scanner->setNext(nodeHolder->getNext());
    m_front = scanner;
    delete scanner;
    delete nodeHolder;
  }
  m_length--;
}

template <typename T>
T LinkedList<T>::getEntry(int index) const
{
  if(index > m_length || index < 1)
  {
    throw(std::runtime_error("Invalid index.\n"));
  }
  else
  {
    Node<T>* scanner = m_front;
    if(index == 1)
    {
      return(m_front->getEntry());
    }
    else
    {
      for(int i=1; i<index; i++)
      {
        scanner = scanner->getNext();
      }
      return(scanner->getEntry());
    }
    delete scanner;
  }
}

template <typename T>
void LinkedList<T>::setEntry(int index, T entry)
{
  remove(index);
  insert(entry, index);
}

template <typename T>
void LinkedList<T>::clear()
{
  while(m_length>0)
  {
    remove(1);
  }
}

template <typename T>
int LinkedList<T>::getLength() const
{
  return m_length;
}

template <typename T>
bool LinkedList<T>::isEmpty()
{
  if(m_front == NULL)
  {
    return(true);
  }
  else
  {
    return(false);
  }
}

template <typename T>
void LinkedList<T>::delete(T entry)
{
  // // find
  // Node<T>* scanner = m_front;
  // Node<T>* temp;
  //
  //   Node<T> *temp = m_front;
  //   int count = 0;
  //
  //   while(m_front != NULL)
  //   {
  //     if(m_front->getEntry() == entry)
  //     {
  //
  //     }
  //     m_front = m_front->getNext();
  //   }
  //   m_front = temp;
  //   return(count);
  //
  // // remove
  //   Node<T>* scanner = m_front;
  //   Node<T>* temp;
  //   for(int i=1; i<index-1; i++)
  //   {
  //     scanner = scanner->getNext();
  //   }
  //   temp = scanner->getNext();
  //   Node<T>* nodeHolder = temp->getNext();
  //   scanner->setNext(nodeHolder->getNext());
  //   m_front = scanner;
  //   delete scanner;
  //   delete nodeHolder;
  // m_length--;
}

template <typename T>
bool LinkedList<T>::find(T entry)
{
  if(isEmpty())
  {
    return(false);
  }
  else
  {
    Node<T> *temp = m_front;
    int count = 0;

    while(m_front != NULL)
    {
      if(m_front->getEntry() == entry)
      {
        count = 1;
      }
      m_front = m_front->getNext();
    }
    m_front = temp;
    return(count);
  }
}
// T findPrev(x);
// void appendList();

template <typename T>
void LinkedList<T>::forwardTraverse()
{
  if(isEmpty())
  {
    std::cout << "The list is empty\n";
  }
  else
  {
    Node<T> *temp = m_front;
    while(m_front != NULL)
    {
      std::cout << m_front->getEntry() << " ";
      m_front = m_front->getNext();
    }
    m_front = temp;
    std::cout << '\n';
  }
}

template <typename T>
void LinkedList<T>::backwardTraverse()
{
  if(isEmpty())
  {
    std::cout << "The list is empty\n";
  }
  else
  {
    Node<T> *temp = m_front;
    T arr[m_length];
    int count = m_length-1;

    while(m_front != NULL)
    {
      arr[count] = m_front->getEntry();
      m_front = m_front->getNext();
      count--;
    }

    for(int i=0; i<m_length; i++)
    {
      std::cout << arr[i] << ' ';
    }
    m_front = temp;
    std::cout << '\n';
  }
}
