#ifndef MOJO_CORE_DELEGATE_HPP
#define MOJO_CORE_DELEGATE_HPP

#include <Mojo/Core/Types.h>
#include <Mojo/Core/Export.h>
#include <Mojo/Core/Assert.h>

#define DELEGATE_NAME Delegate0
    #include <Mojo/Core/Delegate.template>
#undef  DELEGATE_NAME

#define DELEGATE_NAME Delegate1
#define DELEGATE_TARGS typename T1
#define DELEGATE_SARGS T1
#define DELEGATE_FARGS T1 t1
#define DELEGATE_CARGS t1
    #include <Mojo/Core/Delegate.template>
#undef  DELEGATE_CARGS
#undef  DELEGATE_FARGS
#undef  DELEGATE_SARGS
#undef  DELEGATE_TARGS
#undef  DELEGATE_NAME

#define DELEGATE_NAME Delegate2
#define DELEGATE_TARGS typename T1, typename T2
#define DELEGATE_SARGS T1, T2
#define DELEGATE_FARGS T1 t1, T2 t2
#define DELEGATE_CARGS t1, t2
    #include <Mojo/Core/Delegate.template>
#undef  DELEGATE_CARGS
#undef  DELEGATE_FARGS
#undef  DELEGATE_SARGS
#undef  DELEGATE_TARGS
#undef  DELEGATE_NAME

#endif /* MOJO_CORE_DELEGATE_HPP */