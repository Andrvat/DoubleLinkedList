#pragma once

#include <exception>
#include <string>

namespace LinkedLists {

    /**
     * @class LinkedListsException
     *
     * @brief A simple exception class that allows to use exceptions not only from STL
     *
     * @inherit std::exception
     *
     * @author Andrey Valitov
     *
     * @version 1.0
     */
    class LinkedListsException : public std::exception {
    private:
        std::string errorMessage_;
    public:
        LinkedListsException() = default;

        explicit LinkedListsException(const std::string &errorMessage) {
            errorMessage_ = errorMessage;
        }

        [[nodiscard]] const char *what() const noexcept override {
            return errorMessage_.c_str();
        }
    };

}
