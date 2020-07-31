#include "RadixSort.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
void RadixSort( uint8_t *pWork, uint8_t *pTemp, const size_t elementCount, const size_t elementSize )
{
	const size_t copySize = elementCount * elementSize;

	// CRAP
	/*
	pWork[ 0] = 227;
	pWork[ 1] = 132;
	pWork[ 2] = 20;
	pWork[ 3] = 191;


	pWork[ 4] = 53;
	pWork[ 5] = 119;
	pWork[ 6] = 65;
	pWork[ 7] = 191;

	pWork[ 8] = 117;
	pWork[ 9] = 236;
	pWork[10] = 45;
	pWork[11] = 191;
	//*/
	
	/*
	Serial.print("Element count: "); Serial.println(elementCount);
	Serial.print("Element Size: "); Serial.println(elementSize);
	Serial.print("Copy size: "); Serial.println(copySize);

	Serial.print("Working buffer before: ");
	const float *pFloatBufferWork = reinterpret_cast< float* >( pWork );
	for( size_t i = 0; i < elementCount; ++i )
	{
		Serial.print(pFloatBufferWork[i]);
		Serial.print(" ");
	}
	Serial.println();
	//*/
	// end of CRAP

	

	// 
	//size_t byteIdx = 0;
	for( size_t byteIdx = 0; byteIdx < elementSize; ++byteIdx )
	{
		// Cleat bytes count
		int byteCount[256];
		memset( byteCount, 0, sizeof( int ) * 256 );

		// Count all bytes in byteIdx position
		for( size_t i = 0; i < elementCount; ++i )
		{
			const size_t offset = i * elementSize + byteIdx;
			const uint8_t byte = pWork[offset];
			++byteCount[byte];
		}

		// CRAP
		/*
		Serial.println("Working bytes before: ");
		for( size_t i = 0; i < copySize; ++i )
		{
			Serial.print(pWork[i]);
			Serial.print(" ");
		}
		Serial.println();
		//*/

		/*
		Serial.println("Count of presented bytes: ");
		for( int i = 0; i < 256; ++i )
			if( byteCount[i] > 0 )
			{
				Serial.print(i);
				Serial.print("-");
				Serial.println(byteCount[i]);
			}
			*/
		// end of CRAP

		// Convert the each byte sum
		int sum = 0;
		for( int i = 0; i < 256; ++i )
		{
			const int thisItem = byteCount[i];
			byteCount[i] = sum;
			sum += thisItem;
		}

		// CRAP
		/*
		Serial.print("Position of bytes: ");
		for( int i = 0; i < 256; ++i )
		{
			Serial.print(i);
			Serial.print("-");
			Serial.println(byteCount[i]);
		}
		//*/
		// end of CRAP


		// Place data from work buffer to tmp buffer
		for( size_t i = 0; i < elementCount; ++i )
		{


			const size_t offset = i * elementSize + byteIdx;
			const uint8_t byte = pWork[offset];
			const int count = byteCount[byte];

			/*
			Serial.println();
			Serial.print("Offset: ");Serial.println(offset);
			Serial.print("Byte: ");Serial.println(byte);
			Serial.print("Position: ");Serial.println(count);
			//*/

			// Copy element from i-position of work buffer to count-position of tmp buffer
			for( size_t j = 0; j < elementSize; ++j )
			{
				const size_t workOffset = i * elementSize + j;
				const size_t tempOffset = count * elementSize + j;
				pTemp[tempOffset] = pWork[workOffset];
			}

			// Move position
			++byteCount[byte];

			// CRAP
			/*
			Serial.println("Tmp buffer: ");
			for( size_t i = 0; i < copySize; ++i )
			{
				Serial.print(pTemp[i]);
				Serial.print(" ");
			}
			Serial.println();
			//*/
			// end of CRAP
		}

		// And copy all data from temp buffer to work buffer
		//memcpy( pWork, pTemp, copySize );
		for( size_t i = 0; i < copySize; ++i )
			pWork[i] = pTemp[i];


		// CRAP
		/*
		Serial.println("Working bytes after: ");
		for( size_t i = 0; i < copySize; ++i )
		{
			Serial.print(pWork[i]);
			Serial.print(" ");
		}
		Serial.println();
		Serial.println();
		Serial.println();
		//*/
		// end of CRAP
	}

	// CRAP
	/*
	Serial.print("Working buffer after: ");
	for( size_t i = 0; i < elementCount; ++i )
	{
		Serial.print(pFloatBufferWork[i]);
		Serial.print(" ");
	}
	Serial.println();
	//*/
	// end of CRAP


	
}
////////////////////////////////////////////////////////////////////////////////////////////////////