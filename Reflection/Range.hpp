#pragma once

template <typename Type>
class Range
{
public:
  Range(Type &aBegin, Type &aEnd)
    : mBegin(aBegin), mEnd(aEnd) {};

  bool IsRange() { return mBegin != mEnd; }

  const Type begin() const { return mBegin; }
  const Type end() const { return mEnd; }
  Type begin() { return mBegin; }
  Type end() { return mEnd; }

  typename Type::difference_type size() const { return mEnd - mBegin; }
protected:
  Type mBegin;
  Type mEnd;
};
