#include <cstddef>
#include <print>
#include <source_location>
#include <filesystem>
//TODO: Maybe adding the stack trace could be cool for knowing where the call is coming

namespace farra
{
    //template <std::size_t Size>
    class LifeObject
    {
    public:
        LifeObject(const std::source_location sl = std::source_location::current()) noexcept
        {
            // std::filesystem::path path {sl.file_name()};
            // std::println("{} ({}:{}) `{}` -> {}", path.filename().string(), sl.line(), sl.column(), sl.function_name(),
            //     "LifeObject() [constructor]");

            ++timesConstructor;
        }

        LifeObject(const LifeObject& other, const std::source_location sl = std::source_location::current()) noexcept
        {
            // std::filesystem::path path {sl.file_name()};
            // std::println("{} ({}:{}) `{}` -> {}", path.filename().string(), sl.line(), sl.column(), sl.function_name(),
            //     "LifeObject(const LifeObject&) [copy constructor]");

            ++timesCopyConstructor;
        }

        LifeObject(LifeObject&&, const std::source_location sl = std::source_location::current()) noexcept
        {
            // std::filesystem::path path {sl.file_name()};
            // std::println("{} ({}:{}) `{}` -> {}", path.filename().string(), sl.line(), sl.column(), sl.function_name(),
            //     "LifeObject(LifeObject&&) [move constructor]");

            ++timesMoveConstructor;
        }

        LifeObject& operator=(const LifeObject&) noexcept
        {
            //std::println("{}", "operator=(const LifeObject&) [copy assignment]");
            ++timesCopyAssignment;
            return *this;
        }

        LifeObject& operator=(LifeObject&&) noexcept
        {
            //std::println("{}", "operator=(LifeObject&&) [move assignment]");
            ++timesMoveAssignment;
            return *this;
        }

        ~LifeObject() noexcept
        {
            //std::println("{}", "~LifeObject() [destructor]");
            ++timesDestructor;
        }


        static inline std::size_t timesConstructor{};
        static inline std::size_t timesCopyConstructor{};
        static inline std::size_t timesMoveConstructor{};
        static inline std::size_t timesCopyAssignment{};
        static inline std::size_t timesMoveAssignment{};
        static inline std::size_t timesDestructor{};

    private:
        std::array<bool, 100000> size{};
    };
}
