#include <Mojo/Services.hpp>

#include <stdio.h>

namespace Mojo
{
namespace Filesystem
{
    struct File {
        FILE* handle;
        uint32_t mode;
    };
}
namespace Services { template <> Mojo::Services::Filesystem* Get<Mojo::Services::Filesystem>(); }
namespace Providers
{
    class Filesystem : public Mojo::Services::Filesystem
    {
        public:
            Filesystem()
                : _initialized(false)
            {
            }

            ~Filesystem()
            {
            }

            bool Initialize()
            {
                if( !_initialized ) return false;
                _initialized = true;
                return true;
            }

            void Deinitialize()
            {
                _initialized = false;
            }

            const char* GetRootPath()
            {
                static const char* root_path = "";
                return root_path;
            }

            Mojo::Filesystem::File* Open( const char* path, uint32_t file_mode )
            {
                using namespace Mojo::Filesystem;

                FILE* file_handle = NULL;
                switch( file_mode ) {
                    case FILE_READ:       file_handle = fopen(path, "rb"); break;
                    case FILE_WRITE:      file_handle = fopen(path, "wb"); break;
                    case FILE_READ_WRITE: file_handle = fopen(path, "ab+"); break;
                }

                if( !file_handle ) return NULL;

                Mojo::Filesystem::File* file = new Mojo::Filesystem::File();
                file->handle = file_handle;
                file->mode   = file_mode;
                return file;
            }

            void Close( Mojo::Filesystem::File* file )
            {
                if( !file ) return;
                fclose(file->handle);
                delete file;
            }

            size_t Read( Mojo::Filesystem::File* file, size_t num_bytes, void* buffer )
            {
                if( !file ) return 0;
                return fread(buffer, sizeof(uint8_t), sizeof(num_bytes), file->handle);
            }

            size_t Write( Mojo::Filesystem::File* file, size_t num_bytes, const void* buffer )
            {
                if( !file ) return 0;
                return fwrite(buffer, sizeof(uint8_t), sizeof(num_bytes), file->handle);
            }

            size_t Length( Mojo::Filesystem::File* file )
            {
                if( !file ) return 0;
                
                fseek(file->handle, 0, SEEK_END);
                long length = ftell(file->handle);
                fseek(file->handle, 0, SEEK_SET);

                if( length < 0 ) return 0;
                return (size_t)length;
            }

        private:
            bool _initialized;
    };
}
namespace Services
{
    template <> Mojo::Services::Filesystem* Get<Mojo::Services::Filesystem>()
    {
        static Mojo::Providers::Filesystem* filesystem_provider = new Mojo::Providers::Filesystem();
        return (Mojo::Services::Filesystem*)filesystem_provider;
    }
}
}