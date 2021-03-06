#ifndef _DEDEFS_HPP
#define _DEDEFS_HPP
/*-------------------------------------------------------------------------
 * drawElements C++ Base Library
 * -----------------------------
 *
 * Copyright 2014 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 *//*!
 * \file
 * \brief Basic definitions.
 *//*--------------------------------------------------------------------*/

#include "deDefs.h"

#if !defined(__cplusplus)
#	error "C++ is required"
#endif

namespace de
{

//!< Compute absolute value of x.
template<typename T> inline T		abs			(T x)			{ return x < T(0) ? -x : x; }

//!< Get minimum of x and y.
template<typename T> inline T		min			(T x, T y)		{ return x <= y ? x : y; }

//!< Get maximum of x and y.
template<typename T> inline T		max			(T x, T y)		{ return x >= y ? x : y; }

//!< Clamp x in range a <= x <= b.
template<typename T> inline T		clamp		(T x, T a, T b)	{ DE_ASSERT(a <= b); return x < a ? a : (x > b ? b : x); }

//!< Test if x is in bounds a <= x < b.
template<typename T> inline bool	inBounds	(T x, T a, T b)	{ return a <= x && x < b; }

//!< Test if x is in range a <= x <= b.
template<typename T> inline bool	inRange		(T x, T a, T b)	{ return a <= x && x <= b; }

//! Helper for DE_CHECK() macros.
void throwRuntimeError (const char* message, const char* expr, const char* file, int line);

//! Default deleter.
template<typename T> struct DefaultDeleter
{
	inline DefaultDeleter (void) {}
	template<typename U> inline DefaultDeleter (const DefaultDeleter<U>&) {}
	template<typename U> inline DefaultDeleter<T>& operator= (const DefaultDeleter<U>&) { return *this; }
	inline void operator() (T* ptr) const { delete ptr;	}
};

//! A deleter for arrays
template<typename T> struct ArrayDeleter
{
	inline ArrayDeleter (void) {}
	template<typename U> inline ArrayDeleter (const ArrayDeleter<U>&) {}
	template<typename U> inline ArrayDeleter<T>& operator= (const ArrayDeleter<U>&) { return *this; }
	inline void operator() (T* ptr) const { delete[] ptr; }
};

//! Get an element of an array with a specified size.
template <int Size, typename Elem>
const Elem& getSizedArrayElement(const Elem (&array)[Size], int offset)
{
	DE_ASSERT(inBounds(offset, 0, Size));
	return array[offset];
}

} // de

/*--------------------------------------------------------------------*//*!
 * \brief Throw runtime error if condition is not met.
 * \param X		Condition to check.
 *
 * This macro throws std::runtime_error if condition X is not met.
 *//*--------------------------------------------------------------------*/
#define DE_CHECK_RUNTIME_ERR(X)				do { if ((!deGetFalse() && (X)) ? DE_FALSE : DE_TRUE) ::de::throwRuntimeError(DE_NULL, #X, __FILE__, __LINE__); } while(deGetFalse())

/*--------------------------------------------------------------------*//*!
 * \brief Throw runtime error if condition is not met.
 * \param X		Condition to check.
 * \param MSG	Additional message to include in the exception.
 *
 * This macro throws std::runtime_error with message MSG if condition X is
 * not met.
 *//*--------------------------------------------------------------------*/
#define DE_CHECK_RUNTIME_ERR_MSG(X, MSG)	do { if ((!deGetFalse() && (X)) ? DE_FALSE : DE_TRUE) ::de::throwRuntimeError(MSG, #X, __FILE__, __LINE__); } while(deGetFalse())

//! Get array start pointer.
#define DE_ARRAY_BEGIN(ARR) (&(ARR)[0])

//! Get array end pointer.
#define DE_ARRAY_END(ARR)	(DE_ARRAY_BEGIN(ARR) + DE_LENGTH_OF_ARRAY(ARR))

//! Empty C++ compilation unit silencing.
#if (DE_COMPILER == DE_COMPILER_MSC)
#	define DE_EMPTY_CPP_FILE namespace { deUint8 unused; }
#else
#	define DE_EMPTY_CPP_FILE
#endif

#endif // _DEDEFS_HPP
