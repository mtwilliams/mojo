#ifndef MOJO_UI_CONTROL_HPP
#define MOJO_UI_CONTROL_HPP

#include <Mojo/Core.hpp>
#include <Mojo/Math.hpp>

#include <list>

namespace Mojo
{
namespace UI
{
    class MOJO_CLASS_EXPORT(Control) : public Mojo::NonCopyable
    {
        public:
            Control( const int32_t x, const int32_t y, const int32_t width, const int32_t height )
                : _is_dirty(true)
                , _parent(NULL)
                , _bounds(x, y, width, height)
            {
            }

            virtual ~Control()
            {
                if( _parent ) _parent->RemoveChild(this);
            }

            Mojo::Vector2i Position() const { return Mojo::Vector2i(_bounds.x, _bounds.y); }
            Mojo::Vector2i Size() const { return Mojo::Vector2i(_bounds.width, _bounds.height); }
            Mojo::Recti    Bounds() const { return _bounds; }

            std::list<Control*>& Children() { return _children; }
            Control* Parent() const { return _parent; }
            bool Dirty() const { return _is_dirty; }

            void AddChild( Mojo::UI::Control* child )
            {
                _children.push_back(child);
                if( child->_parent ) child->_parent->RemoveChild(child);
                child->_is_dirty = false;
                child->_parent = NULL;
                _is_dirty = true;
            }

            void RemoveChild( Mojo::UI::Control* child )
            {
                _children.remove(child);
                child->_is_dirty = false;
                child->_parent = NULL;
                _is_dirty = true;
            }

        private:
            bool _is_dirty;
            Control* _parent;
            std::list<Control*> _children;
            Mojo::Recti _bounds;
    };
}
}

#endif /* MOJO_UI_CONTROL_HPP */