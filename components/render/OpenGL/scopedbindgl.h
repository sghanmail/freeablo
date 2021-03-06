#pragma once
#include <glad/glad.h>
#include <optional>

namespace Render
{
    class BindableGL
    {
    public:
        virtual ~BindableGL() = default;
        virtual void bind(std::optional<GLuint> extra1, std::optional<GLuint> extra2) = 0;
        virtual void unbind(std::optional<GLuint> extra1, std::optional<GLuint> extra2) = 0;
    };

    class ScopedBindGL
    {
    public:
        ScopedBindGL() = default;
        ScopedBindGL(ScopedBindGL&) = delete;
        ScopedBindGL(ScopedBindGL&& other)
        {
            *this = other;
            other.mResource = nullptr;
        }

        explicit ScopedBindGL(BindableGL& resource, std::optional<GLuint> extra1 = std::nullopt, std::optional<GLuint> extra2 = std::nullopt)
            : mResource(&resource), mExtra1(extra1), mExtra2(extra2)
        {
            mResource->bind(mExtra1, mExtra2);
        }
        explicit ScopedBindGL(BindableGL* resource, std::optional<GLuint> extra1 = std::nullopt, std::optional<GLuint> extra2 = std::nullopt)
            : ScopedBindGL(*resource, extra1, extra2)
        {
        }

        ~ScopedBindGL()
        {
            if (mResource)
                mResource->unbind(mExtra1, mExtra2);
        }

    private:
        ScopedBindGL& operator=(const ScopedBindGL&) = default;

    private:
        BindableGL* mResource = nullptr;
        std::optional<GLuint> mExtra1;
        std::optional<GLuint> mExtra2;
    };
}
