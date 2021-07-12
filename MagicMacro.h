#pragma once

/**
 The whole magic in here was copied from
 https://stackoverflow.com/questions/44758329/c-or-macro-magic-to-generate-method-and-forward-arguments. So credits
 go to the according author as well.

 The only part slightly adjusted is `MAGICAL_MACRO` to demonstrate how the call can be wrapped in a lambda that could
 be transported in a queue
*/
#define MAGICAL_MACRO(return_type, method_name, ...) \
    return_type method_name(__VA_ARGS__) override \
    { \
        _q.push([=]() { return _obj.method_name(EVAL(MAP(TYPE_NAME, __VA_ARGS__))); }); \
        auto result = std::async([this]() { \
            tQueueType f; _q.pop(f); \
            std::cout << "\tImpl : " << std::this_thread::get_id() << std::endl; \
            return f(); \
        }); \
        std::cout << "\tProxy: " << std::this_thread::get_id() << std::endl; \
        return result.get(); \
    }

/* Define all types here */
#define SPLIT_int int COMMA
#define SPLIT_uint32_t uint32_t COMMA
#define SPLIT_char char COMMA
#define SPLIT_float float COMMA
#define SPLIT_double double COMMA

#define FIRST_(a, ...) a
#define SECOND_(a, b, ...) b

#define FIRST(...) FIRST_(__VA_ARGS__,)
#define SECOND(...) SECOND_(__VA_ARGS__,)

#define EMPTY()

#define EVAL(...) EVAL1024(__VA_ARGS__)
#define EVAL1024(...) EVAL512(EVAL512(__VA_ARGS__))
#define EVAL512(...) EVAL256(EVAL256(__VA_ARGS__))
#define EVAL256(...) EVAL128(EVAL128(__VA_ARGS__))
#define EVAL128(...) EVAL64(EVAL64(__VA_ARGS__))
#define EVAL64(...) EVAL32(EVAL32(__VA_ARGS__))
#define EVAL32(...) EVAL16(EVAL16(__VA_ARGS__))
#define EVAL16(...) EVAL8(EVAL8(__VA_ARGS__))
#define EVAL8(...) EVAL4(EVAL4(__VA_ARGS__))
#define EVAL4(...) EVAL2(EVAL2(__VA_ARGS__))
#define EVAL2(...) EVAL1(EVAL1(__VA_ARGS__))
#define EVAL1(...) __VA_ARGS__

#define DEFER1(m) m EMPTY()
#define DEFER2(m) m EMPTY EMPTY()()
#define DEFER3(m) m EMPTY EMPTY EMPTY()()()
#define DEFER4(m) m EMPTY EMPTY EMPTY EMPTY()()()()

#define IS_PROBE(...) SECOND(__VA_ARGS__, 0)
#define PROBE() ~, 1

#define CAT(a,b) a ## b

#define NOT(x) IS_PROBE(CAT(_NOT_, x))
#define _NOT_0 PROBE()

#define BOOL(x) NOT(NOT(x))

#define IF_ELSE(condition) _IF_ELSE(BOOL(condition))
#define _IF_ELSE(condition) CAT(_IF_, condition)

#define _IF_1(...) __VA_ARGS__ _IF_1_ELSE
#define _IF_0(...)             _IF_0_ELSE

#define _IF_1_ELSE(...)
#define _IF_0_ELSE(...) __VA_ARGS__

#define HAS_ARGS(...) BOOL(FIRST(_END_OF_ARGUMENTS_ __VA_ARGS__)())
#define _END_OF_ARGUMENTS_() 0

#define MAP(m, first, ...)           \
  m(first)                           \
  IF_ELSE(HAS_ARGS(__VA_ARGS__))(    \
    COMMA DEFER2(_MAP)()(m, __VA_ARGS__)   \
  )(                                 \
    /* Do nothing, just terminate */ \
  )
#define _MAP() MAP


#define COMMA ,

#define CALL(A,B) A B
#define SPLIT(D) EVAL1(CAT(SPLIT_, D))
#define TYPE_NAME(D) CALL(SECOND,(SPLIT(D)))
