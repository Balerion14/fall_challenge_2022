/**
 * @author Sorann753 (Doriath Arthus)
 * @date 2022
 * @license MIT
 */

#ifndef CININJECTOR_HPP
#define CININJECTOR_HPP

#include <iostream>
#include <sstream>

/**
 * @brief allow to inject strings into std::cin
 */
class cinInjector {
public:

    /**
     * @brief construct a new cinInjector object from a string
     * @param input the string to inject
     */
    cinInjector(std::string input)
    : iss(std::move(input)), backup(std::cin.rdbuf())
    {
        std::cin.rdbuf(iss.rdbuf());
    }

    /**
     * @brief construct a new cinInjector object
     */
    cinInjector()
    : iss(), backup(std::cin.rdbuf())
    {
        std::cin.rdbuf(iss.rdbuf());
    }

    /**
     * @brief destroy the cinInjector object and restore std::cin to its original state
     */
    ~cinInjector() {
        std::cin.rdbuf(backup);
    }

    /**
     * @brief inject data into the stream as a const reference
     * @param T the type of the data to inject
     * @param value the data to inject into the stream
     * @return cinInjector& a reference to this object
     */
    template<typename T>
    cinInjector& operator << (const T& value) {
        iss << value;
        return *this;
    }

    /**
     * @brief inject data into the stream as an rvalue reference
     * @param T the type of the data to inject
     * @param value the data to inject into the stream
     * @return cinInjector& a reference to this object
     */
    template<typename T>
    cinInjector& operator << (T&& value) {
        iss << std::move(value);
        return *this;
    }

    /**
     * @brief inject data into the stream as a const pointer
     * @param T the type of the data to inject
     * @param value the data to inject into the stream
     * @return cinInjector& a reference to this object
     */
    template<typename T>
    cinInjector& operator << (const T* value) {
        iss << value;
        return *this;
    }

private:

    std::streambuf* const backup = std::cin.rdbuf();
    std::stringstream iss;
};

#endif

/**
 * @license MIT
 * @copyright 2022 Arthus Doriath (Sorann753)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all copies
 * or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
 * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */