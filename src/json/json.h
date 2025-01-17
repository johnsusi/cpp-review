#pragma once

#include <concepts>
#include <map>
#include <string>
#include <variant>
#include <vector>

namespace rocksolid::json
{

class JsonValue
{

  public:
    explicit JsonValue() = delete;
    explicit JsonValue(std::nullptr_t);
    explicit JsonValue(bool value);
    explicit JsonValue(std::integral auto value) : _value(NumberValue{std::to_string(value)})
    {
    }
    explicit JsonValue(double value);
    explicit JsonValue(std::string value);
    explicit JsonValue(std::vector<JsonValue> value);
    explicit JsonValue(std::map<std::string, JsonValue> value);
    explicit JsonValue(const JsonValue &other) = default;
    JsonValue(JsonValue &&other) noexcept;
    JsonValue &operator=(const JsonValue &other) = default;
    JsonValue &operator=(JsonValue &&other) noexcept = default;
    ~JsonValue() = default;

    bool IsNull() const;
    bool IsFalse() const;
    bool IsTrue() const;
    bool IsNumber() const;
    bool IsString() const;
    bool IsArray() const;
    bool IsObject() const;

    template <typename T> T As() const
    {

        if constexpr (std::integral<T>)
        {
            return std::stoi(std::get<NumberValue>(_value).Value);
        }
        else if constexpr (std::floating_point<T>)
        {
            return std::stod(std::get<NumberValue>(_value).Value);
        }
        else if constexpr (std::convertible_to<std::string, T>)
        {
            return std::get<StringValue>(_value).Value;
        }
        else
        {
            throw std::runtime_error("Not a number or a string");
        }
    }

    template <> bool As() const
    {
        if (IsFalse())
        {
            return false;
        }
        if (IsTrue())
        {
            return true;
        }
        throw std::runtime_error("Not a boolean");
    }

    static JsonValue Null();
    static JsonValue False();
    static JsonValue True();
    static JsonValue Number(std::string value);
    static JsonValue String(std::string value);
    static JsonValue Array(std::vector<JsonValue> value);
    static JsonValue Object(std::map<std::string, JsonValue> value);

  private:
    struct NullValue
    {
    };
    struct FalseValue
    {
    };
    struct TrueValue
    {
    };
    struct NumberValue
    {
        std::string Value;
    };
    struct StringValue
    {
        std::string Value;
    };
    struct ArrayValue
    {
        std::vector<JsonValue> Value;
    };
    struct ObjectValue
    {
        std::map<std::string, JsonValue> Value;
    };

    using ValueType = std::variant<NullValue, FalseValue, TrueValue, NumberValue, StringValue, ArrayValue, ObjectValue>;
    ValueType _value;

    JsonValue(auto &&value) : _value(std::forward<decltype(value)>(value))
    {
    }
};

} // namespace rocksolid::json