#ifndef MOJO_SCENE_NODE_HPP
#define MOJO_SCENE_NODE_HPP

#include <Mojo/Core.hpp>

namespace Mojo
{
    class MOJO_CLASS_EXPORT(SceneNode) : public Mojo::NonCopyable
    {
        public:
            SceneNode();
            ~SceneNode();

            SceneNode* GetParent() const { return _parent; }
            SceneNode* GetLeftChild() const { return _left_child; }
            SceneNode* GetRightChild() const { return _right_child; }



        private:
            SceneNode* _parent;
            SceneNode* _left_child, _right_child;
    };
}

#endif /* MOJO_SCENE_NODE_HPP */