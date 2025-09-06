// Markus Scholtes 2025
// XOR of the first n bytes of a file
// A second call with the same parameters restores the file to its original state
// Invocation: XORFile <FILENAME> [<COUNTOFBYTES>]
// <COUNTOFBYTES> defaults to 32

// Compile with: C:\Windows\Microsoft.NET\Framework64\v4.0.30319\csc.exe XORFile.cs

using System;
using System.IO;

class XORFile
{
	static int Main(string[] arguments)
	{
    if (arguments.Length < 1)
    {
    	Console.WriteLine("Invocation: XORFile <FILENAME> [<COUNTOFBYTES>]");
    	return -1;
  	}

		string fileName = arguments[0];
		int numBytes = 32;
		if (arguments.Length > 1)
		{
      bool success = int.TryParse(arguments[1], out numBytes);
      if (!success)
    	{
    		Console.WriteLine("Wrong parameter for count of bytes.");
    		return -1;
  		}
  		if (numBytes < 1)
    	{
    		Console.WriteLine("Count of bytes must be positive.");
    		return -1;
  		}
		}

		byte[] dataArray = new byte[numBytes];

		try
		{
			using (FileStream fileStream = new FileStream(fileName, FileMode.Open, FileAccess.ReadWrite))
			{
				numBytes = fileStream.Read(dataArray, 0, numBytes);

				if (numBytes > 0)
				{
					Console.Write("Original value(s): ");
					for (int i = 0; i < numBytes; i++)
					{
						Console.Write("[" + dataArray[i].ToString("X") + "]");
						dataArray[i] = (byte)~dataArray[i];
					}

					fileStream.Seek(0, SeekOrigin.Begin);
					fileStream.Write(dataArray, 0, numBytes);

					Console.Write("\r\nNew value(s): ");
					for (int i = 0; i < numBytes; i++)
					{
						Console.Write("[" + dataArray[i].ToString("X") + "]");
					}
				}
				else
				{
					Console.Write("Read no data.");
				}
			}
		}
		catch (Exception ex)
		{
			Console.WriteLine("Error: " + ex.Message);
			return 1;
		}

		return 0;
	}
}
