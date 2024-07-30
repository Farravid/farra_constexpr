#include <cstddef>
#include <print>
#include <source_location>

namespace farra
{
    template <std::size_t Size>
    class LifeObject
    {
    public:
        LifeObject() noexcept
        {
            auto sl = std::source_location::current();
            std::println("{}", sl.function_name());
        }

        LifeObject(const LifeObject& other) noexcept
        {
            std::println("LifeObject(const LifeObject&) [copy constructor]");
        }

        LifeObject(LifeObject&&) noexcept
        {
            std::println("LifeObject(LifeObject&&) [move constructor]");
        }

        LifeObject& operator=(const LifeObject&) noexcept
        {
            std::println("operator=(const LifeObject&) [copy assignment]");
            return *this;
        }

        LifeObject& operator=(LifeObject&&) noexcept
        {
            std::println("operator=(LifeObject&&) [move assignment]");
            return *this;
        }

        ~LifeObject() noexcept
        {
            std::println("~LifeObject() [destructor]");
        }

    private:
        std::array<bool, Size> size{};
    };
}
