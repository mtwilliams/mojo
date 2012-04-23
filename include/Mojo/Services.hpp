#ifndef MOJO_SERVICES_HPP
#define MOJO_SERVICES_HPP

#include <Mojo/Core.hpp>

#include <Mojo/Services/InputService.hpp>
#include <Mojo/Services/PhysicsService.hpp>
#include <Mojo/Services/GraphicsService.hpp>
#include <Mojo/Services/FilesystemService.hpp>

#define MOJO_GET_SERVICE( service ) Mojo::Services::Get<Mojo::Services::service>()

namespace Mojo
{
namespace Services
{
    template <typename T>
    MOJO_EXPORT(T* Get());
}
}

#endif /* MOJO_SERVICES_HPP */