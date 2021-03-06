#ifndef MOJO_CORE_NON_COPYABLE_HPP
#define MOJO_CORE_NON_COPYABLE_HPP

#include <Mojo/Core/Types.h>
#include <Mojo/Core/Export.h>

namespace Mojo
{
    class MOJO_CLASS_EXPORT(NonCopyable)
    {
        protected:
            NonCopyable( const NonCopyable& other );
            NonCopyable& operator=( const NonCopyable& other );
            NonCopyable() {}
            virtual ~NonCopyable() {}
    };
}

#endif /* MOJO_CORE_NON_COPYABLE_HPP */