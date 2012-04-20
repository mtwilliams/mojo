#ifndef MOJO_CORE_NON_COPYABLE_HPP
#define MOJO_CORE_NON_COPYABLE_HPP

#include <Mojo/Core/Types.hpp>
#include <Mojo/Core/Export.hpp>

namespace Mojo
{
    class MOJO_CLASS_EXPORT(NonCopyable)
    {
        private:
            NonCopyable( const NonCopyable& other );
            NonCopyable& operator=( const NonCopyable& other );

        protected:
            NonCopyable() {}
            virtual ~NonCopyable() {}
    };
}

#endif /* MOJO_CORE_NON_COPYABLE_HPP */