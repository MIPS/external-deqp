#ifndef _EGLUGLFUNCTIONLOADER_HPP
#define _EGLUGLFUNCTIONLOADER_HPP
/*-------------------------------------------------------------------------
 * drawElements Quality Program EGL Module
 * ---------------------------------------
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
 * \brief glw::FunctionLoader using eglGetProcAddress() and tcu::Library.
 *//*--------------------------------------------------------------------*/

#include "tcuDefs.hpp"
#include "tcuFunctionLibrary.hpp"
#include "glwFunctionLoader.hpp"

namespace eglu
{

class GLFunctionLoader : public glw::FunctionLoader
{
public:
										GLFunctionLoader	(const tcu::FunctionLibrary* platformLibrary);
	glw::GenericFuncType				get					(const char* name) const;

private:
										GLFunctionLoader	(const GLFunctionLoader&);
	GLFunctionLoader&					operator=			(const GLFunctionLoader&);

	const tcu::FunctionLibrary* const	m_library;			//!< Base platform library for functions. Used if eglGetProcAddress() fails.
};

} // eglu

#endif // _EGLUGLFUNCTIONLOADER_HPP
