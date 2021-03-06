/*-------------------------------------------------------------------------
 * drawElements Quality Program OpenGL ES 3.0 Module
 * -------------------------------------------------
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
 * \brief Compressed texture tests
 *//*--------------------------------------------------------------------*/

#include "es3fCompressedTextureTests.hpp"
#include "es3fASTCDecompressionCases.hpp"
#include "gluStrUtil.hpp"
#include "gluTextureUtil.hpp"
#include "tcuCompressedTexture.hpp"
#include "tcuVector.hpp"
#include "deStringUtil.hpp"

#include <string>

using std::string;
using tcu::IVec3;
using tcu::CompressedTexture;

namespace deqp
{
namespace gles3
{
namespace Functional
{

static const string getASTCFormatShortName (CompressedTexture::Format format)
{
	DE_ASSERT(tcu::isASTCFormat(format));
	const IVec3 blockSize = tcu::getASTCBlockSize(format);
	DE_ASSERT(blockSize.z() == 1);

	return de::toString(blockSize.x()) + "x" + de::toString(blockSize.y()) + (tcu::isASTCSRGBFormat(format) ? "_srgb" : "");
}

CompressedTextureTests::CompressedTextureTests (Context& context)
	: TestCaseGroup (context, "compressed", "Compressed Texture Tests")
{
}

CompressedTextureTests::~CompressedTextureTests (void)
{
}

void CompressedTextureTests::init (void)
{
	// ASTC cases.
	{
		TestCaseGroup* const astcGroup = new TestCaseGroup(m_context, "astc", "ASTC Tests");
		addChild(astcGroup);

		// Block test cases.

		for (int astcTestTypeI = 0; astcTestTypeI < ASTCBLOCKTESTTYPE_LAST; astcTestTypeI++)
		{
			const ASTCBlockTestType		astcTestType	= (ASTCBlockTestType)astcTestTypeI;
			TestCaseGroup* const		testTypeGroup	= new TestCaseGroup(m_context, getBlockTestTypeName(astcTestType), getBlockTestTypeDescription(astcTestType));
			astcGroup->addChild(testTypeGroup);

			for (int formatI = 0; formatI < CompressedTexture::FORMAT_LAST; formatI++)
			{
				const CompressedTexture::Format format = (CompressedTexture::Format)formatI;

				if (!tcu::isASTCFormat(format))
					continue;
				if (tcu::isASTCSRGBFormat(format) && isBlockTestTypeHDROnly(astcTestType))
					continue;

				testTypeGroup->addChild(new ASTCBlockCase2D(m_context, getASTCFormatShortName(format).c_str(), glu::getCompressedTexFormatName(glu::getGLFormat(format)), astcTestType, format));
			}
		}

		// Image size/block size remainder cases.

		{
			TestCaseGroup* const blockSizeRemainderGroup = new TestCaseGroup(m_context, "block_size_remainder", "Test image size/block size remainders");
			astcGroup->addChild(blockSizeRemainderGroup);

			for (int formatI = 0; formatI < CompressedTexture::FORMAT_LAST; formatI++)
			{
				const CompressedTexture::Format format = (CompressedTexture::Format)formatI;

				if (!tcu::isASTCFormat(format))
					continue;

				blockSizeRemainderGroup->addChild(new ASTCBlockSizeRemainderCase2D(m_context, getASTCFormatShortName(format).c_str(), glu::getCompressedTexFormatName(glu::getGLFormat(format)), format));
			}
		}
	}
}

} // Functional
} // gles3
} // deqp
