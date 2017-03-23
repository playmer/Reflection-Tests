#pragma once

#include <algorithm>

template<typename ForwardIterator, typename Type, typename Predicate> inline
ForwardIterator CacheFriendlyLowerBound(ForwardIterator aFirst, 
                                        ForwardIterator aLast, 
                                        const Type& aValue, 
                                        Predicate& aPredicate)
{
  typename ForwardIterator::difference_type count = aLast - aFirst;
  typename ForwardIterator::difference_type i = count;
  typename ForwardIterator::difference_type j = 0;

  while (j < count)
  {
    ForwardIterator middle = aFirst + j;

    if (aPredicate(*middle, aValue))
    {
      j = 2 * j + 2;
    }
    else
    {
      i = j;
      j = 2 * j + 1;
    }
  }

  return aFirst + i;
}


template<typename ForwardIterator, typename Type, typename Predicate> inline
ForwardIterator CacheFriendlyUpperBound(ForwardIterator aFirst,
                                        ForwardIterator aLast, 
                                        const Type& aValue, 
                                        Predicate& aPredicate)
{
  typename ForwardIterator::difference_type count = aLast - aFirst;
  typename ForwardIterator::difference_type i = count; 
  typename ForwardIterator::difference_type j = 0;

  while (j < count)
  {
    ForwardIterator middle = aFirst + j;

    if (!aPredicate(aValue, *middle))
    {
      j = 2 * j + 2;
    }
    else
    {
      i = j;
      j = 2 * j + 1;
    }
  }

  return aFirst + i;
}