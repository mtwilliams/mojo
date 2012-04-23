#ifndef MOJO_SERVICES_FILESYSTEM_HPP
#define MOJO_SERVICES_FILESYSTEM_HPP

#include <Mojo/Core.hpp>

#define MOJO_FILESYSTEM_REGISTER_CALLBACK( event, callback ) Mojo::Services::Get<Mojo::Services::Filesystem>()->Register_##event(callback);
#define MOJO_FILESYSTEM_DEREGISTER_CALLBACK( event, id ) Mojo::Services::Get<Mojo::Services::Filesystem>()->Deregister_##event(id);

namespace Mojo
{
namespace Filesystem
{
    struct File;

    enum FileMode {
        FILE_READ  = (1 << 0),
        FILE_WRITE = (1 << 1),
        FILE_READ_WRITE = FILE_READ | FILE_WRITE
    };
}

namespace Services
{
    class Filesystem : public Mojo::NonCopyable
    {
        public:
            virtual ~Filesystem() {}

            virtual bool Initialize() = 0;
            virtual void Deinitialize() = 0;

            virtual const char* GetRootPath() = 0;

            virtual Mojo::Filesystem::File* Open( const char* path, uint32_t file_mode ) = 0;
            virtual void Close( Mojo::Filesystem::File* file ) = 0;

            virtual size_t Read( Mojo::Filesystem::File* file, size_t num_bytes, void* buffer ) = 0;
            virtual size_t Write( Mojo::Filesystem::File* file, size_t num_bytes, const void* buffer ) = 0;
            virtual size_t Length( Mojo::Filesystem::File* file ) = 0;

            // todo: virtual uint32_t Register_OnFileChanged() = 0;
    };
}
}

#endif /* MOJO_SERVICES_FILESYSTEM_HPP */