#pragma once




template <typename TemplateType>
class const_iterator;

template <typename TemplateType>
class iterator : public std::iterator<std::random_access_iterator_tag, TemplateType>
{
public:
  using pointer = TemplateType*;
  using reference = TemplateType&;
  using value_type = TemplateType;
  using size_type = size_t;

  inline iterator(pointer aPointer = nullptr)
    : mCurrent(aPointer)
  {

  }

  inline iterator(const iterator &aIterator)
    : mCurrent(aIterator.mCurrent)
  {

  }

  inline iterator& operator=(const iterator &aIterator)
  {
    mCurrent = aIterator.mCurrent;
    return *this;
  }

  inline iterator& operator++()
  {
    ++mCurrent;
    return *this;
  }

  inline iterator operator++(int)
  {
    iterator previousIter{ *this };
    ++mCurrent;
    return previousIter;
  }

  operator const_iterator<TemplateType>();

  inline bool operator==(const iterator &aIterator)
  {
    return mCurrent == aIterator.mCurrent;
  }

  inline bool operator!=(const iterator &aIterator)
  {
    return mCurrent != aIterator.mCurrent;
  }

  inline reference operator*()
  {
    return *mCurrent;
  }

  inline pointer operator->()
  {
    return mCurrent;
  }

private:
  pointer mCurrent;
};

template <typename TemplateType>
class const_iterator : public std::iterator<std::random_access_iterator_tag, const TemplateType>
{
public:
  using pointer = const TemplateType*;
  using reference = const TemplateType&;
  using value_type = const TemplateType;
  using size_type = size_t;

  friend class iterator<TemplateType>;

  inline const_iterator(pointer aPointer = nullptr)
    : mCurrent(aPointer)
  {

  }

  inline const_iterator(const const_iterator &aIterator)
    : mCurrent(aIterator.mCurrent)
  {

  }

  inline const_iterator& operator=(const const_iterator &aIterator)
  {
    mCurrent = aIterator.mCurrent;
    return *this;
  }

  inline const_iterator& operator++()
  {
    ++mCurrent;
    return *this;
  }

  inline const_iterator operator++(int)
  {
    const_iterator previousIter{ *this };
    ++mCurrent;
    return previousIter;
  }

  inline bool operator==(const const_iterator &aIterator)
  {
    return mCurrent == aIterator.mCurrent;
  }

  inline bool operator!=(const const_iterator &aIterator)
  {
    return mCurrent != aIterator.mCurrent;
  }

  inline reference operator*()
  {
    return *mCurrent;
  }

  inline pointer operator->()
  {
    return mCurrent;
  }

private:
  pointer mCurrent;
};

template<typename TemplateType>
iterator<TemplateType>::operator const_iterator<TemplateType>()
{
  const_iterator<TemplateType> it;
  it.mCurrent = mCurrent;

  return it;
}


template<typename IteratorType>
class CountingIterator : public IteratorType
{
public:
  inline CountingIterator(const IteratorType &aIterator)
    : IteratorType(aIterator), mCount(0)
  {

  }

  //inline CountingIterator& operator++()
  //{
  //  IteratorType::operator++;
  //  return *this;
  //}
  //
  //inline CountingIterator operator++(int)
  //{
  //  IteratorType::operator++(int);
  //  return previousIter;
  //}

  inline size_t Count()
  {
    return mCount;
  }
private:
  size_t mCount = 0;
};
