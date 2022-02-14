enum
{
	c1 = 95,
	c2 = 78,
	cx1 = 0x246DC5,
	cx2 = 0x9F262B
};

CString MakeSerialString(int serial_number)
{
	CString serial_string;
	LPTSTR hex_str = "0123456789ABCDEF";

	if ((serial_number >= 1) && (serial_number <= 100000))
	{
		int n1 = (serial_number * c1) ^ cx1;
		int n2 = (serial_number * c2) ^ cx2;
		serial_string += hex_str[(n1 >> 20) & 0x0F];	// 1
		serial_string += hex_str[(n2 >>  0) & 0x0F];	// 2
		serial_string += hex_str[(n1 >> 12) & 0x0F];	// 3
		serial_string += hex_str[(n2 >>  8) & 0x0F];	// 4
		serial_string += hex_str[(n1 >>  4) & 0x0F];	// 5
		serial_string += hex_str[(n2 >> 16) & 0x0F];	// 6
		serial_string += hex_str[(n1 >>  0) & 0x0F];	// A
		serial_string += hex_str[(n2 >> 20) & 0x0F];	// B
		serial_string += hex_str[(n1 >>  8) & 0x0F];	// C
		serial_string += hex_str[(n2 >> 12) & 0x0F];	// D
		serial_string += hex_str[(n1 >> 16) & 0x0F];	// E
		serial_string += hex_str[(n2 >>  4) & 0x0F];	// F
	}

	return serial_string;
}

int ExtractSerialNumber(CString serial_string)
{
	int serial_number = 0;

	if (serial_string.GetLength() == 12)
	{
		serial_string.MakeUpper();
		CString hex_str = "0123456789ABCDEF";
		int x1 = ((
			(hex_str.Find(serial_string[ 0]) << 20) +
			(hex_str.Find(serial_string[10]) << 16) +
			(hex_str.Find(serial_string[ 2]) << 12) +
			(hex_str.Find(serial_string[ 8]) <<  8) +
			(hex_str.Find(serial_string[ 4]) <<  4) +
			(hex_str.Find(serial_string[ 6]) <<  0)) ^ cx1) / c1;
		int x2 = ((
			(hex_str.Find(serial_string[ 7]) << 20) +
			(hex_str.Find(serial_string[ 5]) << 16) +
			(hex_str.Find(serial_string[ 9]) << 12) +
			(hex_str.Find(serial_string[ 3]) <<  8) +
			(hex_str.Find(serial_string[11]) <<  4) +
			(hex_str.Find(serial_string[ 1]) <<  0)) ^ cx2) / c2;
		if ((x1 == x2) && (x1 >= 1) && (x1 <= 100000))
		{
			return x1;
		}
	}

	return serial_number;
}

//**********************

CString MakeSerialString(int serial_number)
{
	CString serial_string;
	LPTSTR hex_str = "0123456789BCDEFGHIJLNOPQSTUVWXYZ";

	if ((serial_number >= 1) && (serial_number <= 100000))
	{
		__int64 n1 = (serial_number * c1) ^ cx1;
		__int64 n2 = (serial_number * c2) ^ cx2;
		__int64 n =
			(((n1 >> 20) & 0x0F) << 44) +	// 1
			(((n2 >>  0) & 0x0F) << 40) +	// 2
			(((n1 >> 12) & 0x0F) << 36) +	// 3
			(((n2 >>  8) & 0x0F) << 32) +	// 4
			(((n1 >>  4) & 0x0F) << 28) +	// 5
			(((n2 >> 16) & 0x0F) << 24) +	// 6
			(((n1 >>  0) & 0x0F) << 20) +	// A
			(((n2 >> 20) & 0x0F) << 16) +	// B
			(((n1 >>  8) & 0x0F) << 12) +	// C
			(((n2 >> 12) & 0x0F) <<  8) +	// D
			(((n1 >> 16) & 0x0F) <<  4) +	// E
			(((n2 >>  4) & 0x0F) <<  0);	// F
		serial_string += hex_str[(n >> 45) & 0x1F];	// 1
		serial_string += hex_str[(n >> 40) & 0x1F];	// 2
		serial_string += hex_str[(n >> 35) & 0x1F];	// 3
		serial_string += hex_str[(n >> 30) & 0x1F];	// 4
		serial_string += hex_str[(n >> 25) & 0x1F];	// 5
		serial_string += hex_str[(n >> 20) & 0x1F];	// 6
		serial_string += hex_str[(n >> 15) & 0x1F];	// 7
		serial_string += hex_str[(n >> 10) & 0x1F];	// 8
		serial_string += hex_str[(n >>  5) & 0x1F];	// 9
		serial_string += hex_str[(n >>  0) & 0x1F];	// 10
	}

	return serial_string;
}

int ExtractSerialNumber(CString serial_string)
{
	int serial_number = 0;

	if (serial_string.GetLength() == 10)
	{
		serial_string.MakeUpper();
		CString hex_str = "0123456789BCDEFGHIJLNOPQSTUVWXYZ";
		__int64 x = ((
			(hex_str.Find(serial_string[ 0]) << 45) +
			(hex_str.Find(serial_string[ 1]) << 40) +
			(hex_str.Find(serial_string[ 2]) << 35) +
			(hex_str.Find(serial_string[ 3]) << 30) +
			(hex_str.Find(serial_string[ 4]) << 25) +
			(hex_str.Find(serial_string[ 5]) << 20) +
			(hex_str.Find(serial_string[ 6]) << 15) +
			(hex_str.Find(serial_string[ 7]) << 10) +
			(hex_str.Find(serial_string[ 8]) <<  5) +
			(hex_str.Find(serial_string[ 9]) <<  0);
		__int64 x1 = ((
			(((x >> 44) & 0x1F) << 20) +
			(((x >>  4) & 0x1F) << 16) +
			(((x >> 36) & 0x1F) << 12) +
			(((x >> 12) & 0x1F) <<  8) +
			(((x >> 28) & 0x1F) <<  4) +
			(((x >> 20) & 0x1F) <<  0)) ^ cx1) / c1;
		__int64 x2 = ((
			(((x >> 16) & 0x1F) << 20) +
			(((x >> 24) & 0x1F) << 16) +
			(((x >>  8) & 0x1F) << 12) +
			(((x >> 32) & 0x1F) <<  8) +
			(((x >>  0) & 0x1F) <<  4) +
			(((x >> 40) & 0x1F) <<  0)) ^ cx2) / c2;
		if ((x1 == x2) && (x1 >= 1) && (x1 <= 100000))
		{
			return x1;
		}
	}

	return serial_number;
}
