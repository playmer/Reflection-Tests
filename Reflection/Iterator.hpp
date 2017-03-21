#pragma once




template <typename TemplateType>
class ConstRandomAccessIterator;

template <typename TemplateType>
class RandomAccessIterator : public std::iterator<std::random_access_iterator_tag, TemplateType>
{
public:
  using pointer = TemplateType*;
  using reference = TemplateType&;
  using value_type = TemplateType;
  using size_type = size_t;

  inline RandomAccessIterator(pointer aPointer = nullptr)
    : mCurrent(aPointer)
  {

  }

  inline RandomAccessIterator(const RandomAccessIterator &aIterator)
    : mCurrent(aIterator.mCurrent)
  {

  }

  inline RandomAccessIterator& operator=(const RandomAccessIterator &aIterator)
  {
    mCurrent = aIterator.mCurrent;
    return *this;
  }

  inline RandomAccessIterator& operator++()
  {
    ++mCurrent;
    return *this;
  }

  inline RandomAccessIterator operator++(int)
  {
    RandomAccessIterator previousIter{ *this };
    ++mCurrent;
    return previousIter;
  }

  operator ConstRandomAccessIterator<TemplateType>();

  inline bool operator==(const RandomAccessIterator &aIterator)
  {
    return mCurrent == aIterator.mCurrent;
  }

  inline bool operator!=(const RandomAccessIterator &aIterator)
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
class ConstRandomAccessIterator : public std::iterator<std::random_access_iterator_tag, const TemplateType>
{
public:
  using pointer = const TemplateType*;
  using reference = const TemplateType&;
  using value_type = const TemplateType;
  using size_type = size_t;

  friend class RandomAccessIterator<TemplateType>;

  inline ConstRandomAccessIterator(pointer aPointer = nullptr)
    : mCurrent(aPointer)
  {

  }

  inline ConstRandomAccessIterator(const ConstRandomAccessIterator &aIterator)
    : mCurrent(aIterator.mCurrent)
  {

  }

  inline ConstRandomAccessIterator& operator=(const ConstRandomAccessIterator &aIterator)
  {
    mCurrent = aIterator.mCurrent;
    return *this;
  }

  inline ConstRandomAccessIterator& operator++()
  {
    ++mCurrent;
    return *this;
  }

  inline ConstRandomAccessIterator operator++(int)
  {
    ConstRandomAccessIterator previousIter{ *this };
    ++mCurrent;
    return previousIter;
  }

  inline bool operator==(const ConstRandomAccessIterator &aIterator)
  {
    return mCurrent == aIterator.mCurrent;
  }

  inline bool operator!=(const ConstRandomAccessIterator &aIterator)
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
RandomAccessIterator<TemplateType>::operator ConstRandomAccessIterator<TemplateType>()
{
  ConstRandomAccessIterator<TemplateType> it;
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
