#pragma once
#include <initializer_list>
#include <stdint.h>
#include <vector>

#include "BufferElement.h"

namespace Hurma {

namespace Render {

    class HURMA_API BufferLayout
	{
	public:
		BufferLayout() {}

		BufferLayout(std::initializer_list<BufferElement> elements)
			: mElements(elements)
		{
			calculateOffsetsAndStride();
		}

		uint32_t getStride() const { return mStride; }
		const std::vector<BufferElement>& getElements() const { return mElements; }

		std::vector<BufferElement>::iterator begin() { return mElements.begin(); }
		std::vector<BufferElement>::iterator end() { return mElements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return mElements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return mElements.end(); }

	private:
		void calculateOffsetsAndStride()
		{
			size_t offset = 0;
			mStride = 0;
			for (auto& element : mElements)
			{
				element.offset = offset;
				offset += element.size;
				mStride += element.size;
			}
		}
	private:
        #pragma warning(push)
        #pragma warning(disable:4251)
		std::vector<BufferElement> mElements;
		#pragma warning(pop)
        
        uint32_t mStride = 0;
	};

}

}