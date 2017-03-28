//~~~~~~~~~~~~~~~~~~~~~~~~~~
// ��� ������� ������������ ����������� ����� ������������������ ������ 
// � ���������� ���������.
// *InputData - ��������� �� ������������������ ������.
// BytesNumber - ���������� ������, ��� ������� ��������� ����������� �����.
// Offset - �������� ������������ ������ ������������������
// ������, � �������� �������� ��������� ����������� ����� (0 - ��� ��������).
unsigned char ucCrcMaker(unsigned char *InputData, unsigned char BytesNumber, 
                         unsigned char Offset)
{
    register unsigned char i, j, Data, CrcCode = 0, Polinom = 0x69;
    for(i = Offset; i < BytesNumber + Offset; i++)
    {
        Data = InputData[i];
        for(j = 0; j < 8; j++)
        {
            if(CrcCode & (1 << 7))
            {
                CrcCode *= 2;
                if(Data & (1 << 7)) CrcCode ++;
                CrcCode ^= Polinom;
            }
            else
            {
                CrcCode *= 2;
                if(Data & (1 << 7)) CrcCode ++;
            }
            Data *= 2;
        }
    }
    return CrcCode;
} 