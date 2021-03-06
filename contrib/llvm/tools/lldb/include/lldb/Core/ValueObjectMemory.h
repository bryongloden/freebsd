//===-- ValueObjectMemory.h -----------------------------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef liblldb_ValueObjectMemory_h_
#define liblldb_ValueObjectMemory_h_

// C Includes
// C++ Includes
// Other libraries and framework includes
// Project includes
#include "lldb/Core/ValueObject.h"
#include "lldb/Symbol/CompilerType.h"

namespace lldb_private {

//----------------------------------------------------------------------
// A ValueObject that represents memory at a given address, viewed as some 
// set lldb type.
//----------------------------------------------------------------------
class ValueObjectMemory : public ValueObject
{
public:
    ~ValueObjectMemory() override;

    static lldb::ValueObjectSP
    Create (ExecutionContextScope *exe_scope, 
            const char *name,
            const Address &address, 
            lldb::TypeSP &type_sp);

    static lldb::ValueObjectSP
    Create (ExecutionContextScope *exe_scope, 
            const char *name,
            const Address &address, 
            const CompilerType &ast_type);

    uint64_t
    GetByteSize() override;

    ConstString
    GetTypeName() override;

    ConstString
    GetDisplayTypeName() override;
    
    size_t
    CalculateNumChildren(uint32_t max) override;

    lldb::ValueType
    GetValueType() const override;

    bool
    IsInScope() override;

    lldb::ModuleSP
    GetModule() override;

protected:
    bool
    UpdateValue() override;
    
    CompilerType
    GetCompilerTypeImpl() override;

    Address  m_address;  ///< The variable that this value object is based upon
    lldb::TypeSP m_type_sp;
    CompilerType m_compiler_type;

private:
    ValueObjectMemory (ExecutionContextScope *exe_scope, 
                       const char *name,
                       const Address &address, 
                       lldb::TypeSP &type_sp);

    ValueObjectMemory (ExecutionContextScope *exe_scope,
                       const char *name, 
                       const Address &address,
                       const CompilerType &ast_type);
    //------------------------------------------------------------------
    // For ValueObject only
    //------------------------------------------------------------------
    DISALLOW_COPY_AND_ASSIGN (ValueObjectMemory);
};

} // namespace lldb_private

#endif // liblldb_ValueObjectMemory_h_
