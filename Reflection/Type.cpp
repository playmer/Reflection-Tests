#pragma once

#include "Type.hpp"

DefineType(DocumentedObject)
{
  auto documentation = BindProperty<decltype(&DocumentedObject::GetDocumentation),
                                    &DocumentedObject::GetDocumentation,
                                    decltype(&DocumentedObject::SetDocumentation), 
                                    &DocumentedObject::SetDocumentation>("Documentation");

  GetStaticType()->AddProperty(std::move(documentation));
}

DefineType(Type)
{

}

DefineType(Function)
{

}


DefineType(Property)
{

}


DefineType(Field)
{

}

DefineExternalType(void)
DefineExternalType(i8)
DefineExternalType(i16)
DefineExternalType(i32)
DefineExternalType(i64)
DefineExternalType(u8)
DefineExternalType(u16)
DefineExternalType(u32)
DefineExternalType(u64)
DefineExternalType(float)
DefineExternalType(double)
DefineExternalType(std::string)