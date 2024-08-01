#include <cstddef>
#include <print>
#include <source_location>
#include <filesystem>

namespace farra
{
    //template <std::size_t Size>
    class LifeObject
    {
    public:
        LifeObject(const std::source_location sl = std::source_location::current()) noexcept
        {
            #ifdef NDEBUG
            #else
            std::filesystem::path path {sl.file_name()};
            std::println("{} ({}:{}) `{}` -> {}", path.filename().string(), sl.line(), sl.column(), sl.function_name(),
                "LifeObject() [constructor]");
            #endif

            ++timesConstructor;
        }

        LifeObject(const LifeObject& other, const std::source_location sl = std::source_location::current()) noexcept
        {
            #ifdef NDEBUG
            #else
            std::filesystem::path path {sl.file_name()};
            std::println("{} ({}:{}) `{}` -> {}", path.filename().string(), sl.line(), sl.column(), sl.function_name(),
                "LifeObject(const LifeObject&) [copy constructor]");
            #endif

            ++timesCopyConstructor;
        }

        LifeObject(LifeObject&&, const std::source_location sl = std::source_location::current()) noexcept
        {
            #ifdef NDEBUG
            #else
            std::filesystem::path path {sl.file_name()};
            std::println("{} ({}:{}) `{}` -> {}", path.filename().string(), sl.line(), sl.column(), sl.function_name(),
                "LifeObject(LifeObject&&) [move constructor]");
            #endif

            ++timesMoveConstructor;
        }

        LifeObject& operator=(const LifeObject&) noexcept
        {
            #ifdef NDEBUG
            #else
            std::println("{}", "operator=(const LifeObject&) [copy assignment]");
            #endif

            ++timesCopyAssignment;
            return *this;
        }

        LifeObject& operator=(LifeObject&&) noexcept
        {
            #ifdef NDEBUG
            #else
            std::println("{}", "operator=(LifeObject&&) [move assignment]");
            #endif

            ++timesMoveAssignment;
            return *this;
        }

        ~LifeObject() noexcept
        {
            #ifdef NDEBUG
            #else
            std::println("{}", "~LifeObject() [destructor]");
            #endif

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
