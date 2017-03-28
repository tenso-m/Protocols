/* Using Qt */
// Парсинг посылки, полученной от весового терминала
QByteArray getContent(QByteArray &bytes)
{
    QByteArray arr;
    auto packSize = bytes.size();
    if(packSize >= 3 && packSize <= 255)
    {
        bool check = true;
        while(check)
        {
            // Trash before 0xFF			
            while(bytes.indexOf(0xFF) != 0 && bytes.size() > 0)
                bytes.remove(0, 1);

            while(bytes.indexOf(0xFF) == 0 && bytes.size() > 0)
                bytes.remove(0, 1);

            // Trash at the and of packet
            if(bytes.indexOf(0xFF) > -1
                    && bytes.indexOf(0xFF, bytes.indexOf(0xFF)+1) > -1)
            {
                int range = bytes.size() - bytes.indexOf(0xFF, bytes.indexOf(0xFF)+1)+1;
                bytes.remove(bytes.indexOf(0xFF), range);
            }
            else
                return QByteArray();

            for(int i = 0; i < bytes.size(); i++)
            {
                arr.append(bytes.at(i));
                if(bytes.indexOf(0xFF) == i && bytes.indexOf(0xFE) == i+1)
                    i++;
            }

            auto n = arr.size();
            QByteArray checkCrc;
            if(n >= 3)
            {
                checkCrc.append(arr[0]);
                checkCrc.append(arr[1]);
                checkCrc.append('\0');
                if(arr.lastIndexOf(crc8(checkCrc)))
                {
                    arr.chop(1);
                    check = false;
                }
                else
                    return QByteArray();
            }
            else
                return QByteArray();
        }
    }
    else
        return QByteArray();

    return arr;
}
