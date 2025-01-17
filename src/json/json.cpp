#include "json.h"

using JsonValue = rocksolid::json::JsonValue;

JsonValue::JsonValue(std::nullptr_t) : _value(NullValue{})
{
}

JsonValue::JsonValue(bool value) : _value(value ? ValueType(TrueValue{}) : ValueType(FalseValue{}))
{
}

JsonValue::JsonValue(double value) : _value(NumberValue{std::to_string(value)})
{
}

JsonValue::JsonValue(std::string value) : _value(StringValue{std::move(value)})
{
}

JsonValue::JsonValue(std::vector<JsonValue> value) : _value(ArrayValue{std::move(value)})
{
}

JsonValue::JsonValue(std::map<std::string, JsonValue> value) : _value(ObjectValue{std::move(value)})
{
}

bool rocksolid::json::JsonValue::IsNull() const
{
    return std::holds_alternative<NullValue>(_value);
}
bool rocksolid::json::JsonValue::IsFalse() const
{
    return std::holds_alternative<FalseValue>(_value);
}
bool rocksolid::json::JsonValue::IsTrue() const
{
    return std::holds_alternative<TrueValue>(_value);
}
bool rocksolid::json::JsonValue::IsNumber() const
{
    return std::holds_alternative<NumberValue>(_value);
}
bool rocksolid::json::JsonValue::IsString() const
{
    return std::holds_alternative<StringValue>(_value);
}
bool rocksolid::json::JsonValue::IsArray() const
{
    return std::holds_alternative<ArrayValue>(_value);
}
bool rocksolid::json::JsonValue::IsObject() const
{
    return std::holds_alternative<ObjectValue>(_value);
}

JsonValue rocksolid::json::JsonValue::Null()
{
    return JsonValue(NullValue{});
}

JsonValue rocksolid::json::JsonValue::False()
{
    return JsonValue(FalseValue{});
}

JsonValue rocksolid::json::JsonValue::True()
{
    return JsonValue(TrueValue{});
}

JsonValue rocksolid::json::JsonValue::Number(std::string value)
{
    return JsonValue(NumberValue{std::move(value)});
}

JsonValue rocksolid::json::JsonValue::String(std::string value)
{
    return JsonValue(StringValue{std::move(value)});
}

JsonValue rocksolid::json::JsonValue::Array(std::vector<JsonValue> value)
{
    return JsonValue(ArrayValue{std::move(value)});
}

JsonValue rocksolid::json::JsonValue::Object(std::map<std::string, JsonValue> value)
{
    return JsonValue(ObjectValue{std::move(value)});
}
