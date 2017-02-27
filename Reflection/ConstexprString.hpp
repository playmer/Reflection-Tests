#pragma once

constexpr size_t StringLength(const char *aString)
{
  size_t i = 0;

  while (*aString != '\0')
  {
    ++i;
    ++aString;
  }

  return i;
}


constexpr size_t GetNumberOfTokens(const char *aString)
{
  size_t num = 0;



  return num;
}

template <size_t tConstSize>
struct ConstexprToken
{
  constexpr ConstexprToken(const char *aBegin)
    : mData{ '\0' }
  {
    for (size_t i = 0; i < tConstSize; i++)
    {
      mData[i] = aBegin[i];
    }

    mData[tConstSize] = '\0';
  }

  template<size_t tDifferentSize>
  constexpr ConstexprToken(const ConstexprToken<tDifferentSize> &aToken)
    : mData{ '0' }
  {
    static_assert(tDifferentSize <= tConstSize, "Trying to copy a ConstexprToken to a ConstexprToken of too small a size.");
    for (size_t i = 0; i < tDifferentSize; i++)
    {
      mData[i] = aToken.data()[i];
    }

    mData[tDifferentSize] = '\0';
  }

  constexpr size_t Size() const { return tConstSize; };
  constexpr size_t size() const { return tConstSize; };
  constexpr const char* Data() const { return mData; };
  constexpr const char* data() const { return mData; };

private:
  char mData[tConstSize + 1];
};


constexpr size_t GetLastInstanceOfCharacter(const char *aString, size_t aSize, char aCharacter)
{
  size_t toReturn = aSize + 1;

  while (aSize != 0)
  {
    if (aString[aSize] == aCharacter)
    {
      toReturn = aSize;
      break;
    }
    --aSize;
  }

  return toReturn;
}


constexpr size_t GetFirstInstanceOfCharacter(const char *aString, size_t aSize, char aCharacter)
{
  size_t toReturn = aSize + 1;

  size_t i = 0;

  while (i != aSize)
  {
    if (aString[i] == aCharacter)
    {
      toReturn = i;
      break;
    }
    ++i;
  }

  return toReturn;
}