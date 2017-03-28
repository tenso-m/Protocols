/* Пример с использованием Qt */
char crc8(const QByteArray &bytes)
{
    unsigned char crc = 0;
    for (int i = 0; i < bytes.size(); i++)
    {
        char c = bytes.at(i);
        for (int j = 0; j < 8; j++)
        {
            bool b = crc & 0x80_sc;
            crc = crc << 1;
            if (c & 0x80_sc)
                crc++;
            if (b)
                crc ^= 0x69_sc;
            c = c << 1;
        }
    }
    return crc;
}